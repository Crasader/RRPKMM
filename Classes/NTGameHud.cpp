#include "NTGameHud.h"
#include "NTConstants.h"
#include "NTMessageBox.h"
#include "NTMenuItem.h"
#include "NTGameSave.h"
#include "NTStart.h"
#include "NTGameSound.h"
#include "NTGameScene.h"
#include "NTGift.h"
#include "KickBoss.h"

bool NTGameHud::init()
{
	bool Res = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		initValues();
		initUI();
		Res = true;
	} while (0);

	return Res;
}

void NTGameHud::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, PRIORITY_NTLAYER_UI,true);
}


void NTGameHud::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}


void NTGameHud::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}


void NTGameHud::initValues()
{
	m_bIsTouchMu = false;
	m_pMenu = NULL;
	m_bIsPauseLock = false;
	m_bIsPause = false;
}

void NTGameHud::initUI()
{
	//≥ı ºªØ±≥æ∞“Ù¿÷
    scheduleUpdate();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//∑÷ ˝±≥æ∞£¨¬∑≥Ã±≥æ∞
	CCSprite* pScoreBg = CCSprite::create("game/game_bx.png");
	pScoreBg->setPosition(ccp(111, winSize.height-32.5f));
	this->addChild(pScoreBg);
	CCSprite* pMilesBg = CCSprite::create("game/game_jl.png");
	pMilesBg->setPosition(ccp(370, winSize.height-32.5f));
	this->addChild(pMilesBg);


	//∑÷ ˝
	m_pScoreLabel = CCLabelAtlas::create("0","start/start_jbsz.png",14,21,'0');
    m_pScoreLabel->setScale(0.93f);
	m_pScoreLabel->setPosition(ccp(126, winSize.height-32.5f));
	m_pScoreLabel->setAnchorPoint(ccp(0.5f, 0.5f));
	this->addChild(m_pScoreLabel);
	//¬∑≥Ã
	m_pMilesLabel= CCLabelAtlas::create("0","start/start_jbsz1.png",15,23,'0');
	m_pMilesLabel->setPosition(ccp(383, winSize.height-32.5f));
	m_pMilesLabel->setAnchorPoint(ccp(0.5f, 0.5f));
	this->addChild(m_pMilesLabel);

// 	//ÃÌº”ÕÊº“—™Ãı
// 	CCSprite* playerBloodBg=CCSprite::create("game/game_txdb.png");
// 	playerBloodBg->setPosition(ccp(539, winSize.height-22.5f));
// 	this->addChild(playerBloodBg);
// 	CCSprite* playerBloodFg=CCSprite::create("game/game_txxt.png");
// 	m_pPlayerHp=CCProgressTimer::create(playerBloodFg);
// 	m_pPlayerHp->setType(kCCProgressTimerTypeBar);
// 	m_pPlayerHp->setMidpoint(ccp(0,0)); 
// 	m_pPlayerHp->setBarChangeRate(ccp(1,0));
// 	m_pPlayerHp->setPosition(ccp(557, winSize.height-23.5f));
// 	m_pPlayerHp->setPercentage(100);
// 	this->addChild(m_pPlayerHp);
// 	CCSprite* pPlayerHead = CCSprite::create("game/game_tx4.png");
// 	pPlayerHead->setPosition(ccp(483, winSize.height-22));
// 	this->addChild(pPlayerHead);
// 	//ÃÌº”NPC—™Ãı
// 	CCSprite* pNpcBloodBg=CCSprite::create("game/game_txdb.png");
// 	pNpcBloodBg->setPosition(ccp(539, winSize.height-70));
// 	this->addChild(pNpcBloodBg);
// 	CCSprite* pNpcBloodFg=CCSprite::create("game/game_txxt.png");
// 	m_pNpcHp=CCProgressTimer::create(pNpcBloodFg);
// 	m_pNpcHp->setType(kCCProgressTimerTypeBar);
// 	m_pNpcHp->setMidpoint(ccp(0,0)); 
// 	m_pNpcHp->setBarChangeRate(ccp(1,0));
// 	m_pNpcHp->setPosition(ccp(556, winSize.height-71));
// 	m_pNpcHp->setPercentage(100);
// 	this->addChild(m_pNpcHp);
// 	CCSprite* pNpcHead = CCSprite::create("game/game_tx7.png");
// 	pNpcHead->setPosition(ccp(484, winSize.height-71));
// 	this->addChild(pNpcHead);

	//==================================================================================∞¥≈•
	//‘›Õ£
	NTMenuItemSprite* openPause = NTMenuItemSprite::create(
		CCSprite::create("game/game_zt.png"),
		CCSprite::create("game/game_zt.png"),NULL
		);
	NTMenuItemSprite* closePause = NTMenuItemSprite::create(
		CCSprite::create("game/game_bf.png"),
		CCSprite::create("game/game_bf.png"),NULL
		);
	m_pPauseItem=CCMenuItemToggle::createWithTarget(
		this,menu_selector(NTGameHud::pauseItemCallBack),
		openPause,closePause,NULL);
	m_pPauseItem->setPosition(ccp(770-100, winSize.height-29));

	//∑µªÿ≤Àµ•
	NTMenuItemSprite* backState = NTMenuItemSprite::create(
		CCSprite::create("game/game_zjm.png"),
		CCSprite::create("game/game_zjm.png"),
		NULL,this,menu_selector(NTGameHud::backToStateCallBack)
		);
	backState->setPosition(ccp(770, winSize.height-90));

	//÷ÿ¿¥
	NTMenuItemSprite* replay = NTMenuItemSprite::create(
		CCSprite::create("game/game_chl.png"),
		CCSprite::create("game/game_chl.png"),
		NULL,this,menu_selector(NTGameHud::replayCallBack)
		);
	replay->setPosition(ccp(770, winSize.height-150));

// 	//“Ù¿÷
	NTMenuItemSprite* openMusic = NTMenuItemSprite::create(
		CCSprite::create("game/game_music0.png"),
		CCSprite::create("game/game_music0.png"),NULL
		);
	NTMenuItemSprite* closeMusic = NTMenuItemSprite::create(
		CCSprite::create("game/game_music1.png"),
		CCSprite::create("game/game_music1.png"),NULL
		);
	toggleMusic = CCMenuItemToggle::createWithTarget(
		this,menu_selector(NTGameHud::musicSwitchCallBack),
		openMusic,closeMusic,NULL);
	toggleMusic->setPosition(ccp(770, winSize.height-210));
	if(!NTGameSound::sharedEngine()->isAudioOpen()){
		toggleMusic->setSelectedIndex(1);
//		NTGameSound::sharedEngine()->openAll();
	}

	m_pMenu = CCMenu::create(m_pPauseItem, backState, replay,/* toggleMusic,*/ NULL);
	m_pMenu->setPosition(CCPointZero);
	this->addChild(m_pMenu);
	m_pMenu->setPosition(ccp(100, 0));
}


bool NTGameHud::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (!m_bIsTouchMu)
	{
		m_bIsTouchMu = m_pMenu->ccTouchBegan(pTouch,pEvent);
	}

	return m_bIsTouchMu;
}

void NTGameHud::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchMoved(pTouch,pEvent);
	}
}

void NTGameHud::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchEnded(pTouch,pEvent);
		m_bIsTouchMu = false;
	}
}

void NTGameHud::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchCancelled(pTouch,pEvent);
		m_bIsTouchMu = false;
	}
}
//∏˙–¬∑÷ ˝
void NTGameHud::updateScores( int iScore )
{
	m_pScoreLabel->setString(CCString::createWithFormat("%d", iScore)->getCString());
}

//∏˙–¬æ‡¿Î
void NTGameHud::updateDistance( int iMiles )
{
	m_pMilesLabel->setString(CCString::createWithFormat("%d", iMiles)->getCString());
}
void NTGameHud::updateGameSaveDistance()
{
    CCLog("updateScore");
    int score=NTGameSave::sharedGameSave()->getDataById(_GS_SCORE)+getControlLayer()->m_iScore;
      NTGameSave::sharedGameSave()->updateValue(_GS_SCORE,score);
    switch (NTGameSave::sharedGameSave()->getDataById(_GS_TASKONE)) {
        case 4:
            NTGameSave::sharedGameSave()->updateValue(_GS_TASKONE_FINISH,score>9999?1:0);
            break;
        case 5:
            NTGameSave::sharedGameSave()->updateValue(_GS_TASKONE_FINISH,score>29999?1:0);
            break;
        case 6:
            NTGameSave::sharedGameSave()->updateValue(_GS_TASKONE_FINISH,score>49999?1:0);
            break;
        case 10:
            NTGameSave::sharedGameSave()->updateValue(_GS_TASKONE_FINISH,score>79999?1:0);
            break;
        default:
            break;
    }
}
//∏˙–¬npc—™¡ø
void NTGameHud::updateNpcHp( int iCurrentBlood, int iType)
{
	float percents = 100*iCurrentBlood/actor_data[iType][ACTOR_DATA_HP];
	m_pNpcHp->setPercentage(percents);
}
//∏˙–¬Ω«…´—™¡ø
void NTGameHud::updatePlayerHp( int iCurrentBlood )
{
	float percents = 100*iCurrentBlood/actor_data[ACTOR_1][ACTOR_DATA_HP];
	m_pPlayerHp->setPercentage(percents);
}

//œ‘ æ”Œœ∑Ω· ¯ΩÁ√Ê
void NTGameHud::showGameOverMsg( int iScore, int iMiles )
{
    NTGameSound::sharedEngine()->playEffectById(SOUND_MAP_STEP, true,NTGameSave::sharedGameSave()->isSound);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	 pMsg = NTMessageBox::create();
	this->addChild(pMsg, GameLayerMSG, GameLayerMSG);
	int iCurrentHero = NTGameSave::sharedGameSave()->getHeroSelect();
	int iHeroLevel = NTGameSave::sharedGameSave()->getDataById(_GS_HERO1_LEVEL+iCurrentHero);
	int iCurrentPet = NTGameSave::sharedGameSave()->getHeroPet();
	int iPetLevel = NTGameSave::sharedGameSave()->getDataById(_GS_PET1_LEVEL+iCurrentPet);
	float fAddMarkWithHero = actor_info[iCurrentHero][ACTOR_BASE_EXTRA_MARK]+iHeroLevel*actor_info[iCurrentHero][ACTOR_ADD_EXTRA_MARK];
	float fAddMarkWithPet = iCurrentPet==-1?0:pet_info[iCurrentPet][PET_BASE_EXTRA_MARK]+iPetLevel*pet_info[iCurrentPet][PET_ADD_EXTRA_MARK];

	float fAddGoldWithHero = actor_info[iCurrentHero][ACTOR_BASE_EXTRA_GOLD]+iHeroLevel*actor_info[iCurrentHero][ACTOR_ADD_EXTRA_GOLD];
	float fAddGoldWithPet = iCurrentPet==-1?0:pet_info[iCurrentPet][PET_BASE_EXTRA_GOLD]+iPetLevel*pet_info[iCurrentPet][PET_ADD_EXTRA_GOLD];

	//µ±æ÷∑÷ ˝
	int iTotalScore = iScore*2+iMiles*5;
	iTotalScore += iTotalScore*(fAddMarkWithHero/100);
	iTotalScore += iTotalScore*(fAddMarkWithPet/100);
	int iMaxScore = NTGameSave::sharedGameSave()->getDataById(_GS_MAX_SCORE);
    //Jerry--HeartCount
    int iHeart = NTGameSave::sharedGameSave()->getDataById(_GS_HEART);

	//¥Ê¥¢◊Ó∏ﬂ∑÷
	if(iMaxScore<iTotalScore){
		NTGameSave::sharedGameSave()->updateValue(_GS_MAX_SCORE, iTotalScore);
		iMaxScore = iTotalScore;
	}
	//¥Ê¥¢Ω±“ ˝
	int iAddGold = (iMiles/2);
	iAddGold += iAddGold*(fAddGoldWithHero/100);
	iAddGold += iAddGold*(fAddGoldWithPet/100);
	NTGameSave::sharedGameSave()->updateValue(_GS_GOLD, iAddGold+NTGameSave::sharedGameSave()->getDataById(_GS_GOLD));

	//±≥æ∞
	//±≥æ∞øÚ
	CCSprite* pBg=CCSprite::create("count/count_db1.png");
	pBg->setPosition(ccp(320, winSize.height-230));
	pMsg->addChild(pBg,2);
    
    CCSprite* pPro=CCSprite::create("count/count_db2.png");
    pPro->setPosition(ccp(580, winSize.height-230));
    pMsg->addChild(pPro,1);
    
   
   
    //pPro->addChild(getMenuItem);
    
    //
    CCSprite* pTitle;
    int a[6]={0,0,0,0,0,1};
    if(!NTGameSave::sharedGameSave()->isBoughtTheHero(_GS_HERO_IS_BUY_2)) a[0]=1;
    if (!NTGameSave::sharedGameSave()->isBoughtTheHero(_GS_HERO_IS_BUY_3))a[1]=1;
//    if (!NTGameSave::sharedGameSave()->isBoughtThePet(_GS_PET_IS_BUY_1))a[2]=1;
//    if (!NTGameSave::sharedGameSave()->isBoughtThePet(_GS_PET_IS_BUY_2))a[3]=1;
//    if (!NTGameSave::sharedGameSave()->isBoughtThePet(_GS_PET_IS_BUY_3))a[4]=1;
    int sum=0;
    for (int i=0;i<6;i++) {
        sum+=a[i];
    }
    if (sum==0) {
        pPro->removeAllChildren();
        pPro->setVisible(false);
        getMenuItem->setVisible(false);
    }else {
        CCLog("sum=%d",sum);
        sum=rand()%sum;
         CCLog("sum=%d",sum);
        int j=0;
        int b[5];
        for (int i=0; i<6; i++) {
            if(a[i]==1) {
            b[j]=i;
                 CCLog("b[%d]=%d",j,i);
                j++;
               
            }
        }
        index=b[sum]+4;
        //int Price[6]={8,10,20000,40000,60000,20};
        if (b[sum]!=5) {
            isCall=false;
        }
        //Jerry--Call
		CCSprite *get;
		CCSprite* get0;
		if (index == 4)
		{
			get = CCSprite::create(isCall ? "heart/8yuan.png" : "heart/8yuan.png");
			get0 = CCSprite::create(isCall ? "heart/8yuan.png" : "heart/8yuan.png");
		}
		else if (index == 5)
		{
			get = CCSprite::create(isCall ? "heart/10yuan.png" : "heart/10yuan.png");
			get0 = CCSprite::create(isCall ? "heart/10yuan.png" : "heart/10yuan.png");
		}
		else if (index == 9)
		{
			get = CCSprite::create(isCall ? "heart/20yuan.png" : "heart/20yuan.png");
			get0 = CCSprite::create(isCall ? "heart/20yuan.png" : "heart/20yuan.png");
		}

		get->setScale(0.8);
		get0->setScale(0.8);
        

        getMenuItem = NTMenuItemSprite::create(
                                               get,
                                               get0,
                                               NULL, this, menu_selector(NTGameHud::onGetCallBack));
        
//        CCLabelAtlas* BuyPrice = CCLabelAtlas::create(CCString::createWithFormat("%d", Price[b[sum]])->getCString(), "heart/stage_an2nb.png", 12, 20, 48);
//        BuyPrice->setAnchorPoint(ccp(0.5f,0.5f));
//        BuyPrice->setPosition(ccp(getMenuItem->getContentSize().width/2+12,getMenuItem->getContentSize().height/2+4));
//        getMenuItem->addChild(BuyPrice);
      pTitle=CCSprite::create((CCString::createWithFormat("count/count_js%d.png",b[sum])->getCString()));
        pTitleGet = NTMenuItemSprite::create(
                                               pTitle,
                                               pTitle,
                                               NULL, this, menu_selector(NTGameHud::onGetCallBack));
        pTitleGet->setPosition(ccp(580,winSize.height-225));
        //pPro->addChild(pTitle);
    }
    
   
	//¿˙ ∑◊Ó∏ﬂ∑÷
	CCLabelAtlas* pMaxScore=CCLabelAtlas::create(
		CCString::createWithFormat("%d", iMaxScore)->getCString(), "count/count_zgfnb.png", 10, 15, 48);
	pMaxScore->setAnchorPoint(ccp(0.5f, 0.5f));
	pMaxScore->setPosition(ccp(370, winSize.height-180));
	pMsg->addChild(pMaxScore,3);
	//◊‹∑÷ ˝
	CCLabelAtlas* pTotalScore=CCLabelAtlas::create(
		CCString::createWithFormat("%d", iTotalScore)->getCString(), "count/count_zfnb.png", 28, 42, 48);
	pTotalScore->setAnchorPoint(ccp(0.5f, 0.5f));
	pTotalScore->setPosition(ccp(320, winSize.height-230));
	pMsg->addChild(pTotalScore,3);
	//∑÷ ˝
	CCLabelAtlas* pScore=CCLabelAtlas::create(
		CCString::createWithFormat("%d", iScore)->getCString(), "count/count_mnb.png", 13, 20, 48);
	pScore->setAnchorPoint(ccp(0.5f, 0.5f));
	pScore->setPosition(ccp(330, winSize.height-320));
	pMsg->addChild(pScore,3);
	//π´¿Ô ˝
	CCLabelAtlas* pMile=CCLabelAtlas::create(
		CCString::createWithFormat("%d", iMiles)->getCString(), "count/count_mnb.png", 13, 20, 48);
	pMile->setAnchorPoint(ccp(0.5f, 0.5f));
	pMile->setPosition(ccp(330, winSize.height-280));
	pMsg->addChild(pMile,3);
    //Jerry--HeartCount
    CCLabelAtlas* pHeart=CCLabelAtlas::create(
                        CCString::createWithFormat("%d", iHeart)->getCString(), "count/count_mnb.png", 13, 20, 48);
    pHeart->setAnchorPoint(ccp(0.5f, 0.5f));
    pHeart->setPosition(ccp(330, winSize.height-140));
    pMsg->addChild(pHeart,3);
	//∞¥≈•
	CCSprite *normal=CCSprite::create("count/count_an.png");
	CCSprite* sel=CCSprite::create("count/count_an.png");
	NTMenuItemSprite* okMenuItem = NTMenuItemSprite::create(
		normal,
		sel,
		NULL, this, menu_selector(NTGameHud::onMsgOkCallBack));

	okMenuItem->setPosition(ccp(255, winSize.height-380));
    CCSprite *re0=CCSprite::create("count/count_an2.png");
    CCSprite *re1=CCSprite::create("count/count_an2.png");
    NTMenuItemSprite* reMenuItem = NTMenuItemSprite::create(
                    re0,
                    re1,
                    NULL, this, menu_selector(NTGameHud::onMsgReCallBack));
    
    CCSprite* gift= CCSprite::create("gift/gift_2.png");
    NTMenuItemSprite* ismag = NTMenuItemSprite::create(gift,gift,this,menu_selector(NTGameHud::menu_gift));
  
    //Jerry--Action
    CCActionInterval *scaleto =CCScaleTo::create(0.4, 1.05);
    CCActionInterval *Rescaleto =CCScaleTo::create(0.4, 1);
    CCFiniteTimeAction* seq = CCSequence::create(scaleto,Rescaleto,NULL);
    CCActionInterval * repeatForever =CCRepeatForever::create((CCActionInterval* )seq);
    gift->runAction(repeatForever);
    
    reMenuItem->setPosition(ccp(395, winSize.height-380));
     getMenuItem->setPosition(ccp(580,winSize.height-380));
    ismag->setPosition(ccp(180,380));
	pMsg->setSeletor(okMenuItem, reMenuItem,ismag,getMenuItem,pTitleGet);
    
   
}
//”Œœ∑Ω· ¯µƒªÿµ˜∫Ø ˝£®ºÃ–¯”Œœ∑£©
void NTGameHud::onMsgOkCallBack( CCObject *pSender )
{

    this->removeChildByTag(GameLayerMSG);
    CCDirector::sharedDirector()->replaceScene(NTStart::scene());
    updateGameSaveDistance();
   // NTGameSound::sharedEngine()->closeAll();
    //	toggleMusic->setSelectedIndex(1);
}
void NTGameHud::onGetCallBack(CCObject *pSender)
{
    if (index!=0) {
        CCLog("get");
        Cocos_order(index);
        //index=0;
    }
}
void NTGameHud::menu_gift(CCObject *pSender)
{
    NTGift* pLayer = NTGift::create();
    pMsg->addChild(pLayer,3);
    pLayer->setPosition(ccp(0,0));
    
}

void NTGameHud::onMsgReCallBack( CCObject *pSender )
{
      updateGameSaveDistance();
    if (NTGameSave::sharedGameSave()->getDataById(_GS_HEART_COUNTLESS)==1)
    {
          CCDirector::sharedDirector()->replaceScene(NTGameScene::scene());
        return;
    }
    if(NTGameSave::sharedGameSave()->getDataById(_GS_HEART))
    {
      NTGameSave::sharedGameSave()->updateValue(_GS_HEART,NTGameSave::sharedGameSave()->getDataById(_GS_HEART)-1);
    CCDirector::sharedDirector()->replaceScene(NTGameScene::scene());
    }
    else{
        this->removeChildByTag(GameLayerMSG);
        CCDirector::sharedDirector()->replaceScene(NTStart::scene());
        //NTGameSound::sharedEngine()->closeAll();
    }
}

void NTGameHud::pauseItemCallBack( cocos2d::CCObject* pSender )
{
	if(m_bIsPauseLock){
		return;
	}else{
		m_bIsPauseLock = true;
		m_pPauseItem->setEnabled(false);
	}

	pause(!getIsPause());

	if(getIsPause()) 
	{
		m_pPauseItem->runAction(CCMoveBy::create(0.2f, ccp(100, 0)));
		m_pMenu->runAction(CCSequence::createWithTwoActions(
			CCMoveTo::create(0.2f, ccp(0, 0)),
			CCCallFunc::create(this, callfunc_selector(NTGameHud::pauseItemLock))
			)
			);

	} else {

		m_pPauseItem->runAction(CCMoveBy::create(0.2f, ccp(-100, 0)));
		m_pMenu->runAction(CCSequence::createWithTwoActions(
			CCMoveTo::create(0.2f, ccp(100, 0)),
			CCCallFunc::create(this, callfunc_selector(NTGameHud::pauseItemLock))));
	}
}

void NTGameHud::pause( bool pFlag )
{

	setIsPause(pFlag);
	getControlLayer()->pauseGameAll(pFlag);
	if(pFlag) {
	} else {
	}
}

void NTGameHud::pauseItemLock()
{
	m_bIsPauseLock = false;
	m_pPauseItem->setEnabled(true);
}
//”Œœ∑æ≠–– ±µƒ÷ÿ¿¥∞¥≈•
void NTGameHud::replayCallBack( cocos2d::CCObject* pSender )
{
      updateGameSaveDistance();
    if(NTGameSave::sharedGameSave()->getDataById(_GS_HEART))
    {
        NTGameSave::sharedGameSave()->updateValue(_GS_HEART,NTGameSave::sharedGameSave()->getDataById(_GS_HEART)-1);
        CCDirector::sharedDirector()->replaceScene(NTGameScene::scene());
    }
    else{
        this->removeChildByTag(GameLayerMSG);
        CCDirector::sharedDirector()->replaceScene(NTStart::scene());
      
       // NTGameSound::sharedEngine()->closeAll();
    }
}
//”Œœ∑æ≠–– ±µƒ∑µªÿ∞¥≈•
void NTGameHud::backToStateCallBack( cocos2d::CCObject* pSender )
{
      updateGameSaveDistance();
	CCDirector::sharedDirector()->replaceScene(NTStart::scene());
	//NTGameSound::sharedEngine()->closeAll();
//	toggleMusic->setSelectedIndex(1);
}

void NTGameHud::musicSwitchCallBack( cocos2d::CCObject* pSender )
{
	NTGameSound::sharedEngine()->playEffectById(SOUND_BUTTON,false,NTGameSave::sharedGameSave()->isSound);
	NTGameSound::sharedEngine()->switchAudio();
}
 void NTGameHud::update( float dt )
{
    
    if (this->getChildByTag(8)!=NULL){
        if (getChildByTag(8)->getScale()==0) {
            getControlLayer()->pauseGameAll(false);
        }
    }
    if(NTGameSave::sharedGameSave()->isBoughtTheHero(_GS_HERO_IS_BUY_2)&&index==4)
    {
        getMenuItem->setVisible(false);
        index=0;
        return;
    }
    if(NTGameSave::sharedGameSave()->isBoughtTheHero(_GS_HERO_IS_BUY_3)&&index==5)
    {
        getMenuItem->setVisible(false);
        index=0;
        return;
    }
}
void NTGameHud::showKickBoss()
{
    KickBoss* pLayer = KickBoss::create();
    pLayer->timeCount=5+floor(m_pControlLayer->m_iScore-10000)/5000;
    this->addChild(pLayer,999999,8);
    pLayer->setPosition(ccp(0,0));
    pLayer->setControlLayer(m_pControlLayer);
    getControlLayer()->pauseGameAll(true);
}







