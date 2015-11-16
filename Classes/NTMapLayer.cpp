
#include "NTMapLayer.h"
#include "NTRoad.h"
#include "CCShake.h"
#include "NTCoinPosData.h"
#include "json.h"
#include "NTSharedJsonData.h"
#include "NTUtility.h"

#define  TEST_MODE 1
USING_NS_CC;

NTMapLayer::~NTMapLayer()
{
	/*CC_SAFE_RELEASE(m_pBoxArray);*/
}

// on "init" you need to initialize your instance
bool NTMapLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	initValues();

// 	//天空
// 	CCSprite* pSky = CCSprite::create("game/gd_tk.png");
// 	pSky->setPosition(ccp(winSize.width/2, 373));
// 	pSky->setScaleX(winSize.width/pSky->getContentSize().width);
// 	this->addChild(pSky, GAME_MAP_SKY);
// 	//云
// 	CCSprite* pCloud1 = CCSprite::create("game/gd_yu_0.png");
// 	pCloud1->setPosition(ccp(200, 406));
// 	this->addChild(pCloud1, GAME_MAP_CLOUD);
// 	CCSprite* pCloud2 = CCSprite::create("game/gd_yu_0.png");
// 	pCloud2->setPosition(ccp(577, 446));
// 	this->addChild(pCloud2, GAME_MAP_CLOUD);


	//滚动背景
	float autoBgY[6] = {377, 377, 252, 251.5, 168, 168};
	for(unsigned int i=0; i<6; i++){
		//滚动背景1,2,3
		CCPoint pPicturePos = ccp(winSize.width*0.5f, autoBgY[i]);
		CCPoint pAimPos = ccp(-winSize.width, 0);
		CCPoint pBackPos = ccp(winSize.width, 0);
		m_pAutoBg[i] = NTAutoScrollLayer::create(CCString::createWithFormat("game/%s", autoBgFileName[i])->getCString(), pPicturePos);
		m_pAutoBg[i]->setSpeed(-getSpeed()*autoBgSpeedScale[i/2]);
		m_pAutoBg[i]->setAimPos(pAimPos);
		m_pAutoBg[i]->setBackPos(pBackPos);
		m_pAutoBg[i]->setPositionX(winSize.width*(i%2));
		this->addChild(m_pAutoBg[i], GAME_MAP_AUTO_BG);
	}

	//金库模式背景
	for(unsigned int i=6; i<8; i++){
		CCPoint pPicturePos = ccp(winSize.width/2, winSize.height/2);
		CCPoint pAimPos = ccp(-winSize.width, 0);
		CCPoint pBackPos = ccp(winSize.width, 0);
		m_pAutoBg[i] = NTAutoScrollLayer::create(CCString::createWithFormat("game/%s", autoBgFileName[i])->getCString(), pPicturePos);
		m_pAutoBg[i]->setSpeed(-getSpeed()*autoBgSpeedScale[i/2]);
		m_pAutoBg[i]->setAimPos(pAimPos);
		m_pAutoBg[i]->setBackPos(pBackPos);
		m_pAutoBg[i]->setPositionX(winSize.width*(i%2));
		this->addChild(m_pAutoBg[i], GAME_MAP_AUTO_BG+1);
		m_pAutoBg[i]->setVisible(false);
	}

	//天空模式背景
	m_pSkyBg = CCSprite::create("sky_bg.png");
	m_pSkyBg->setScaleX(4.0f);
	m_pSkyBg->setPosition(ccp(winSize.width/2, winSize.height/2));
	m_pSkyBg->setVisible(false);
	this->addChild(m_pSkyBg, GAME_MAP_AUTO_BG+100);

	//超级模式的光
	m_pSuperModeLight = CCSprite::create("game/eff_scene.png");
	m_pSuperModeLight->setScaleX(4.0f);
	m_pSuperModeLight->setPosition(ccp(winSize.width/2, winSize.height/2));
	m_pSuperModeLight->setVisible(false);
	this->addChild(m_pSuperModeLight, GAME_MAP_AUTO_BG+200);

	//初始化基础地图
    createBaseMap();

	scheduleUpdate();

    return true;
}


void NTMapLayer::initValues()
{
	//生成一条道路，道路起始点，ccp(0, 150)，1.0个屏幕
	m_pBoxBatchNode = CCSpriteBatchNode::create("box.png");
	this->addChild(m_pBoxBatchNode);

	m_pBoxArray = CCArray::create();
	m_pBoxArray->retain();

	m_pBoxFreeArray = CCArray::create();
	m_pBoxFreeArray->retain();

	m_fLeftLine=0;

	m_fSpeed = BASE_SPEED;

	m_fSpeedExtra = 0;

	m_fSpeedOrginal = 0;

	m_bSuperMode = false;

	m_bIsShake = false;

	m_fLength = 0;

	m_iMapLevel = ROAD_HARD_LEVEL_500;

	iCurrentBlank = 0;

	m_bIsMapStop = false;

	m_pEffectLayer = NTEffectLayer::create();
	addChild(m_pEffectLayer);
	m_pEffectLayer->setMapLayer(this);
}

void NTMapLayer::update( float dt )
{
	if(getIsMapStop()){
		return;
	}

	float fMoveGap = m_fSpeed*dt;
	m_fLength += fMoveGap;
	
	//按Speed移动地图,leftLine也要跟着更新
	CCObject* pObj;
	CCARRAY_FOREACH(m_pBoxArray, pObj){
		NTBox* pBox = (NTBox*)pObj;
		if(pBox->shouldBeMoveWithMap()){
			pBox->setPositionX(pBox->getPositionX()-fMoveGap*pBox->getSpeedScale());
		}
	}
	m_fLeftLine-=fMoveGap;

	//移除图块
	CCArray* pArrayRemvo = CCArray::create();
	CCARRAY_FOREACH(m_pBoxArray, pObj){
		NTBox* pBox = (NTBox*)pObj;
		CCPoint pPOS = pBox->getLeftPos();
		if(pBox->shouldBeRecycle()){
			pBox->removeFromParentAndCleanup(false);
			if(pBox->isShouldInFreeArray()){
				m_pBoxFreeArray->addObject(pBox);
			}
			pArrayRemvo->addObject(pBox);
			pBox->reset();
		}
	}
	m_pBoxArray->removeObjectsInArray(pArrayRemvo);


	//补充图块,如果这一帧的移动，会造成leftLine位置出现在屏幕上，则补充图块
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	while (m_fLeftLine<=winSize.width)
	{
			if(m_bSuperMode){
				addGoldRoad();
				continue;
			}

			//生成道路
			NTRoad* pRoad = createRoad();

			createBoxOnRoad(pRoad);


			//生成远景气球
			if(CCRANDOM_0_1()<0.05f){
				int iTypeBalloon = ((int)(CCRANDOM_0_1()*3))%2+BOX_BALLOON1;
				NTBox* pBox = createBoxWithType(iTypeBalloon);
				pBox->setPosition(ccp(pRoad->getPositionX(), CCRANDOM_0_1()*100+350));		
				pBox->setSpeedScale(autoBgSpeedScale[2]);
				pBox->showSelfEffect(0.0f);
				m_pBoxBatchNode->addChild(pBox, GAME_MAP_AUTO_BG);
			}
			
		
	}

	//增加移动速度
	if(m_fSpeed<UP_SPEED){
		m_fSpeed+=ADD_SPEED;

		//滚动背景
		for(unsigned int i=0; i<8; i++){
			if(m_pAutoBg[i]->isVisible()){
				m_pAutoBg[i]->setSpeed(-getSpeed()*autoBgSpeedScale[i/2]);
			}
			
		}
	}
	else{
		m_fSpeed=UP_SPEED;
	}
	

	updateMapLevel();
}

void NTMapLayer::createBoxOnRoad( NTRoad* pRoad )
{
	//生成金币
// 			int iCoinCount = pRoad->getRoadLength()+2;
// 			for(unsigned int i=0; i<iCoinCount; i++){
// 
// 				if(i==iCoinCount/2){
// 					//生成一个坐骑
// 					NTBox* pBox = createBoxWithType(CCRANDOM_0_1()>0.5f?BOX_MOUNT_HORSE:BOX_MOUNT_BEAR);
// 					pBox->setPosition(ccp(pRoad->getPositionX()+pBox->getContentSize().width*(i+0.5f-iCoinCount/2), 
// 						pRoad->getHightLine()+100));				
// 					m_pBoxBatchNode->addChild(pBox, 20);
// 					continue;
// 				}
// 
// 				NTBox* pBox = createBoxWithType(BOX_COIN);
// 				pBox->setPosition(ccp(pRoad->getPositionX()+pBox->getContentSize().width*(i+0.5f-iCoinCount/2), 
// 					pRoad->getHightLine()+100));				
// 				m_pBoxBatchNode->addChild(pBox, 20);
// 			}

	//如果是空隙
	if(pRoad->getType()==ROAD_BLANK){
		createBlockOnAir(pRoad->getPosition());
	}
	//如果是真实道路
	else{
		//范围内生成金币
		bool bBoxInRect = createBoxInRect(
			ccp(pRoad->getLeftPos().x, pRoad->getHightLine()+100), 
			ccp(pRoad->getRightPos().x, pRoad->getHightLine()+100));

		//生成弹簧
		int iCountSpring = pRoad->getHight()==ROAD_POSY_LOW/* && pRoad->getRoadLength()==0*/?1:0;
		for(unsigned int i=0; i<iCountSpring; i++){
			NTBox* pBox = createBoxWithType(BOX_SPRING);
			pBox->setPosition(ccp(pRoad->getLeftPos().x+pRoad->getContentSize().width/2, 
				pRoad->getHightLine()+pBox->getContentSize().height/2));				
			m_pBoxBatchNode->addChild(pBox, 15);

			//如果没有生成金币堆，生成弧线金币
			if(!bBoxInRect){
				if(CCRANDOM_0_1()<0.5f){
					int iRand = ((int)(CCRANDOM_0_1()*10))%4;
					switch(iRand)
					{
					case 0:
						{
							addGameCoinInSin(ccpAdd(ccp(pRoad->getLeftPos().x, pRoad->getHightLine()), ccp(0, pBox->getContentSize().height)), 
								120, pRoad->getContentSize().width
								);
						}break;
					case 1:
						{
							addGameCoinInSin(ccpAdd(ccp(pRoad->getLeftPos().x, pRoad->getHightLine()), ccp(0, pBox->getContentSize().height)), 
								150, pRoad->getContentSize().width/2
								);
							addGameCoinInSin(ccpAdd(ccp(pBox->getPositionX(), pRoad->getHightLine()), ccp(0, pBox->getContentSize().height)), 
								150, pRoad->getContentSize().width/2
								);
						}break;
					case 2:
						{
							addGameCoinInSin(ccpAdd(ccp(pBox->getPositionX(), pRoad->getHightLine()), ccp(0, pBox->getContentSize().height+30)), 
								170, pRoad->getContentSize().width/2
								);
						}break;
					case 3:
						{
							addGameCoinInSin(ccpAdd(ccp(pRoad->getLeftPos().x, pRoad->getHightLine()), ccp(0, pBox->getContentSize().height+50)), 
								40, pRoad->getContentSize().width, 0.5f
								);
						}break;
					}
				}
			}
		}

		//生成钩子
		int iCountHook = pRoad->getHight()==ROAD_POSY_HIGH&&!bBoxInRect?((int)(CCRANDOM_0_1()*10))%pRoad->getRoadLength():0;
		int iType = ((int)(CCRANDOM_0_1()*10))%3+BOX_HOOK1;
		for(unsigned int i=0; i<iCountHook; i++){
			NTBox* pBox = createBoxWithType(iType);
			pBox->setPosition(ccp(pRoad->getPositionX()+pBox->getContentSize().width*(i+0.5f-iCountHook/2), 
				pRoad->getHightLine()+pBox->getContentSize().height/2+ACTOR_STAND_MIN_HIGH));				
			m_pBoxBatchNode->addChild(pBox, 15);
			pBox->showSelfEffect(0.1f*i);
		}
		//如果生成了钩子
		if(iCountHook>0){
			if(CCRANDOM_0_1()<0.5f){
				addGameCoinInSin(ccpAdd(ccp(pRoad->getLeftPos().x, pRoad->getHightLine()), ccp(0, 20)), 
					20, pRoad->getContentSize().width, 0.001f, false
					);
			}
		}
		


		//生成飞行障碍
		if(pRoad->getRoadLength()>=4 && iCountHook<=0){
			if(CCRANDOM_0_1()<0.3f+m_iMapLevel*0.25f){
				showSpecialHit(ccp(0, pRoad->getHightLine()+30));
				if(m_iMapLevel>=2){
					showSpecialHit(ccp(0, pRoad->getHightLine()));
				}
				if(m_iMapLevel>=5){
					showSpecialHit(ccp(0, pRoad->getHightLine()+60));
				}
			}
		}

		//生成路面障碍
		if(iCountHook<=0 && iCountSpring<=0){
			int iBlockCount = ((int)(CCRANDOM_0_1()*10))%pRoad->getRoadLength();
			int iType = ((int)(CCRANDOM_0_1()*10))%4+BOX_BLOCK1;
			NTBox* pBox = NTBox::createBox(iType);
			iBlockCount = pBox->getContentSize().width*iBlockCount>pRoad->getContentSize().width?
				pRoad->getContentSize().width/pBox->getContentSize().width-1:iBlockCount;
			for(unsigned int i=0; i<iBlockCount; i++){
				NTBox* pBox = createBoxWithType(iType);
				pBox->setPosition(ccp(pRoad->getPositionX()+pBox->getContentSize().width*(i+0.5f-iBlockCount/2), 
					pRoad->getHightLine()+pBox->getContentSize().height/2-12));
				m_pBoxBatchNode->addChild(pBox, 15);
			}

			//如果有路面障碍
			if(!bBoxInRect && iBlockCount>0){
				if(CCRANDOM_0_1()<0.5f){
					addGameCoinInSin(ccpAdd(ccp(pRoad->getLeftPos().x, pRoad->getHightLine()), ccp(0, 120)), 
						20, pRoad->getContentSize().width, 0.5f
						);
				}
			}

			//没有路面障碍
			if(!bBoxInRect && iBlockCount<=0){
				if(CCRANDOM_0_1()<0.5f){
					addGameCoinInSin(ccpAdd(ccp(pRoad->getLeftPos().x, pRoad->getHightLine()), ccp(0, 50)), 
						20, pRoad->getContentSize().width, 0.001f
						);
				}
			}
		}
	}
}

void NTMapLayer::createBaseMap()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	iCurrentRoadHigh = 0;
	do
	{
		iCurrentRoadHigh = iCurrentRoadHigh%2;
		NTRoad* pRoad = NTRoad::createRoad(BOX_ROAD_1);
		pRoad->initRoad(BOX_ROAD_1, 12, ROAD_POSY_LOW+iCurrentRoadHigh);
		pRoad->setPosition(ccp(m_fLeftLine+pRoad->getContentSize().width/2, pRoad->getHightLine()-pRoad->getContentSize().height/2));
		m_pBoxArray->addObject(pRoad);
		m_pBoxBatchNode->addChild(pRoad, GAME_MAP_ROAD);
		m_fLeftLine+=pRoad->getContentSize().width-34;
		iCurrentRoadHigh++;

	} while (m_fLeftLine<=winSize.width*1.0f);
	
}


bool NTMapLayer::createBoxInRect( CCPoint pStartPos, CCPoint pEndPos, bool bForce )
{
	//根据道路等级判断是否出现金币堆
	if(CCRANDOM_0_1()>coin_show_probability[m_iMapLevel] && !bForce){
		return false;
	}

	//可以摆几个图案
	int iCountCrowd = ((int)(pEndPos.x-pStartPos.x))/((int)COIN_POS_DATA);
	iCountCrowd = iCountCrowd>2?iCountCrowd-2:0;
	CCPoint pCenterPos = ccpMidpoint(pEndPos, pStartPos);
	float fCrowdAllLength = COIN_POS_DATA*iCountCrowd;

// 	//如果过多则不生成
// 	if(iCountCrowd>5){
// 		return false;
// 	}
	//如果是5,则打出HAPPY
	const char words[6] = "HAPPY";

#if TEST_MODE
	cclogCurTime();
#endif
	for(unsigned int i=0; i<iCountCrowd; i++){
		CCPoint pStart = ccp(pCenterPos.x-fCrowdAllLength/2+COIN_POS_DATA*i, pCenterPos.y);
		int iType = ((int)(CCRANDOM_0_1()*100))%10+COIN_PICTURE_START;
		if(iCountCrowd==5)
		{
			iType = GET_LETTER_COIN_INDEX_BY_ASCALL(words[i]);
		}
		createBoxCrowd(pStart, iType);
	}
#if TEST_MODE
	cclogCurTime();
#endif
	return true;
}

void NTMapLayer::createBoxCrowd( CCPoint pStartPos, int iType )
{
	//CSJson::Value pWordsJson=  NTSharedJsonData::sharedJsonData()->getJsonContent();
	for(int i=COIN_HEIGHT_COUNT-1; i>=0; i--){
		for(unsigned int j=0; j<COIN_WIDTH_COUNT; j++){
			
			//普通金币
			if(NTSharedJsonData::sharedJsonData()->getPosValue(iType,i,j) == 1){
				NTBox* pBox = createBoxWithType(BOX_COIN);
				pBox->setPosition(ccpAdd(pStartPos, ccp(j*COIN_GAP, (COIN_HEIGHT_COUNT-1-i)*COIN_GAP)));				
				m_pBoxBatchNode->addChild(pBox, 20);
			}
			//随机BUFF，根据概率出
			else if(NTSharedJsonData::sharedJsonData()->getPosValue(iType,i,j)==2){
				//可以出现BUFF
				if(CCRANDOM_0_1()<buff_show_probability[m_iMapLevel]){
					NTBox* pBox = createBoxWithType(getRandomBuffInBoxCrowd());
					pBox->setPosition(ccpAdd(pStartPos, ccp(j*COIN_GAP, (COIN_HEIGHT_COUNT-1-i)*COIN_GAP)));	
					m_pBoxBatchNode->addChild(pBox, 21);
				}
				//不出现buff,则照常放金币
				else{
					NTBox* pBox = createBoxWithType(BOX_COIN);
					pBox->setPosition(ccpAdd(pStartPos, ccp(j*COIN_GAP, (COIN_HEIGHT_COUNT-1-i)*COIN_GAP)));				
					m_pBoxBatchNode->addChild(pBox, 20);
				}
				
			}
		}
	}
}

int NTMapLayer::getRandomBuffInBoxCrowd()
{
	float fRandom = CCRANDOM_0_1();
	for(unsigned int i=0; i<BOX_BUFF_END-BOX_BUFF_START-1; i++){
		if(fRandom<=buff_type_probability[i]){
			return BOX_BUFF_START+i+1;
		}
	}
}


void NTMapLayer::addGameCoinInSin(CCPoint pos, float sinMAX, float length, float fSinOffx, bool bWithBuff){
	int offx=COIN_GAP;
	float sinOffx = 3.14/(length/offx);
	if(fSinOffx!=0){
		sinOffx = fSinOffx;
	}
	int i=0;
	do 
	{

		NTBox* pProp = createBoxWithType(BOX_COIN);
		pProp->setPosition(ccp(pos.x +offx*i, pos.y+sinMAX*sin(sinOffx*i)));
		m_pBoxBatchNode->addChild(pProp, 20);	

		i++;
	} while (offx*i<length);

	//可以出现BUFF
	if(CCRANDOM_0_1()<buff_show_probability[m_iMapLevel] && bWithBuff){
		i=i/2;
		NTBox* pBox = createBoxWithType(getRandomBuffInBoxCrowd());
		pBox->setPosition(ccp(pos.x +offx*i, pos.y+sinMAX*sin(sinOffx*i)));	
		m_pBoxBatchNode->addChild(pBox, 21);
	}
}


NTBox* NTMapLayer::createBoxWithType( int pType )
{
	//如果是可回收的
	if(NTBox::isShouldInFreeArray(pType)){
		CCObject* pObj;
		CCARRAY_FOREACH(m_pBoxFreeArray, pObj){
			NTBox* pBox = (NTBox*)pObj;
			if(pBox->getType()==pType){
				m_pBoxArray->addObject(pBox);
				m_pBoxFreeArray->removeObject(pBox);
				return pBox;
			}else{
				CCLOG("-----------------------------------------------------------%d", pBox->getType());
			}
		}
	}

	NTBox* pBox = NTBox::createBox(pType);
	pBox->setMapLayer(this);
	m_pBoxArray->addObject(pBox);
	return pBox;
}

NTRoad* NTMapLayer::createRoad()
{
	//当前的高度
	iCurrentRoadHigh = iCurrentRoadHigh%3;
	int iMaxRoad = road_data[getMapLevel()][20][0];
	int iRandomIndex = ((int)(CCRANDOM_0_1()*100))%20;
	//如果上一个是空隙，且当前是空隙,重新选择一个道路
	if(iCurrentBlank==1 && iRandomIndex>iMaxRoad){
		iRandomIndex = ((int)(CCRANDOM_0_1()*100))%(iMaxRoad+1);
	}
	int iType = road_data[getMapLevel()][iRandomIndex][0];
	int iLength = road_data[getMapLevel()][iRandomIndex][1];

	NTRoad* pRoad = NTRoad::createRoad(iType);

	//如果当前是空隙
	if(iType==ROAD_BLANK){
		iCurrentBlank = 1;

		pRoad->setType(ROAD_BLANK);
		pRoad->setRoadLength(iLength/50);
		pRoad->setHightLine(road_posy[iCurrentRoadHigh]);
		pRoad->setContentSize(CCSizeMake(iLength, 32));
		pRoad->setPosition(ccp(iLength/2+m_fLeftLine, road_posy[iCurrentRoadHigh]));
		m_fLeftLine+=pRoad->getContentSize().width;

	}
	//是真实的道路
	else{
		iCurrentBlank = 0;

		pRoad->initRoad(iType, iLength, ROAD_POSY_LOW+iCurrentRoadHigh);
		pRoad->setPosition(ccp(m_fLeftLine+pRoad->getContentSize().width/2, pRoad->getHightLine()-pRoad->getContentSize().height/2));
		m_pBoxArray->addObject(pRoad);
		m_pBoxBatchNode->addChild(pRoad, GAME_MAP_ROAD);
		m_fLeftLine+=pRoad->getContentSize().width-34;
	}

	//高度随机
	if(CCRANDOM_0_1()>0.5f){
		iCurrentRoadHigh+=1;
	}else{
		iCurrentRoadHigh+=2;
	}

	return pRoad;
}


void NTMapLayer::reset()
{
	m_fSpeed = BASE_SPEED;
}

void NTMapLayer::extraSpeed( float dt, int iAdd)
{
	//结束上一次的加速，重新开始加速计时
	if(getActionByTag(MAP_ACTION_EXTRASPEED)!=NULL){
		stopActionByTag(MAP_ACTION_EXTRASPEED);
		extraSpeedCallBack();
	}

	m_fSpeedExtra = iAdd;
	m_fSpeed += m_fSpeedExtra;
	CCSequence* seq = CCSequence::createWithTwoActions(
		CCDelayTime::create(dt), 
		CCCallFunc::create(this, callfunc_selector(NTMapLayer::extraSpeedCallBack)));
	seq->setTag(MAP_ACTION_EXTRASPEED);
	runAction(seq);
}

void NTMapLayer::extraSpeedCallBack()
{
	m_fSpeed -= m_fSpeedExtra;
	m_fSpeedExtra = 0;
}

void NTMapLayer::showSuperMode()
{
	runAction(CCCallFunc::create(this, callfunc_selector(NTMapLayer::showSuperModeCallBack)));
}

void NTMapLayer::showSuperModeCallBack()
{
	createMapForSupperMode();
}

void NTMapLayer::createMapForSupperMode()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	if(m_fLeftLine>=winSize.width*10){
		return;
	}

// 	//移除图块，使leftLine到屏幕左边缘
// 	CCObject* pObj;
// 	CCArray* pArrayRemvo = CCArray::create();
// 	CCARRAY_FOREACH(m_pBoxArray, pObj){
// 		NTBox* pBox = (NTBox*)pObj;
// 		CCPoint pPOS = pBox->getLeftPos();
// 		pBox->removeFromParentAndCleanup(false);
// 		m_pBoxFreeArray->addObject(pBox);
// 		pArrayRemvo->addObject(pBox);
// 	}
// 	m_pBoxArray->removeObjectsInArray(pArrayRemvo);
// 	m_fLeftLine = 0;

	//生成道路
	iCurrentRoadHigh = ROAD_POSY_HIGH;
	NTRoad* pRoad = NTRoad::createRoad(BOX_ROAD_2);
	pRoad->initRoad(BOX_ROAD_2, 20, ROAD_POSY_LOW+iCurrentRoadHigh);
	pRoad->setContentSize(CCSizeMake(pRoad->getLengthLine(), 32));
	pRoad->setPosition(ccp(m_fLeftLine+pRoad->getContentSize().width/2, pRoad->getContentSize().height/2+280));
	m_pBoxArray->addObject(pRoad);
	m_pBoxBatchNode->addChild(pRoad, GAME_MAP_ROAD);

	NTRoad* pRoadLow = NTRoad::createRoad(BOX_ROAD_1);
	pRoadLow->initRoad(BOX_ROAD_1, 20, ROAD_POSY_LOW);
	pRoadLow->setPosition(ccp(m_fLeftLine+pRoadLow->getContentSize().width/2, pRoadLow->getHightLine()-pRoadLow->getContentSize().height/2));
	m_pBoxArray->addObject(pRoadLow);
	m_pBoxBatchNode->addChild(pRoadLow, GAME_MAP_ROAD);


	//生成磁铁
	int iCountMagnet = 1;
	for(unsigned int i=0; i<iCountMagnet; i++){
		NTBox* pBox = createBoxWithType(BOX_MAGNET);
		pBox->setPosition(ccp(m_fLeftLine+pRoad->getContentSize().width*0.2f, 
			pRoad->getContentSize().height+150+280));				
		m_pBoxBatchNode->addChild(pBox, 10);
	}

	//生成金币
	int iCoinCount = pRoad->getRoadLength()*2;
	for(unsigned int i=0; i<iCoinCount; i++){

		NTBox* pBox1 = createBoxWithType(BOX_COIN);
		pBox1->setPosition(ccp(pRoad->getPositionX()+pBox1->getContentSize().width*(i+0.5f-iCoinCount/2), 
			pRoad->getContentSize().height+100+280));		
		m_pBoxBatchNode->addChild(pBox1, 20);

		NTBox* pBox2 = createBoxWithType(BOX_COIN);
		pBox2->setPosition(ccp(pRoad->getPositionX()+pBox2->getContentSize().width*(i+0.5f-iCoinCount/2), 
			pRoad->getContentSize().height+50+280));				
		m_pBoxBatchNode->addChild(pBox2, 20);

		NTBox* pBox3 = createBoxWithType(BOX_COIN);
		pBox3->setPosition(ccp(pRoad->getPositionX()+pBox2->getContentSize().width*(i+0.5f-iCoinCount/2), 
			pRoad->getContentSize().height-50+280));				
		m_pBoxBatchNode->addChild(pBox3, 20);
	}


	m_fLeftLine+=pRoadLow->getContentSize().width;
	iCurrentRoadHigh++;
}

void NTMapLayer::addProps( int iType, CCPoint pPos )
{
	NTBox* pBox = createBoxWithType(iType);
	pBox->setPosition(pPos);				
	m_pBoxBatchNode->addChild(pBox, 10);
}


void NTMapLayer::shake(float dt) {
	if(m_bIsShake) {
		return;
	}

	m_bIsShake = true;
	this->setScale(1.05f);
	this->runAction(
		CCSequence::create(
		CCShake::create(dt, 3),
		/*		CCShake::createWithStrength(1.0f,0,20),*/
		CCCallFunc::create(this, callfunc_selector(NTMapLayer::resetShake)),
		NULL));
}

void NTMapLayer::resetShake() {
	this->setScale(1.0);
	this->setPosition(CCPointZero);
	m_bIsShake = false;
}

void NTMapLayer::updateMapLevel()
{
	m_iMapLevel = (m_fLength/800)/20;
	m_iMapLevel = m_iMapLevel>ROAD_HARD_LEVEL_9000?ROAD_HARD_LEVEL_9000:m_iMapLevel;
}

void NTMapLayer::showSpecialHit(CCPoint pPos)
{
	showLightPre(pPos);
}

void NTMapLayer::showLightPre(CCPoint pPos)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pLight = CCSprite::createWithSpriteFrameName("PPlane11.png");
	pLight->setPosition(ccp(winSize.width/2, pPos.y));
	this->addChild(pLight);
	pLight->setOpacity(0);
	pLight->runAction(CCSequence::create(
		CCDelayTime::create(1.0f),
		CCFadeIn::create(0.2f),
		CCFadeOut::create(0.6f),
		CCCallFuncN::create(this, callfuncN_selector(NTMapLayer::showLightPreCallBack)),
		CCCallFuncN::create(this, callfuncN_selector(NTMapLayer::removeSelfCallBack)),
		NULL));
}

void NTMapLayer::showLightPreCallBack(CCNode* pSender)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	NTBox* pFlyBlock = createBoxWithType(BOX_FLY_BLOCK);
	pFlyBlock->setPosition(ccp(winSize.width, pSender->getPositionY()));
	pFlyBlock->setSpeedScale(1.5f);
	pFlyBlock->showSelfEffect(0.1f);
	m_pBoxBatchNode->addChild(pFlyBlock, 20);
}


void NTMapLayer::createBlockOnAir(CCPoint pPos)
{
	//砖头，或者打金币，或者冰箱
	int iType;
	CCPoint pPosAdd;
	switch(((int)(CCRANDOM_0_1()*10))%3)
	{
		case 0:
			{
				iType = BOX_BRICK;
				pPosAdd = ccp(0, 0);
			}break;
		case 1:
			{
				iType = BOX_SUPER_COIN;
				pPosAdd = ccp(0, 100);
			}break;
		case 2:
			{
				iType = BOX_ICE_BOX;
				pPosAdd = ccp(0, 0);
			}break;
	}
	NTBox* pFlyBlock = createBoxWithType(iType);
	pFlyBlock->setPosition(ccpAdd(pPos, pPosAdd));
	m_pBoxBatchNode->addChild(pFlyBlock, 20);
}

void NTMapLayer::createBlockOnRoad( NTRoad* pRoad )
{

}


void NTMapLayer::showGoldArea()
{
	m_bSuperMode = true;
	m_bIsMapStop=true;

	//
	m_pSuperModeLight->setVisible(true);
	m_pSuperModeLight->setOpacity(255);
	m_pSuperModeLight->setScale(4.0f);
	m_pSuperModeLight->runAction(CCSpawn::createWithTwoActions(CCFadeOut::create(2.5f), CCScaleTo::create(2.5f, 15.0f)));

	m_pSkyBg->setVisible(true);
	m_pSkyBg->setOpacity(255);
	m_pSkyBg->runAction(CCSequence::create(
		CCDelayTime::create(2.0f),
		CCCallFunc::create(this, callfunc_selector(NTMapLayer::showGoldAreaCallBack)),
		CCFadeOut::create(0.5f), 
		NULL));

	CCSprite* pStartSuper = CCSprite::createWithSpriteFrameName("eff_wz_cjjl1.png");
	pStartSuper->setPosition(ccp(800+pStartSuper->getContentSize().width/2, 240));
	this->getParent()->addChild(pStartSuper, 1200);
	CCSprite* pStarSuperBack = CCSprite::createWithSpriteFrameName("eff_wz_cjjl0.png");
	pStarSuperBack->setPosition(ccp(pStartSuper->getContentSize().width/2, pStartSuper->getContentSize().height/2));
	pStartSuper->addChild(pStarSuperBack);
	pStarSuperBack->runAction(CCRepeatForever::create(CCBlink::create(0.5f, 3)));

	pStartSuper->runAction(CCSequence::create(
		CCEaseSineOut::create(CCMoveTo::create(0.4f, ccp(400, 240))),
		CCDelayTime::create(1.1f),
		CCEaseSineIn::create(CCMoveTo::create(0.4f, ccp(-pStartSuper->getContentSize().width/2, 240))),
		CCCallFuncN::create(this, callfuncN_selector(NTMapLayer::removeSelfCallBack)),
		NULL));
}

void NTMapLayer::showGoldAreaCallBack()
{
	m_bIsMapStop=false;

	//隐藏之前的滚动背景
	for(unsigned int i=0; i<6; i++){
		m_pAutoBg[i]->setVisible(false);
	}
	m_pSkyBg->setVisible(false);
	for(unsigned int i=6; i<8; i++){
		m_pAutoBg[i]->setVisible(true);
	}
	//移除图块，使leftLine到屏幕左边缘
	resetLeftLine();
	m_fGoldAreaLine1 = 0;
	m_fGoldAreaLine2 = 0;
	m_fGoldAreaLine3 = 0;

	addGoldRoad();
}


void NTMapLayer::addGoldRoad()
{
	//生成道路
	NTRoad* pRoadLow = NTRoad::createRoad(BOX_ROAD_3);
	pRoadLow->initRoad(BOX_ROAD_3, 4, ROAD_POSY_HIGH);
	pRoadLow->setPosition(ccp(m_fLeftLine+pRoadLow->getContentSize().width/2, pRoadLow->getHightLine()-pRoadLow->getContentSize().height/2));
	pRoadLow->setIsCanStand(false);
	m_pBoxArray->addObject(pRoadLow);
	m_pBoxBatchNode->addChild(pRoadLow, GAME_MAP_ROAD);
	m_fLeftLine+=pRoadLow->getContentSize().width;

	//添加1层背景物品
	int iRandN1 = ((int)(CCRANDOM_0_1()*100))%5;
	bool bGap1 = CCRANDOM_0_1()>0.5f?true:false;
	m_fGoldAreaLine1 += bGap1?CCRANDOM_0_1()*200:0;
	for(unsigned int i=0; i<iRandN1; i++){
		NTBox* pBox = createBoxWithType(BOX_GOLDAREA_PROP1);
		pBox->setPosition(ccp(m_fGoldAreaLine1, 334));		
		m_pBoxBatchNode->addChild(pBox, GAME_MAP_AUTO_BG+2);
		pBox->setSpeedScale(autoBgSpeedScale[3]);
		m_fGoldAreaLine1 += pBox->getContentSize().width;
	}
	//添加2层背景物品
	int iRandN2 = ((int)(CCRANDOM_0_1()*100))%5;
	bool bGap2 = CCRANDOM_0_1()>0.5f?true:false;
	m_fGoldAreaLine2 += bGap2?CCRANDOM_0_1()*200:0;
	for(unsigned int i=0; i<iRandN2; i++){
		NTBox* pBox = createBoxWithType(BOX_GOLDAREA_PROP2);
		pBox->setPosition(ccp(m_fGoldAreaLine2, 214));				
		m_pBoxBatchNode->addChild(pBox, GAME_MAP_AUTO_BG+3);
		pBox->setSpeedScale(autoBgSpeedScale[3]);
		m_fGoldAreaLine2 += pBox->getContentSize().width;
	}
	//添加3层背景物品
	int iRandN3 = ((int)(CCRANDOM_0_1()*100))%5;
	bool bGap3 = CCRANDOM_0_1()>0.5f?true:false;
	m_fGoldAreaLine3 += bGap3?CCRANDOM_0_1()*200:0;
	for(unsigned int i=0; i<iRandN3; i++){
		NTBox* pBox = createBoxWithType(CCRANDOM_0_1()>0.5f?BOX_GOLDAREA_PROP3:BOX_GOLDAREA_PROP4);
		pBox->setPosition(ccp(m_fGoldAreaLine3, 143));				
		m_pBoxBatchNode->addChild(pBox, GAME_MAP_AUTO_BG+4);
		pBox->setSpeedScale(autoBgSpeedScale[3]);
		m_fGoldAreaLine3 += pBox->getContentSize().width;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_fGoldAreaLine1 = m_fGoldAreaLine1<winSize.width?winSize.width:m_fGoldAreaLine1;
	m_fGoldAreaLine2 = m_fGoldAreaLine2<winSize.width?winSize.width:m_fGoldAreaLine2;
	m_fGoldAreaLine3 = m_fGoldAreaLine3<winSize.width?winSize.width:m_fGoldAreaLine3;

	//添加金币
// 	createBoxInRect(
// 		ccp(pRoadLow->getLeftPos().x, pRoadLow->getHightLine()+100), 
// 		ccp(pRoadLow->getRightPos().x, pRoadLow->getHightLine()+100),
// 		true);
	addGameCoinInSin(ccpAdd(ccp(pRoadLow->getLeftPos().x, pRoadLow->getHightLine()), ccp(0, 90)), 
		20, pRoadLow->getContentSize().width-22, 0.5f, false
		);
	addGameCoinInSin(ccpAdd(ccp(pRoadLow->getLeftPos().x, pRoadLow->getHightLine()), ccp(0, 150)), 
		20, pRoadLow->getContentSize().width-22, -0.5f, false
		);
	addGameCoinInSin(ccpAdd(ccp(pRoadLow->getLeftPos().x, pRoadLow->getHightLine()), ccp(0, 40)), 
		5, pRoadLow->getContentSize().width-22, 0.001f, false
		);
}

void NTMapLayer::fromGoldAreaBackToNormalRoad()
{
	//隐藏之前的滚动背景
	for(unsigned int i=0; i<6; i++){
		m_pAutoBg[i]->setVisible(true);
	}
	m_pSkyBg->setVisible(false);
	for(unsigned int i=6; i<8; i++){
		m_pAutoBg[i]->setVisible(false);
	}
	m_bSuperMode = false;

	resetLeftLine();

	createBaseMap();
}

void NTMapLayer::showEffect( CCPoint pPos, int iType )
{
	m_pEffectLayer->playAnimateForBomb(pPos, iType);
}

void NTMapLayer::showGuideRoad()
{
	resetLeftLine();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	iCurrentRoadHigh = 0;
	iCurrentRoadHigh = iCurrentRoadHigh%2;
	NTRoad* pRoad = NTRoad::createRoad(BOX_ROAD_1);
	pRoad->initRoad(BOX_ROAD_1, 25, ROAD_POSY_LOW+iCurrentRoadHigh);
	pRoad->setPosition(ccp(m_fLeftLine+pRoad->getContentSize().width/2, pRoad->getHightLine()-pRoad->getContentSize().height/2));
	m_pBoxArray->addObject(pRoad);
	m_pBoxBatchNode->addChild(pRoad, GAME_MAP_ROAD);
	m_fLeftLine+=pRoad->getContentSize().width-34;
	iCurrentRoadHigh++;

	//路面弹簧
	int iBlockCount = ((int)(CCRANDOM_0_1()*10))%pRoad->getRoadLength();
	int iType = BOX_SPRING;
	NTBox* pBox = createBoxWithType(iType);
	pBox->setPosition(ccp(pRoad->getLeftPos().x+pRoad->getContentSize().width*0.4f, 
		pRoad->getHightLine()+pBox->getContentSize().height/2-12));
	m_pBoxBatchNode->addChild(pBox, 15);

	//生成钩子
	int iCountHook = 5;
	iType = BOX_HOOK3;
	for(unsigned int i=0; i<iCountHook; i++){
		NTBox* pBox = createBoxWithType(iType);
		pBox->setPosition(ccp(pRoad->getLeftPos().x+pRoad->getContentSize().width*0.6f+pBox->getContentSize().width*i, 
			pRoad->getHightLine()+pBox->getContentSize().height/2+ACTOR_STAND_MIN_HIGH));				
		m_pBoxBatchNode->addChild(pBox, 15);
		pBox->showSelfEffect(0.1f*i);
	}
}

void NTMapLayer::resetLeftLine()
{
	//移除图块，使leftLine到屏幕左边缘
	CCObject* pObj;
	CCArray* pArrayRemvo = CCArray::create();
	CCARRAY_FOREACH(m_pBoxArray, pObj){
		NTBox* pBox = (NTBox*)pObj;
		CCPoint pPOS = pBox->getLeftPos();
		pBox->removeFromParentAndCleanup(false);
		if(pBox->isShouldInFreeArray()){
			m_pBoxFreeArray->addObject(pBox);
		}
		pArrayRemvo->addObject(pBox);
	}
	m_pBoxArray->removeObjectsInArray(pArrayRemvo);
	m_fLeftLine = 0;
}

void NTMapLayer::removeSelfCallBack( CCNode* pSender )
{
	pSender->removeFromParentAndCleanup(true);
}















































