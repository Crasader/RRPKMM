
#include "NTGameGuide.h"
#include "NTMenuItem.h"

#define GUIDE_LAYER_LIGHT	102
#define GUIDE_LAYER_HUD	101


float GUIDE_MOVE_GAP = 0.02f;



NTGameGuide::NTGameGuide()
{
	m_pPointArray = CCArray::create();
	m_pPointArray->retain();
	m_iPointIndex=0;
	m_pVirtualTouch = NULL;
}

NTGameGuide::~NTGameGuide()
{
	CC_SAFE_RELEASE(m_pPointArray);
	CC_SAFE_RELEASE(m_pVirtualTouch);
}


// on "init" you need to initialize your instance
bool NTGameGuide::init() {
	bool bRet = false;
	do {
		CC_BREAK_IF(! CCLayer::init());

		m_pControlLayer = NULL;		
		
		bRet = true;
	} while (0);

	return bRet;
}


void NTGameGuide::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

void NTGameGuide::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, PRIORITY_NTLAYER_GUIDE, true);
}

void NTGameGuide::onEnterTransitionDidFinish()
{

	CCLayer::onEnterTransitionDidFinish();

	this->addChild(CCLayer::create(), GUIDE_LAYER_LIGHT, GUIDE_LAYER_LIGHT);

	initLightLayer();

	m_pVirtualTouch = new CCTouch();
}



void NTGameGuide::initLightLayer()
{
	CCLayer* layer = (CCLayer*)getChildByTag(GUIDE_LAYER_LIGHT);
	
	//箭头
	m_pArrow = CCSprite::create("guide/help_Index3.png");
	m_pArrow->setVisible(false);
	layer->addChild(m_pArrow);

	//手
	m_pHand = CCSprite::create("guide/help_Index1 .png");
	m_pHand->setAnchorPoint(ccp(0.5f, 1.0f));
	m_pHand->setVisible(false);
	layer->addChild(m_pHand);

	//发光
	m_pBlinkLight = CCSprite::create("guide/help_Index2.png");
	m_pBlinkLight->setVisible(false);
	layer->addChild(m_pBlinkLight);

	//数据状态
	initValue();

	initArrayBatchNode();
}

void NTGameGuide::initValue()
{
	m_pArrowBatchNode = NULL;
	setTouchLock(false);
	setGuideLock(false);
	m_iGuideMode = GUIDE_TYPE_TAP;
}



void NTGameGuide::hideHandAndArrow()
{
	m_pArrow->stopAllActions();
	m_pHand->stopAllActions();
	m_pBlinkLight->stopAllActions();
	m_pArrow->setVisible(false);
	m_pHand->setVisible(false);
	m_pBlinkLight->setVisible(false);
}



bool NTGameGuide::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_bTouchLock){
		return true;
	}
	return false;
}

void NTGameGuide::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_bTouchLock){
		return;
	}
}

void NTGameGuide::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_bTouchLock){
		return;
	}
}

void NTGameGuide::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	if(pEvent!=NULL){
		return;
	}
}


void NTGameGuide::showMsgBox(int pType)
{
	m_pControlLayer->pauseGameAll(true);
	char name[40];
	sprintf(name, "guide/set_xs_wz%d.png", pType-_GS_GUIDE_JUMP);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	NTMessageBox* pLayer = NTMessageBox::create();
	pLayer->setTag( GameLayerMSG );
	pLayer->setColor(ccc3(0,0,0));
	pLayer->setOpacity(160);
	this->addChild( pLayer,GameLayerMSG);

	//背景框
	CCSprite* pTextBg = CCSprite::create("guide/set_xs_db.png");
	pTextBg->setPosition(ccp(400, winSize.height-224));
	pLayer->addChild(pTextBg);
	//文字
	CCSprite* pText = CCSprite::create(name);
	pText->setPosition(ccp(400, winSize.height-206));
	pLayer->addChild(pText);
	//按钮
	CCSprite *normal=CCSprite::create("guide/set_qd.png");
	CCSprite* sel=CCSprite::create("guide/set_qd.png");
	sel->setScale(0.9f);
	NTMenuItemSprite* okMenuItem = NTMenuItemSprite::create(
		normal,
		sel,
		NULL, this, menu_selector(NTGameGuide::messageOkCallBack));
	okMenuItem->setPosition(ccp(400, winSize.height-290));
	pLayer->setSeletor(okMenuItem, NULL);

}

void NTGameGuide::messageOkCallBack( CCObject * pSender )
{
	this->removeChildByTag( GameLayerMSG, true );
	m_pControlLayer->pauseGameAll(false);
	showGuide();
}



bool NTGameGuide::runGuide(int pType, 
	CCTouchDelegate* pTouchLayer, CCPoint pStart, CCPoint pEnd, 
	float pDelayTime, CCAction* pActionCallBack, int iGuideMode, CCArray* pPointArray)
{
	if(getGuideLock()){
		return false;
	}else{

		if(pPointArray!=NULL){
			m_pPointArray->removeAllObjects();
			m_pPointArray->addObjectsFromArray(pPointArray);
			m_iPointIndex=1;
		}

		m_iGuideMode = iGuideMode;

		setTouchLock(true);

		//设置数据
		setGuideType(pType);
		if(pTouchLayer!=NULL){
			setTouchLayer(pTouchLayer);
		}else{
			setTouchLayer(this);
		}
		
		setStartToAdd(pStart);
		setTouchStart(pStart);
		setTouchEnd(pEnd);
		setDelayTime(pDelayTime);
		setGuideOverCallBack(pActionCallBack);
		pActionCallBack->retain();

		showMsgBox(getGuideType());

		return true;
	}
}

void NTGameGuide::showGuide()
{
	switch(m_iGuideMode)
	{
		case GUIDE_TYPE_TAP:showTapGuide();break;
		case GUIDE_TYPE_LONG_TAP:showLongTapGuide();break;
		case GUIDE_TYPE_MOVE:showMoveGuide();break;
		case GUIDE_TYPE_DRAW:showDrawGuide();break;
	}
	this->runAction(CCSequence::create(
		CCDelayTime::create(getDelayTime()+0.1f),
		CCCallFunc::create(this, callfunc_selector(NTGameGuide::showGuideCallBack)),
		getGuideOverCallBack(),
		NULL));
}


void NTGameGuide::showTapGuide()
{

	CCPoint pPos = getTouchStart();
	m_pHand->setVisible(true);
	m_pHand->setRotation(-135);
	m_pBlinkLight->setVisible(true);
	m_pHand->setPosition(ccpAdd(pPos, ccp(0,5)));
	m_pBlinkLight->setPosition(pPos);


	m_pHand->runAction(CCSequence::create(
		CCCallFunc::create(this, callfunc_selector(NTGameGuide::showTapTouch)),
		CCFadeIn::create(0.1f),
		CCDelayTime::create(1.1f),
		CCFadeOut::create(0.15f),
		CCCallFunc::create(this, callfunc_selector(NTGameGuide::hideHandAndArrow)),
		NULL
		));
	m_pBlinkLight->runAction(CCSequence::create(
		CCFadeOut::create(0.0f),
		CCDelayTime::create(0.2f),
		CCFadeIn::create(0.0f),
		CCBlink::create(0.8f, 5),
		CCFadeOut::create(0.0f),
		NULL
		));
}


void NTGameGuide::showLongTapGuide()
{
	CCPoint pPos = getTouchStart();
	m_pHand->setVisible(true);
	m_pHand->setRotation(-135);
	m_pBlinkLight->setVisible(true);
	m_pHand->setPosition(ccpAdd(pPos, ccp(0,5)));
	m_pBlinkLight->setPosition(pPos);


	m_pHand->runAction(CCSequence::create(
		CCFadeIn::create(0.2f),
		CCCallFunc::create(this, callfunc_selector(NTGameGuide::showLongTapTouch)),
		CCDelayTime::create(getDelayTime()),
		CCCallFunc::create(this, callfunc_selector(NTGameGuide::showLongTapTouchCallBack)),
		CCFadeOut::create(0.15f),
		CCCallFunc::create(this, callfunc_selector(NTGameGuide::hideHandAndArrow)),
		NULL
		));
	m_pBlinkLight->runAction(CCSequence::create(
		CCFadeOut::create(0.0f),
		CCDelayTime::create(0.2f),
		CCFadeIn::create(0.0f),
		CCBlink::create(getDelayTime(), 5),
		CCFadeOut::create(0.0f),
		NULL
		));
}

void NTGameGuide::showLongTapTouch()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_pVirtualTouch->setTouchInfo(0, getTouchStart().x, winSize.height-getTouchStart().y);

	getTouchLayer()->ccTouchBegan(m_pVirtualTouch, NULL);
	
}


void NTGameGuide::showLongTapTouchCallBack()
{
	getTouchLayer()->ccTouchEnded(m_pVirtualTouch, NULL);
}


void NTGameGuide::showMoveGuide()
{
	setGap(ccpNormalize(ccpSub(m_pEnd, m_pStart)));

	moveHandWithArrayPoint(m_pPointArray);

	showArrowWithArrayPoint(m_pPointArray);

	this->runAction(CCSequence::create(
		CCDelayTime::create(GUIDE_ARROW_SHOW_DELAY+GUIDE_ARROW_SHOW_GAP*m_pPointArray->count()),
		CCCallFunc::create(this, callfunc_selector(NTGameGuide::showDragTouch)),NULL));

}

void NTGameGuide::showDrawGuide()
{
// 	m_pArrow->setVisible(true);
// 	m_pHand->setVisible(true);
// 	m_pHand->setPosition(pPosStart);
// 	m_pHand->setRotation(CC_RADIANS_TO_DEGREES(ccpToAngle(getGap())));
// 
// 	m_pArrow->setPosition(ccpAdd(pPosStart, ccp(getGap().x/2, getGap().y/2)));
// 	m_pArrow->setRotation(90-CC_RADIANS_TO_DEGREES(ccpToAngle(getGap())));
// 
// 
// 	m_pArrow->runAction(CCSequence::create(
// 		CCFadeIn::create(0.9f),
// 		CCFadeOut::create(0.1f),
// 		CCCallFunc::create(this, callfunc_selector(NTGameGuide::showDragTouch)),
// 		CCCallFunc::create(this, callfunc_selector(NTGameGuide::hideHandAndArrow)),
// 		NULL
// 		));

	showDragTouch();
}


void NTGameGuide::showTapTouch()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_pVirtualTouch->setTouchInfo(0, getTouchStart().x, winSize.height-getTouchStart().y);

	getTouchLayer()->ccTouchBegan(m_pVirtualTouch, NULL);
	getTouchLayer()->ccTouchEnded(m_pVirtualTouch, NULL);
}



void NTGameGuide::showDragTouch()
{
	if(m_pPointArray==NULL){
		return;
	}
	changePoint();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_pVirtualTouch->setTouchInfo(0, m_pStart.x, winSize.height-m_pStart.y);
	getTouchLayer()->ccTouchBegan(m_pVirtualTouch, NULL);

	GUIDE_MOVE_GAP = 1000;
	unschedule(schedule_selector(NTGameGuide::updateForTouchMove));
	schedule(schedule_selector(NTGameGuide::updateForTouchMove));
}


void NTGameGuide::updateForTouchMove( float dt )
{
	m_pStartToAdd = ccpAdd(m_pStartToAdd, ccp(getGap().x*GUIDE_MOVE_GAP*dt, getGap().y*GUIDE_MOVE_GAP*dt));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	m_pVirtualTouch->setTouchInfo(0, m_pStartToAdd.x, winSize.height-m_pStartToAdd.y);

	if(fabs(ccpSub(m_pEnd, m_pStart).x)<=fabs(ccpSub(m_pStartToAdd, m_pStart).x)){
		if(!changePoint()){
			unschedule(schedule_selector(NTGameGuide::updateForTouchMove));
			getTouchLayer()->ccTouchEnded(m_pVirtualTouch, NULL);
			showGuideCallBack();
		}else{
			getTouchLayer()->ccTouchMoved(m_pVirtualTouch, NULL);
			changePoint(m_pStartToAdd);
		}
	}else
	{
		getTouchLayer()->ccTouchMoved(m_pVirtualTouch, NULL);
	}

}



void NTGameGuide::showGuideCallBack()
{
	//解锁触摸
	/*setTouchLock(false);*/
	//解锁引导
	setGuideLock(false);
}

bool NTGameGuide::changePoint( CCPoint pStart/*=CCPointZero*/ )
{
	m_iPointIndex++;
	if(m_iPointIndex>=m_pPointArray->count()){
		return false;
	}

	CCNode* pStartNode = (CCNode*)m_pPointArray->objectAtIndex(m_iPointIndex-1);
	CCNode* pEndNode = (CCNode*)m_pPointArray->objectAtIndex(m_iPointIndex);
	if(pStart.equals(CCPointZero)){
		m_pStart = pStartNode->getPosition();
	}else{
		m_pStart = pStart;
	}
	m_pEnd = pEndNode->getPosition();
	setGap(ccpNormalize(ccpSub(m_pEnd, m_pStart)));

	return true;
}


void NTGameGuide::initArrayBatchNode()
{
	m_pArrowBatchNode = CCSpriteBatchNode::create("guide/guide.png");
	this->addChild(m_pArrowBatchNode);
}

void NTGameGuide::showArrowWithArrayPoint( CCArray* pArray )
{
	const char* fileName[2] = {"game_kc_jt0.png", "game_kc_jt1.png"};
	int iCount = pArray->count();
	for(unsigned int i=0; i<iCount-1; i++){
		CCNode* pNodeStart = (CCNode*)pArray->objectAtIndex(i);
		CCNode* pNodeEnd = (CCNode*)pArray->objectAtIndex(i+1);
		CCPoint pStartPos = pNodeStart->getPosition();
		CCPoint pEndPos = pNodeEnd->getPosition();
		CCPoint shootVector = ccpSub(pEndPos, pStartPos);
		float shootAngle = ccpToAngle(shootVector);
		float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);
		float dis = ccpDistance(pStartPos, pEndPos);
		CCSprite* pArraw = CCSprite::createWithSpriteFrameName(i==iCount-2?fileName[1]:fileName[0]);
		pArraw->setAnchorPoint(ccp(0.0f, 0.5f));
		pArraw->setPosition(pStartPos);
		pArraw->setRotation(cocosAngle);
		float scale = (dis/pArraw->getContentSize().width)*0.6f;
 		pArraw->setScaleX(scale>2.0f?2.0f:scale);
// 		pArraw->setScaleY(2.0f);
		m_pArrowBatchNode->addChild(pArraw);
		pArraw->setOpacity(0);
		pArraw->runAction(CCSequence::create(
			CCDelayTime::create(GUIDE_ARROW_SHOW_DELAY*2+GUIDE_ARROW_SHOW_GAP*i), CCFadeIn::create(0.05f),NULL));

		if(i==iCount-2){
			pArraw->setScaleX(1.3f);
		}
	}
	this->runAction(CCSequence::create(
		CCDelayTime::create(GUIDE_ARROW_SHOW_DELAY+GUIDE_ARROW_SHOW_GAP*iCount),
		CCCallFunc::create(this, callfunc_selector(NTGameGuide::showArrowWithArrayPointCallBack)),NULL));
}

void NTGameGuide::showArrowWithArrayPointCallBack()
{
	m_pArrowBatchNode->removeAllChildrenWithCleanup(true);
}

void NTGameGuide::moveHandWithArrayPoint( CCArray* pArray )
{
	CCPoint pPosStart = getTouchStart();
	m_pHand->setVisible(true);
	m_pHand->setPosition(pPosStart);
	int iCount = pArray->count();
	CCPointArray *array = CCPointArray::create(iCount);
	for(unsigned int i=0; i<iCount; i++){
		array->addControlPoint(((CCNode*)pArray->objectAtIndex(i))->getPosition());
	}
	CCCardinalSplineTo *action = CCCardinalSplineTo::create(iCount*GUIDE_ARROW_SHOW_GAP, array, 0);

	CCFiniteTimeAction *seq = CCSequence::create(
		CCDelayTime::create(GUIDE_ARROW_SHOW_DELAY),
		action, 
		CCCallFunc::create(this, callfunc_selector(NTGameGuide::moveHandWithArrayPointCallBack)), 
		NULL);
	m_pHand->runAction(seq);

}

void NTGameGuide::moveHandWithArrayPointCallBack()
{
	m_pHand->setVisible(false);
}




















