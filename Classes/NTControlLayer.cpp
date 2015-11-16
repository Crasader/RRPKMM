#include "NTControlLayer.h"
#include "NTStart.h"
#include "NTConstants.h"
#include "NTGameSave.h"
#include "NTGameGuide.h"
#include "NTMiniMap.h"
#include "NTGameHud.h"
#include "NTGameScene.h"
#include "Assistant.h"
#include "KickBoss.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
//extern CPlayerAttrib *g_playerAttribute;			

static SDialogContent g_OncePayLibao;

extern "C" {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void Java_com_ibirdgame_archirun_PayWrapper_buyGame(JNIEnv* env, jobject thiz, jint id)
	{
       
		CCObject* target = g_OncePayLibao.target;
		SYSDLG_CallFunc pFunc = g_OncePayLibao.func;
		(target->*pFunc)(id);
	}
#endif
}
// on "init" you need to initialize your instance
bool NTControlLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    g_OncePayLibao.target = this;
    g_OncePayLibao.func = (SYSDLG_CallFunc)(&NTControlLayer::purchaseCallBack);
    this->schedule(schedule_selector(NTControlLayer::update_button),0.2f);
	sex = false;
	gameSound =  NTGameSound::sharedEngine();
    return true;
}

void NTControlLayer::onEnterTransitionDidFinish()
{
    //Jerry--kickboss
    
    isKickBoss=true;
	NTGameSound::sharedEngine()->playBackgroundMusic("sound/backgroud.ogg",true,NTGameSave::sharedGameSave()->isSound);
	CCLayer::onEnterTransitionDidFinish();
	m_iMiles = 0;
	m_iScore = 0;
	m_bIsGameOver = false;
	m_bIsInSuperMode = false;
	m_bIsPause = false;
	m_bIsBegin = false;
	count1=1;
	count2=0;
	index = -1;
	//µÿÕº
	m_pMapLayer = NTMapLayer::create();
	this->addChild(m_pMapLayer);

	//ÕÊº“
	m_pActor = NTActor::createActor(NTGameSave::sharedGameSave()->getHeroSelect());
	m_pActor->setMapLayer(getMapLayer());
	/*m_pActor->setIsAutoPlay(true);*/
	this->addChild(m_pActor);
//	NTGameSound::sharedEngine()->initPlayer(m_pActor);

	//≥ËŒÔ
	int iHeroPet = NTGameSave::sharedGameSave()->getHeroPet();
	if(iHeroPet==-1){
		m_pArmaturePet = NULL;
	}else{
		m_pArmaturePet = CCArmature::create(CCString::createWithFormat("pet%d", iHeroPet+1)->getCString());
		m_pArmaturePet->getAnimation()->play("fly");
		m_pArmaturePet->setScale(pet_data[0][PET_DATA_SCALE]);
		m_pArmaturePet->setPosition(ccp(320, 240));
// 		 	m_pArmaturePet->runAction(CCRepeatForever::create(CCSequence::create(
// 		 		CCMoveBy::create(1.0f, ccp(0, 40)),CCMoveBy::create(1.0f, ccp(0, -40)),NULL)));
		this->addChild(m_pArmaturePet);
	}


	//NPC
	m_pActorNpc = NTActor::createActor(ACTOR_2);
	m_pActorNpc->setMapLayer(getMapLayer());
	m_pActorNpc->setIsAutoPlay(true);
	this->addChild(m_pActorNpc);

	m_pActor->setEnemy(m_pActorNpc);
	m_pActorNpc->setEnemy(m_pActor);

	menu_reset(NULL);

	m_fTime = 0;
	//”Œœ∑÷˜ΩÁ√Êµƒ¡Ω∏ˆ∞¥≈•£®œ¬ª¨∫ÕÃ¯£©
	m_pSlide = CCSprite::create("game/game_hx.png");
	m_pSlide->setPosition(ccp(100, 70));
	this->addChild(m_pSlide);
	m_pJump = CCSprite::create("game/game_ty.png");
	m_pJump->setPosition(ccp(700, 70));
	this->addChild(m_pJump);

	m_pJiaSu = CCSprite::create("box/game_dj_fx.png");
	m_pJiaSu->setPosition(ccp(700, 200));
	this->addChild(m_pJiaSu);
    m_pJiaSu->setVisible(false);
	


	//–°µÿÕº (ƒ‹¡øÃı)
	m_pMiniMap = NTMiniMap::create();
	this->addChild(m_pMiniMap);

	
	scheduleUpdate();
	//≥ı ºªØ–¬ ÷ΩÃ≥Ã
	initGuideLayer();
//	this->schedule(schedule_selector(NTControlLayer::update_button),0.2f);
	int nSaveJiaSu = NTGameSave::sharedGameSave()->getDataById(_GS_JIASU);
	sprintf(sss,"%d",nSaveJiaSu);
	label = CCLabelTTF::create(sss, "Arial", 20);	
//	label->setString(sss);
//	label->setOpacity(100);
	label->setPosition(ccp(700, 185));
	label->setColor(ccc3(0, 255, 0));
    label->setVisible(false);
	this->addChild(label, 99999);
	
}


void NTControlLayer::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, PRIORITY_NTLAYER_LEVEL_1, true);
}

void NTControlLayer::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool NTControlLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_bIsGameOver){
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pTouchPos = convertTouchToNodeSpace(pTouch);

	if(m_pActor->getIsFlying()){
		return false;
	}
	if(m_pJiaSu->boundingBox().containsPoint(pTouchPos)){

		if(NTGameSave::sharedGameSave()->getDataById(_GS_JIASU)>=1){
			m_pActor->fly(3.0f);
			gameSound->playEffectById(SOUND_GAME_WIN,true,NTGameSave::sharedGameSave()->isSound);
			NTGameSave::sharedGameSave()->updateValue(_GS_JIASU,NTGameSave::sharedGameSave()->getDataById(_GS_JIASU)-1);
		}
		return true;
	}
	//◊Ûœ¬ª¨
	if(m_pSlide->boundingBox().containsPoint(pTouchPos)&&m_pActor->getIsOnLand()){
      
		m_pActor->slide();
		///gameSound->playEffectById(SOUND_MAP_FLOWER,true,
			//NTGameSave::sharedGameSave()->isSound);
		return true;
	}
	//”“Ã¯‘æ
	else if(m_pJump->boundingBox().containsPoint(pTouchPos)){

		//»Áπ˚ «ACTOR3
		if(m_pActor->getType()==ACTOR_3){
			//»Áπ˚“—æ≠Ã¯∆¿¥¡À,ª¨œË
			if(!m_pActor->getIsOnLand() && m_pActor->getActorGravity()!=GLIDE_G){
				m_pActor->setSpeed(0);
				m_pActor->setActorGravity(GLIDE_G);
				return true;
			}
		}

		m_pActor->jump();
        if (m_pActor->getType()==ACTOR_1) {
            gameSound->playEffectById(SOUND_SKILL_CLEANUP,true,NTGameSave::sharedGameSave()->isSound);
        }else
            gameSound->playEffectById(SOUND_SKILL_DOUBLEATT,true,NTGameSave::sharedGameSave()->isSound);
		
		return false;
	}
}

void NTControlLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	/*m_pActor->setSpeed(m_pActor->getSpeed()<0?70:m_pActor->getSpeed());*/
}

void NTControlLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_pActor->getIsFlying()){
		return;
	}

	if(m_pActor->getActorState()==STATE_SLIDE){
		m_pActor->slideOver();
	}

	//»Áπ˚ «ACTOR3
	if(m_pActor->getType()==ACTOR_3){
		m_pActor->setActorGravity(GRAVITY_G);
		return;
	}
}

void NTControlLayer::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_pActor->getIsFlying()){
		return;
	}

	if(m_pActor->getActorState()==STATE_SLIDE){
		m_pActor->slideOver();
	}

	//»Áπ˚ «ACTOR3
	if(m_pActor->getType()==ACTOR_3){
		m_pActor->setActorGravity(GRAVITY_G);
		return;
	}
}


void NTControlLayer::menu_reset( CCObject* pRender )
{
	menu_Actor1(NULL);
	menu_Actor2(NULL);
	getMapLayer()->reset();
}
void NTControlLayer::menu_props1( CCObject* pRender )
{
	getMapLayer()->addProps(BOX_BANANA_SKIN, ccp(m_pActorNpc->getPositionX()+250, m_pActorNpc->getPositionY()));
}

void NTControlLayer::menu_props2( CCObject* pRender )
{
	m_pActorNpc->setMaxLeftPosX(m_pActorNpc->getMaxLeftPosX()-80);
}

void NTControlLayer::menu_props3( CCObject* pRender )
{
	m_pActor->setMaxLeftPosX(m_pActor->getMaxLeftPosX()+80);
}

void NTControlLayer::menu_Actor1( CCObject* pRender )
{
	m_pActor->setPosition(ccp(150, 300));
	m_pActor->setSpeed(1200);
	m_pActor->setMaxLeftPosX(ACTOR_BASE_MAX_LEFT_POSX);
}

void NTControlLayer::menu_Actor2( CCObject* pRender )
{
	m_pActorNpc->setPosition(ccp(250, -200));
	m_pActorNpc->setSpeed(300);
	m_pActorNpc->setMaxLeftPosX(ACTORNPC_BASE_MAX_LEFT_POSX);
	m_pActorNpc->unscheduleAllSelectors();
	m_pActorNpc->stopAllActions();
	m_pActorNpc->pauseSchedulerAndActions();
}

void NTControlLayer::update( float dt )
{
	
	//√ø¥ŒÀ¢–¬º”ÀŸµ¿æﬂµƒ ˝¡ø
	int nSaveJiaSu = NTGameSave::sharedGameSave()->getDataById(_GS_JIASU);
	sprintf(sss,"%d",nSaveJiaSu);
	label->setString(sss);

	//»Áπ˚ÕÊº“À¿Õˆ, ”Œœ∑Ω· ¯
	if(m_pActor->getActorState()==STATE_DEATH){
		m_bIsGameOver = true;
		showGameOver();
	}

	int iScoreAdd = m_pActor->getScore()-m_iScore;

	m_fTime += dt;

// 	m_pLabelSpeed->setString(CCString::createWithFormat("SPEED: %2.2f", getMapLayer()->getSpeed())->getCString());
// 	m_pLabelMapMoveGap->setString(CCString::createWithFormat("MOVE_GAP: %2.2f", getMapLayer()->getSpeed()*dt)->getCString());
// 	m_pLabelLength->setString(CCString::createWithFormat("SCREEN: %2.2f", getMapLayer()->m_fLength/800)->getCString());
// 	m_pLabelTime->setString(CCString::createWithFormat("TIME: %2.2f", m_fTime)->getCString());

// 	m_pLabelSpeed->setString(CCString::createWithFormat("BATCH: %d", getMapLayer()->getBoxBatchNode()->getChildrenCount())->getCString());
// 	m_pLabelMapMoveGap->setString(CCString::createWithFormat("ARRAY: %d", getMapLayer()->getBoxArray()->count())->getCString());
// 	m_pLabelLength->setString(CCString::createWithFormat("FREE: %d", getMapLayer()->getBoxFreeArray()->count())->getCString());
// 	m_pLabelTime->setString(CCString::createWithFormat("dt: %2.2f", dt)->getCString());

	m_iMiles = getMapLayer()->m_fLength/20;
	m_iScore = m_pActor->getScore();

	//÷¥––ÀŸ∂»±‰ªØ
	float fActorLandSpeedChange = m_pActor->getLandSpeedChangeValue();
	float fNPCLandSpeedChange = m_pActorNpc->getLandSpeedChangeValue();

	//ÕÊº“”Œœ∑ÀŸ∂»”–±‰ªØ£¨◊˜”√”⁄NPC
	if(fActorLandSpeedChange!=0){
		
		if(m_pActor->getActionByTag(ACTOR_ACTION_CHANGE_LAND_SPEED)==NULL){
			m_pActor->setMaxLeftPosX(fActorLandSpeedChange+ACTOR_BASE_MAX_LEFT_POSX);
			CCSequence* pSeq = CCSequence::create(
				CCDelayTime::create(0.5f), 
				CCCallFuncN::create(this, callfuncN_selector(NTControlLayer::landSpeedChangeCallBack)),
				NULL);
			pSeq->setTag(ACTOR_ACTION_CHANGE_LAND_SPEED);
			m_pActor->runAction(pSeq);
		}
	}

	//NPCÀŸ∂»”–±‰ªØ£¨◊˜”√”⁄◊‘º∫
	if(fNPCLandSpeedChange!=0){
		m_pActorNpc->setMaxLeftPosX(m_pActorNpc->getMaxLeftPosX()+fNPCLandSpeedChange);
		m_pActorNpc->setLandSpeedChangeValue(0);
	}

	//∏¸–¬√‘ƒ„µÿÕº
	if(!m_bIsInSuperMode){
        //Jerry--100
		getMiniMap()->updatePowerBar(((float)iScoreAdd)/100);
		if(getMiniMap()->getPercentOfPowerBar()==100){
			showSuperMode();
		}
	}


	//∏¸–¬¬∑≥Ã
	getGameHud()->updateDistance(m_iMiles);
	//∏¸–¬∑÷ ˝
	getGameHud()->updateScores(m_iScore);
// 	//∏¸–¬player—™Ãı
// 	getGameHud()->updatePlayerHp(m_pActor->getHp());
// 	//∏¸–¬npc—™Ãı
// 	getGameHud()->updateNpcHp(m_pActorNpc->getHp(), m_pActorNpc->getType());
	
}


void NTControlLayer::landSpeedChangeCallBack( CCNode* pSender)
{
	NTActor* pActor = (NTActor*)pSender;
	float fActorLandSpeedChange = pActor->getLandSpeedChangeValue();
	pActor->getEnemy()->setMaxLeftPosX(pActor->getEnemy()->getMaxLeftPosX()-fActorLandSpeedChange);
	pActor->setMaxLeftPosX(ACTOR_BASE_MAX_LEFT_POSX);
	pActor->setLandSpeedChangeValue(0);
}


void NTControlLayer::showGameOver()
{
//	unscheduleAllSelectors();
	getMapLayer()->setSpeed(BASE_SPEED);
	m_pActor->setIsOnBlock(true);
	m_pActor->runAction(CCMoveBy::create(BASE_SPEED/400, ccp(-450, 0)));
	this->runAction(CCSequence::create(
		CCDelayTime::create(1.5f),
		CCCallFunc::create(this, callfunc_selector(NTControlLayer::showGameOverCallBack)),NULL));
//Jerry
    //CCCallFunc::create(this, callfunc_selector(NTControlLayer::menu_close2_1)),NULL));
    
}

void NTControlLayer::showGameOverCallBack()
{
//	pauseGameAll(true);
	//¥¥Ω®Ãÿª›¿Ò∞¸
	if(count1==1&&m_pActor->getActorState()==STATE_DEATH){
		count1++;
//		layer = CCLayer::create();
//		CCSprite* monyeBag = CCSprite::create("teHui/bg.png");
//		monyeBag->setScale(0.5f);
//		layer->addChild(monyeBag);
//		layer->setPosition(ccp(400,220));
//		CCMenuItemImage* button1 = CCMenuItemImage::create("teHui/queRen3.png","teHui/queRen3.png",this,menu_selector(NTControlLayer::menu_back));
//		CCMenu* menu1 = CCMenu::create(button1,NULL);
//		
//		index1 = menu1->getTag();
//		layer->addChild(menu1);
//		menu1->setPosition(ccp(0,-65));
//		this->addChild(layer);
//		CCSequence* ac = CCSequence::create(CCDelayTime::create(0.2f),CCScaleTo::create(0.2f,0.8f),
//			CCScaleTo::create(0.2f,1.2f),NULL);
//		button1->runAction(CCSequence::create(CCRepeat::create(ac,3),
//			CCCallFunc::create(this, callfunc_selector(NTControlLayer::menu_CallBack1)),NULL));
        
        
        //Jerry--kickboss
        if(m_iScore>10000&&isKickBoss)
        {
            isKickBoss=false;
            getGameHud()->showKickBoss();
        }else{
        menu_close2_1();
        }
	}else{return;}
}
//“∆≥˝Ãÿª›¿Ò∞¸
void NTControlLayer::menu_CallBack1(){
	layer->runAction(CCSequence::create(CCMoveTo::create(0.8f,ccp(400.0f,1500.0f)),
		CCCallFunc::create(this, callfunc_selector(NTControlLayer::menu_close2_1)),NULL));

}
//¥¥Ω®∏¥ªÓ∞¥≈•
void NTControlLayer::menu_close2_1(){
	//∏¥ªÓ∞¥≈•
//Jerry
    m_TempScore=m_pActor->getScore();
	CCMenuItemSprite* game_ganin = CCMenuItemSprite::create(CCSprite::create("youHui/fuhuojiemian.png"), CCSprite::create("youHui/fuhuojiemian.png"), NULL, this, menu_selector(NTControlLayer::resurrect));

	CCMenuItemSprite* buyButton1 = CCMenuItemSprite::create(CCSprite::create("youHui/2yuan.png"), CCSprite::create("youHui/2yuan.png"), NULL,
		this, menu_selector(NTControlLayer::resurrect));

	buyButton1->setPositionY(-80);
	buyButton1->setScale(1.3);

	CCMenu* menu2 = CCMenu::create(game_ganin, buyButton1, NULL);
    menu2->setTag(198);
	this->addChild(menu2);
	menu2->setPosition(ccp(400,240));

//	CCProgressTo¥¥Ω®Ω¯∂»Ãı
	sp = CCSprite::create("youHui/fuhuo.png");
	CCProgressTo* progress = CCProgressTo::create(2,100);  
	left = CCProgressTimer::create(sp);  
	left->setType(kCCProgressTimerTypeBar);  
	left->setMidpoint(ccp(0,1));  
	left->setBarChangeRate(ccp(1, 0));
	left->setPosition(ccp(397,325));
	this->addChild(left);
	left->runAction(CCSequence::create(progress,CCCallFunc::create(this, callfunc_selector(NTControlLayer::menu_close2_2)),NULL));

}
//æ´∂»Ãıµƒªÿµ˜∫Ø ˝
void NTControlLayer::menu_close2_2(){
//	sp->removeAllChildrenWithCleanup(true);

	if(m_bIsGameOver){
		unscheduleAllSelectors();
		pauseGameAll(true);
      //Jerry--update
		getGameHud()->showGameOverMsg(m_iScore, m_iMiles);
//		NTGameSound::sharedEngine()->closeAll();

	}else{return;}
	
}

void NTControlLayer::resurrect(CCObject* p){
//	g_OncePayLibao.target = this;
//	g_OncePayLibao.func = (SYSDLG_CallFunc)(&NTControlLayer::setupdataLibaoState_4);
    //Jerry--pasue
    pauseGameAll(true);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	//getStaticMethodInfo
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/PayWrapper","Cocos_order", "(I)V");

	if (!isHave) {
		CCLog("jni:¥À∫Ø ˝≤ª¥Ê‘⁄");
	}else{
		CCLog("jni:¥À∫Ø ˝¥Ê‘⁄");
		//µ˜”√¥À∫Ø ˝
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,13);
	}
	CCLog("jni-java∫Ø ˝÷¥––ÕÍ±œ");
#endif
	//∏¥ªÓ∞¥≈•µƒªÿµ˜∫Ø ˝
    
    
//	CCMenu* men = (CCMenu*)p;
//	men->runAction( CCSequence::create(CCMoveTo::create(1,ccp(400,1500)),CCCallFunc::create(this, callfunc_selector(NTControlLayer::menu_close2_3)),NULL) );
//	left->runAction(CCMoveTo::create(1,ccp(400,1500)));
    
}
//µ„ª˜∏¥ªÓ∞¥≈•»Áπ˚∏∂∑—≥…π¶µ˜”√¥À∑Ω∑®
//void NTControlLayer::setupdataLibaoState_4(int i){
//    getGameHud()->pause(false);
//	if(i==1){
//		count2=4;
//		sex = true;
//        //m_pActor->setLife(true);
//	}else{
////		unscheduleAllSelectors();
////		pauseGameAll(true);
////	getGameHud()->showGameOverMsg(m_iScore, m_iMiles);
//		m_bIsGameOver = false;
//		menu_close2_2();
//	}
//	
//}
void NTControlLayer::menu_close2_3(){
	//CCMenu* men = (CCMenu*)p;
    removeChildByTag(198);
	//removeChild(menu2);
	removeChild(left,true);
}
//Ãÿª›¿Ò∞¸µƒ∞¥≈•ªÿµ˜£®÷¥––£∫µ˜µΩ∞≤◊ø∆ΩÃ®£©
void NTControlLayer::menu_back(cocos2d::CCObject* p){
   
    
    
	//∏∂∑—Ω”ø⁄£®π∫¬ÚÃÿª›¿Ò∞¸∞¥≈•£©
	CCNode* sss= (CCNode*)p;
	index1 = sss->getTag();
	//º«¬ºjava∑µªÿ ±”¶÷¥––µƒ∑Ω∑®
//	g_OncePayLibao.target = this;
//	g_OncePayLibao.func = (SYSDLG_CallFunc)(&NTControlLayer::setupdataLibaoState_3);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //≈–∂œµ±«∞ «∑ÒŒ™Android∆ΩÃ®
	JniMethodInfo minfo;//∂®“ÂJni∫Ø ˝–≈œ¢Ω·ππÃÂ
	//getStaticMethodInfo ¥Œ∫Ø ˝∑µªÿ“ª∏ˆbool÷µ±Ì æ «∑Ò’“µΩ¥À∫Ø ˝
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/PayWrapper","Cocos_order", "(I)V");
    
    if (!isHave) {
        CCLog("jni:¥À∫Ø ˝≤ª¥Ê‘⁄");
	}else{
		CCLog("jni:¥À∫Ø ˝¥Ê‘⁄");
		//µ˜”√¥À∫Ø ˝
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,12);
	}
	CCLog("jni-java∫Ø ˝÷¥––ÕÍ±œ");
#endif
	
}
//Ãÿª›¿Ò∞¸∏∂∑—≥…π¶µƒªÿµ˜∫Ø ˝
//void NTControlLayer::setupdataLibaoState_3(int i){
//	count2=3;
//	layer->runAction(CCMoveTo::create(0.8f,ccp(400.0f,1500.0f)));
////	CCLog("sssss");
//	
//}
void NTControlLayer::showSuperMode()
{
	if(!m_bIsInSuperMode){
        //Jerry--task-goldmode
      if(NTGameSave::sharedGameSave()->getDataById(_GS_TASKTWO)==3){
        int goldmodeTimes=NTGameSave::sharedGameSave()->getDataById(_GS_GOLDMODE_TIMES)+1;
        NTGameSave::sharedGameSave()->updateValue(_GS_GOLDMODE_TIMES,goldmodeTimes);
        if(goldmodeTimes==3){
            CCLog("updateSuperMode%d",NTGameSave::sharedGameSave()->getDataById(_GS_GOLDMODE_TIMES));
            NTGameSave::sharedGameSave()->updateValue(_GS_TASKTWO_FINISH,1);
        }
      }
		schedule(schedule_selector(NTControlLayer::updateForSuperMode));
        NTGameSound::sharedEngine()->playBackgroundMusic("sound/bgm_super.ogg", true, NTGameSave::sharedGameSave()->isSound);
		m_pActor->fly(4.0f, true);
		//gameSound->playEffectById(SOUND_GAME_WIN,true,NTGameSave::sharedGameSave()->isSound);
		getMapLayer()->extraSpeed(4.0f);
		getMapLayer()->showGoldArea();
		m_bIsInSuperMode = true;
	}
	
}

void NTControlLayer::updateForSuperMode( float dt )
{
	//
	getMiniMap()->updatePowerBar(-0.15f);
	if(getMiniMap()->getPercentOfPowerBar()>0){
		//À¢≥¨º∂µÿÕº
	}
	else{
		//Ω¯»Î’˝≥£µÿÕº
		unschedule(schedule_selector(NTControlLayer::updateForSuperMode));
		m_bIsInSuperMode = false;
        NTGameSound::sharedEngine()->playBackgroundMusic("sound/backgroud.ogg", true, NTGameSave::sharedGameSave()->isSound);
		getMapLayer()->fromGoldAreaBackToNormalRoad();
	}

}


void NTControlLayer::pauseGameAll( bool pFlag )
{
	if(pFlag==m_bIsPause){
		return;
	}
	m_bIsPause = pFlag;

	if(pFlag) {

		CCDirector* pDirector = CCDirector::sharedDirector();
		if( m_bTouchEnabled ) {
			pDirector->getTouchDispatcher()->removeDelegate(this);
			unregisterScriptTouchHandler();
		}

		// remove this layer from the delegates who concern Accelerometer Sensor
		if (m_bAccelerometerEnabled) {
			pDirector->getAccelerometer()->setDelegate(NULL);
		}

		// remove this layer from the delegates who concern the kaypad msg
		if (m_bKeypadEnabled) {
			pDirector->getKeypadDispatcher()->removeDelegate(this);
		}

		CCNode::onExit();
	} else {

		CCDirector* pDirector = CCDirector::sharedDirector();
		// register 'parent' nodes first
		// since events are propagated in reverse order
		if (m_bTouchEnabled) {
			this->registerWithTouchDispatcher();
		}

		// then iterate over all the children
		CCNode::onEnter();

		// add this layer to concern the Accelerometer Sensor
		if (m_bAccelerometerEnabled) {
			pDirector->getAccelerometer()->setDelegate(this);
		}

		// add this layer to concern the kaypad msg
		if (m_bKeypadEnabled) {
			pDirector->getKeypadDispatcher()->addDelegate(this);
		}
	}
}

void NTControlLayer::initGuideLayer()
{
	m_fTime = 0;
	m_bGuideOver = false;

	//µ⁄“ª¥ŒΩ¯»Î”Œœ∑---------------
	int iFirst = NTGameSave::sharedGameSave()->getDataById(_GS_FIRST_IN_GAME);
	if(iFirst==1)
	{
		NTGameSave::sharedGameSave()->updateValue(_GS_FIRST_IN_GAME, 2);

		NTGameGuide* pGuiide = NTGameGuide::create();
		pGuiide->setControlLayer(this);
		getParent()->addChild(pGuiide, GAME_LAYER_GUIDE, GAME_LAYER_GUIDE);
		pGuiide->setTouchLock(true);
		initGuide();
		gameSound->playBackgroundMusic("sound/backgroud.ogg",true,1);
		getMapLayer()->showGuideRoad();
	}
	else
	{
		this->runAction(CCSequence::create(
			CCDelayTime::create(0.8f),
			CCCallFunc::create(this, callfunc_selector(NTControlLayer::goToRealGame)),
			NULL));
	}

}


void NTControlLayer::initGuide()
{
	this->runAction(CCSequence::create(
		CCDelayTime::create(2.1f),
		CCCallFuncND::create(this, callfuncND_selector(NTControlLayer::runGuide), 
		(void*)_GS_GUIDE_JUMP),//“˝µºÃ¯‘æ
		CCDelayTime::create(1.5f),
		CCCallFuncND::create(this, callfuncND_selector(NTControlLayer::runGuide), 
		(void*)_GS_GUIDE_SLIDE),//“˝µºœ¬ª¨
		CCDelayTime::create(1.0f),
		CCCallFunc::create(this, callfunc_selector(NTControlLayer::goToRealGame)),
		NULL));
}


void NTControlLayer::goToRealGame()
{
	NTGameGuide* pGuide = (NTGameGuide*)getParent()->getChildByTag(GAME_LAYER_GUIDE);
	if(pGuide!=NULL){
		pGuide->setTouchLock(false);
	}
	showGameBegin();
}


void NTControlLayer::runGuideCallBack( CCNode* pSender, void* pData )
{
	int pType = (int)pData;
	NTGameGuide* pGuide = (NTGameGuide*)getParent()->getChildByTag(GAME_LAYER_GUIDE);
	if(pType==_GS_GUIDE_SLIDE){
		pGuide->setTouchLock(false);
	}else{
		pGuide->setTouchLock(true);
	}
}

void NTControlLayer::runGuide( CCNode* pSender, void* pData )
{
	int pType = (int)pData;
	CCTouchDelegate* pDelegate;
	CCPoint pStart;
	CCPoint pEnd;
	float pDelayTime;
	int iMode;
	CCArray* pPointArray = NULL;
	switch(pType){
	case _GS_GUIDE_JUMP:
		{
			pDelegate = this;
			pStart = ccp(700, 65);
			pEnd = ccp(700, 65);
			pDelayTime = 1.5;
			iMode = GUIDE_TYPE_TAP;

		}break;
	case _GS_GUIDE_SLIDE:
		{
			pDelegate = this;
			pStart = ccp(90, 65);
			pEnd = ccp(90, 260);
			pDelayTime = 2.0;
			iMode = GUIDE_TYPE_LONG_TAP;
		}break;
	}

	NTGameGuide* pGuide = (NTGameGuide*)getParent()->getChildByTag(GAME_LAYER_GUIDE);
	pGuide->runGuide(pType, pDelegate, pStart, pEnd, pDelayTime, 
		CCCallFuncND::create(this, callfuncND_selector(NTControlLayer::runGuideCallBack), pData), iMode, pPointArray);
}

void NTControlLayer::showGameBegin()
{
 //	m_pActor->fly(30000);
 //	getMapLayer()->extraSpeed(30000.0f);

	if(m_bIsBegin){
		return;
	}
	CCSprite* pGameStart = CCSprite::create("guide/game_yxks.png");
	pGameStart->setPosition(ccp(800+pGameStart->getContentSize().width/2, 240));
	this->addChild(pGameStart, 1200);
	pGameStart->runAction(CCSequence::create(
		CCDelayTime::create(0.5f),
		CCEaseSineOut::create(CCMoveTo::create(0.4f, ccp(400, 240))),
		CCDelayTime::create(0.6f),
		CCEaseSineIn::create(CCMoveTo::create(0.4f, ccp(-pGameStart->getContentSize().width/2, 240))),
        //CCCallFunc::create(this, callfunc_selector(NTControlLayer::showGameBeginCallBack)),
		//Jerry
        CCCallFunc::create(this, callfunc_selector(NTControlLayer::menu_CallBack2)),
        CCCallFuncN::create(this, callfuncN_selector(NTControlLayer::removeSelfCallBack)),
		NULL));
}
//Jerry--Invalid
//void NTControlLayer::showGameBeginCallBack()
//{
//	m_bIsBegin = true;
//	//--------------”≈ª›ªÓ∂ØΩÁ√Ê
//	layer1 = CCLayer::create();
//	CCSprite* monyeBag = CCSprite::create("youHui/youHui.png");
//	CCMenuItemImage* button1 = CCMenuItemImage::create("youHui/buttonSuer.png","youHui/buttonSuer.png",this,menu_selector(NTControlLayer::menu_back1));
//
//	CCMenu* menu1 = CCMenu::create(button1,NULL);
//
//	button1->setAnchorPoint(ccp(0.5f,0.5f));
//	monyeBag->addChild(menu1);
//	menu1->setPosition(ccp(100,20));
//	layer1->addChild(monyeBag);
//	layer1->setPosition(ccp(400,240));
//	this->addChild(layer1,100);
//
//	CCSequence* ac = CCSequence::create(CCDelayTime::create(0.2f),CCScaleTo::create(0.2f,0.8f),
//		CCScaleTo::create(0.2f,1.2f),NULL);
//	button1->runAction(CCSequence::create(CCRepeat::create(ac,3),CCCallFunc::create(this, callfunc_selector(NTControlLayer::menu_CallBack)),NULL));
//}

void NTControlLayer::removeSelfCallBack( CCNode* pSender )
{
	pSender->removeFromParentAndCleanup(true);
}
////”≈ª›ªÓ∂Øµ„ª˜ ¬º˛£®»∑»œπ∫¬Ú£©
//void NTControlLayer::menu_back1(cocos2d::CCObject* p){
////	CCLog("ssssss");
//	CCNode* pNode = (CCNode*)p;
//	index = pNode->getTag();
//	//∏∂∑—Ω”ø⁄£®”≈ª›µ„ª˜∞¥≈•£©
//	//º«¬ºjava∑µªÿ ±”¶÷¥––µƒ∑Ω∑®
//	g_OncePayLibao.target = this;
//	g_OncePayLibao.func = (SYSDLG_CallFunc)(&NTControlLayer::setupdataLibaoState);
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //≈–∂œµ±«∞ «∑ÒŒ™Android∆ΩÃ®
//	JniMethodInfo minfo;//∂®“ÂJni∫Ø ˝–≈œ¢Ω·ππÃÂ
//	//getStaticMethodInfo ¥Œ∫Ø ˝∑µªÿ“ª∏ˆbool÷µ±Ì æ «∑Ò’“µΩ¥À∫Ø ˝
//	bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/PayWrapper","Cocos_order", "(I)V");
//
//	if (!isHave) {
//		CCLog("jni:¥À∫Ø ˝≤ª¥Ê‘⁄");
//	}else{
//		CCLog("jni:¥À∫Ø ˝¥Ê‘⁄");
//		//µ˜”√¥À∫Ø ˝
//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,10);
//	}
//	CCLog("jni-java∫Ø ˝÷¥––ÕÍ±œ");
//#endif
//}
//void NTControlLayer::setupdataLibaoState(int i){
//	count2=1;
//}
//”≈ª›ΩÁ√Ê“∆≥˝∂Ø◊˜
void NTControlLayer::menu_CallBack(){
	layer1->runAction(CCSequence::create(CCMoveTo::create(0.8f,ccp(400.0f,1500.0f)),
		CCCallFunc::create(this, callfunc_selector(NTControlLayer::menu_CallBack2)),NULL));

}
//”≈ª›ΩÁ√Ê“∆≥˝∂Ø◊˜µƒªÿµ˜∫Ø ˝
void NTControlLayer::menu_CallBack2(){
//	CCLog("ssssss");
	//º”‘ÿº”ÀŸ∞¥≈•
	CCMenuItemImage* game_ganin = CCMenuItemImage::create("youHui/game_jias.png","youHui/game_jias.png",this,menu_selector(NTControlLayer::menu_jiasu));
	jiasuBtn = CCMenu::create(game_ganin,NULL);
	this->addChild(jiasuBtn);
	jiasuBtn->setPosition(ccp(400,240));
	CCSequence* ac = CCSequence::create(CCDelayTime::create(0.2f),CCScaleTo::create(0.2f,0.8f),
		CCScaleTo::create(0.2f,1.2f),NULL);
	game_ganin->runAction(CCSequence::create(CCRepeat::create(ac,3),
		CCCallFunc::create(this, callfunc_selector(NTControlLayer::menu_jiasu2)),NULL));
}
//º”ÀŸ∞¥≈•µƒπ¶ƒ‹
void NTControlLayer::menu_jiasu(CCObject* p){
	//∏∂∑—Ω”ø⁄£®º”ÀŸ∞¥≈•£©
   
    
	//º«¬ºjava∑µªÿ ±”¶÷¥––µƒ∑Ω∑®
//	g_OncePayLibao.target = this;
//	g_OncePayLibao.func = (SYSDLG_CallFunc)(&NTControlLayer::setupdataLibaoState_2);
    //Jerry--Pause
    getGameHud()->pause(true);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //≈–∂œµ±«∞ «∑ÒŒ™Android∆ΩÃ®
	JniMethodInfo minfo;//∂®“ÂJni∫Ø ˝–≈œ¢Ω·ππÃÂ
	//getStaticMethodInfo ¥Œ∫Ø ˝∑µªÿ“ª∏ˆbool÷µ±Ì æ «∑Ò’“µΩ¥À∫Ø ˝
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/PayWrapper","Cocos_order", "(I)V");

	if (!isHave) {
		CCLog("jni:¥À∫Ø ˝≤ª¥Ê‘⁄");
	}else{
		CCLog("jni:¥À∫Ø ˝¥Ê‘⁄");
		//µ˜”√¥À∫Ø ˝
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,11);
	}
	CCLog("jni-java∫Ø ˝÷¥––ÕÍ±œ");
#endif

	CCMenu* ji = (CCMenu*)p;
	//»ÀŒÔ∑…œË
	ji->removeAllChildrenWithCleanup(true);
//	CCLog("ssss");
}
//void NTControlLayer::setupdataLibaoState_2(int i){
//    
//	
//}


//º”ÀŸ∞¥≈•µƒ∂Ø◊˜ªÿµ˜∫Ø ˝
void NTControlLayer::menu_jiasu2(){
	jiasuBtn->removeAllChildrenWithCleanup(true);
}
void NTControlLayer::purchaseCallBack(int i)
{
    //Jerry--BlankCopy
    getGameHud()->pause(false);
    switch (i) {
        case 11:
            count2=2;
            break;
         case 1:
        
                count2=4;
                sex = true;
            menu_close2_3();
                //m_pActor->setLife(true);
           
            
            break;
        case 13:
            m_bIsGameOver = false;
            menu_close2_2();
            break;
        default:
            break;
    }
    
}

void NTControlLayer::update_button(float dt){
//	CCLog("update_button");
   
	if(count2==3){
		count2=-1;
		//Ãÿª›¿Ò∞¸
		NTGameSave::sharedGameSave()->updataBuyheart(index1, true);
		int nSaveHeart =  NTGameSave::sharedGameSave()->getDataById(_GS_HEART);
		NTGameSave::sharedGameSave()->updateValue(_GS_HEART,nSaveHeart+80);
	}else if(count2==1){
		count2=-1;
		//”≈ª›¿Ò∞¸
		NTGameSave::sharedGameSave()->updataBuyheart(index, true);
		int nSaveHeart =  NTGameSave::sharedGameSave()->getDataById(_GS_HEART);
		NTGameSave::sharedGameSave()->updateValue(_GS_HEART,nSaveHeart+2);

		NTGameSave::sharedGameSave()->updateBuyjiaSu(index,true);
		int nSaveJiaSu = NTGameSave::sharedGameSave()->getDataById(_GS_JIASU);
		NTGameSave::sharedGameSave()->updateValue(_GS_JIASU,nSaveJiaSu+3);
	}else if(count2==4){
		if(sex){
			count2=-1;
			//∏¥ªÓ
//            m_pActor->setLife(true);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//            JniMethodInfo minfo;
//            bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/PayWrapper","ShowLog", "(Z)V");
//            
//            if (!isHave) {
//                CCLog("jni:¥À∫Ø ˝≤ª¥Ê‘⁄");
//            }else{
//                CCLog("jni:¥À∫Ø ˝¥Ê‘⁄");
//                //µ˜”√¥À∫Ø ˝
//                minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,m_pActor->getLife());
//            }
//            CCLog("jni-java∫Ø ˝÷¥––ÕÍ±œ");
//            
//            
//#endif
            if(NTGameSave::sharedGameSave()->getDataById(_GS_TASKTHREE)==9){
                NTGameSave::sharedGameSave()->updateValue(_GS_TASKTHREE_FINISH,1);
            }
			m_pActor->removeAllChildrenWithCleanup(true);
			m_pActor = NTActor::createActor(NTGameSave::sharedGameSave()->getHeroSelect());
			if(m_bIsGameOver){m_bIsGameOver = false;}
			if(count1!=1){count1=1;}
            //Jerry
            m_pActor->setScore(m_TempScore);
			m_pActor->setIsOnBlock(false);
			//»√Ω«…´µƒ◊¥Ã¨÷ÿ÷√Œ™≈‹
			m_pActor->updateState(STATE_RUN);
			m_pActor->setMapLayer(getMapLayer());
			//”Œœ∑÷˜≥°æ∞µƒ¡Ω∏ˆøÿ÷∆∞¥≈•
			menu_reset(NULL);
			m_pActor->setIsAutoPlay(false);
			m_pActor->setEnemy(m_pActorNpc);
			m_pActorNpc->setEnemy(m_pActor);
			m_pActorNpc->setIsAutoPlay(true);

			this->addChild(m_pActor);
			m_pActor->runAction(CCMoveTo::create(1,ccp(150,280)));
			m_pActor->fly(5.0);
		}else{
			m_bIsGameOver = false;
			menu_close2_2();
		}
		

	}else if(count2==2){
        
		count2=-1;
		//º”ÀŸ
        
		m_pActor->fly(5.0f,true);
		m_pMapLayer->extraSpeed(10.0f);
	}
}
void NTControlLayer::revive()
{
    m_pActor->removeAllChildrenWithCleanup(true);
    m_pActor = NTActor::createActor(NTGameSave::sharedGameSave()->getHeroSelect());
    if(m_bIsGameOver){m_bIsGameOver = false;}
    if(count1!=1){count1=1;}
    //Jerry
    m_pActor->setScore(m_TempScore);
    m_pActor->setIsOnBlock(false);
    //»√Ω«…´µƒ◊¥Ã¨÷ÿ÷√Œ™≈‹
    m_pActor->updateState(STATE_RUN);
    m_pActor->setMapLayer(getMapLayer());
    //”Œœ∑÷˜≥°æ∞µƒ¡Ω∏ˆøÿ÷∆∞¥≈•
    menu_reset(NULL);
    m_pActor->setIsAutoPlay(false);
    m_pActor->setEnemy(m_pActorNpc);
    m_pActorNpc->setEnemy(m_pActor);
    m_pActorNpc->setIsAutoPlay(true);
    
    this->addChild(m_pActor);
    m_pActor->runAction(CCMoveTo::create(1,ccp(150,280)));
    m_pActor->fly(5.0);
}















