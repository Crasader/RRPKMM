#include "KickBoss.h"
#include "NTConstants.h"
#include "NTControlLayer.h"
#include "NTGameHud.h"
void KickBoss::onEnter()
{
   //Jerry--task--boss
    if(NTGameSave::sharedGameSave()->getDataById(_GS_TASKTWO)==12){
        CCLog("task--boss");
        NTGameSave::sharedGameSave()->updateValue(_GS_TASKTWO_FINISH,1);
    }
	NTCoverLayer::onEnter();
        kickCount=0;
    
   // timeCount=5+getControlLayer()->m_iScore;//floor((getControlLayer()->m_iScore-100)/50);
    scheduleUpdate();
    schedule(schedule_selector(KickBoss::timeUpdate),  1.0f);
    CCSprite* pGameStart = CCSprite::create("Gold/tongbian.png");
    pGameStart->setPosition(ccp(400, 240));
   // pGameStart->setScale(2);
    this->addChild(pGameStart, 2,87);
    pGameStart->setOpacity(220);
    pGameStart->runAction(CCSequence::create(CCDelayTime::create(2.0f),CCCallFuncN::create(this, callfuncN_selector(KickBoss::hintCallBack)),
                                             NULL));
    
   
	initUI();
    m_bIsTouchMu=false;
}
void KickBoss::initUI()
{
    CCSprite* pBg = CCSprite::create("Gold/bbg_arena.jpg");
    pBg->setPosition(ccp(0, 0));
    pBg->setAnchorPoint(ccp(0, 0));
    pBg->setScale(0.8f);
    this->addChild(pBg);
    m_pEffectLayer = NTEffectLayer::create();
    addChild(m_pEffectLayer,2);
    //m_pEffectLayer->setMapLayer(this);
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    m_pBg = CCSprite::create("gift/gift_1.png");
//    m_pBg->setPosition(ccp(winSize.width/2, winSize.height/2));
//    this->addChild(m_pBg);
    CCSprite *mProgressBg = CCSprite::create("Gold/boss-di.png");
    //mProgressBg->setScale(1.2f);
    mProgressBg->setPosition(ccp(150,450));
    addChild(mProgressBg,2);
    CCSprite *mProgress = CCSprite::create("Gold/tiao.png");
    //mProgress->setScale(2);
    pPowerLeft =CCProgressTimer::create(mProgress);
    pPowerLeft->setType(kCCProgressTimerTypeBar);
    pPowerLeft->setPercentage(100);
    pPowerLeft->setMidpoint(ccp(0,1));
    pPowerLeft->setBarChangeRate(ccp(1, 0));
    pPowerLeft->setPosition(200,12);
    mProgressBg->addChild(pPowerLeft);
    m_pCount = CCLabelAtlas::create(CCString::createWithFormat("%d", kickCount)->getCString(), "hero/stage_lvnb.png", 11, 16, 48);
    m_pCount->setScale(3.0f);
    m_pCount->setPosition(ccp(0, 0));
   // this->addChild(m_pCount);
    CCSprite *mTimeLeftBg = CCSprite::create("Gold/daojishi.png");
    mTimeLeftBg->setPosition(ccp(650, 400));
    //mTimeLeftBg->setScale(1.5f);
    addChild(mTimeLeftBg,1);
    
    m_pTimeleft = CCLabelAtlas::create(CCString::createWithFormat("%d",timeCount)->getCString(),"start/start_jbsz1.png",15,23,'0');
    if (timeCount<10) {
        m_pTimeleft->setString(CCString::createWithFormat("0%d", timeCount)->getCString());
    }else
        m_pTimeleft->setString(CCString::createWithFormat("%d", timeCount)->getCString());
    m_pTimeleft->setScale(1.5f);
    m_pTimeleft->setPosition(ccp(50, 10));
    mTimeLeftBg->addChild(m_pTimeleft);
    
    m_pMenu = CCMenu::create();
    m_pMenu->setPosition(CCPointZero);
    m_pMenu->setTouchEnabled(false);
    this->addChild(m_pMenu, 1);
    //Jerry--Aizou
    m_pArmature =CCArmature::create("aizou");
    m_pArmature->setPosition(ccp(400,100));
    m_pArmature->getAnimation()->play("stand1");
    m_pArmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(KickBoss::animationEvent));
    this->addChild(m_pArmature);
}
bool KickBoss::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    if (!m_bIsTouchMu)
    {
        CCPoint touchPoint = pTouch->getLocation();
        m_bIsTouchMu = m_pMenu->ccTouchBegan(pTouch,pEvent);
        ccBezierConfig bezier;
        CCSprite* pCoin =CCSprite::create("Gold/gold.png");
        pCoin->setScale(1.5f);
        addChild(pCoin,2,88);
        if (touchPoint.x<400) {
            pCoin->setPosition(ccp(100,-20));
            bezier.controlPoint_1 = ccp(100,-20);
            bezier.controlPoint_2 = ccp(100,200);
        }else{
            pCoin->setPosition(ccp(700,-20));
        bezier.controlPoint_1 = ccp(700,-20);
        bezier.controlPoint_2 = ccp(700,200);
        }
        bezier.endPosition	= ccp(400,380);
        CCFiniteTimeAction *beizerMove = CCBezierTo::create(0.1f,bezier);
        CCCallFunc *callNext = CCCallFunc::create(this,callfunc_selector(KickBoss::coinHitCallBack));
       
        pCoin->runAction(CCSequence::create(beizerMove,callNext,NULL));
        
        
    }
    
    return true;
    
}
void KickBoss::animationEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
    std::string id = movementID;
    
    if (movementType == LOOP_COMPLETE)
    {
        if (id.compare("fastrun") == 0)
        {
            
        }
    }
    else if(movementType == COMPLETE)
    {
        if (id.compare("hurt") == 0)
        {
           m_pArmature->getAnimation()->play("stand1");
        }
    }
}
void KickBoss::update( float dt )
{
    if (timeCount<1) {
        getControlLayer()->pauseGameAll(false);
        getControlLayer()->menu_close2_1();
//        NTGameHud() *pLayer=(NTGameHud*)this->getParent();      //  pLayer->getControlLayer()->pauseGameAll(false);
        this->removeAllChildrenWithCleanup(true);
        this->removeFromParentAndCleanup(true);
       // getControlLayer()->menu_close2_1();
        
        return;
    }
 //  m_pCount->setString(CCString::createWithFormat("%d", kickCount)->getCString());
    pPowerLeft->setPercentage(100-kickCount/2);
}
void KickBoss::timeUpdate( float dt )
{
    if (timeCount>0) {
         timeCount--;
    }
    if (timeCount<10) {
        m_pTimeleft->setString(CCString::createWithFormat("0%d", timeCount)->getCString());
    }else
    m_pTimeleft->setString(CCString::createWithFormat("%d", timeCount)->getCString());
}
void KickBoss::coinHitCallBack()
{
    getControlLayer()->gameSound->playEffectById(SOUND_SKILL_CLEANUP,true,NTGameSave::sharedGameSave()->isSound);
     m_pArmature->getAnimation()->play("hurt");
    removeChildByTag(88);
    m_pEffectLayer->playAnimateForBomb(ccp(400, 380), EFFECT_BUFF_BOMB);
     kickCount++;
    if (kickCount>199) {
        getControlLayer()->pauseGameAll(false);
        getControlLayer()->revive();
        this->removeAllChildrenWithCleanup(true);
        this->removeFromParentAndCleanup(true);
    }
}
void KickBoss::hintCallBack(CCNode* pSender)
{
    removeChildByTag(87);
   
}


