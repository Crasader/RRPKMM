#include "NTStart.h"
#include "NTMenuItem.h"
#include "NTConstants.h"
#include "NTSet.h"
#include "NTHeart.h"
#include "NTHero.h"
#include "NTSign.h"
#include "NTTask.h"
#include "HelloWorldScene.h"
#include "NTRank.h"
#include "AnimatePacker.h"
#include "NTGameScene.h"
#include "NTGameSave.h"
#include "NTPet.h"
#include "NTSharedJsonData.h"
#include "NTJniHelper.h"
#include "Assistant.h"
#include"NTGameSound.h"
#include "BloodTool.h"
#include "NTGift.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

static SDialogContent g_OncePayLibao;

extern "C" {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void Java_com_ibirdgame_archirun_PayWrapper_BuyItemSucceed(JNIEnv* env, jobject thiz, jint id)
    {
        switch (id) {
            case 0:
                NTGameSave::sharedGameSave()->updateValue(_GS_HEART,NTGameSave::sharedGameSave()->getDataById(_GS_HEART)+5);
                break;
            case 1:
                NTGameSave::sharedGameSave()->updateValue(_GS_HEART,NTGameSave::sharedGameSave()->getDataById(_GS_HEART)+20);
                break;
            case 2:
                NTGameSave::sharedGameSave()->updateValue(_GS_HEART,NTGameSave::sharedGameSave()->getDataById(_GS_HEART)+40);
                break;
            case 3:
                NTGameSave::sharedGameSave()->updateValue(_GS_HEART_COUNTLESS, 1);
                break;
            case 4:
                NTGameSave::sharedGameSave()->updateBuyHero(_GS_HERO_IS_BUY_2, true);
                break;
            case 5:
                NTGameSave::sharedGameSave()->updateBuyHero(_GS_HERO_IS_BUY_3, true);
                break;
            case 6:
                NTGameSave::sharedGameSave()->updateBuyPet(_GS_PET_IS_BUY_1, true);
                break;
            case 7:
                NTGameSave::sharedGameSave()->updateBuyPet(_GS_PET_IS_BUY_2, true);
                break;
            case 8:
                NTGameSave::sharedGameSave()->updateBuyPet(_GS_PET_IS_BUY_3, true);
                break;
            case 9:
             NTGameSave::sharedGameSave()->updateValue(_GS_GOLD,NTGameSave::sharedGameSave()->getDataById(_GS_GOLD)+999999);
                break;
            case 10:
                NTGameSave::sharedGameSave()->updateValue(_GS_HEART,NTGameSave::sharedGameSave()->getDataById(_GS_HEART)+3);
                NTGameSave::sharedGameSave()->updateValue(_GS_GOLD,NTGameSave::sharedGameSave()->getDataById(_GS_GOLD)+10000);
                
                break;
            case 11:
                //Music on
                NTGameSound::sharedEngine()->setBackgroundMusicVolume(1);
                break;
            case 12:
                //Music off
                NTGameSound::sharedEngine()->setBackgroundMusicVolume(0);
                break;
            default:
                break;
        }
    }
#endif
}
extern "C" {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void Java_com_ibirdgame_archirun_PayWrapper_buyGift(JNIEnv* env, jobject thiz, jint id)
	{
		CCObject* target = g_OncePayLibao.target;
		SYSDLG_CallFunc pFunc = g_OncePayLibao.func;
		(target->*pFunc)(id);
	}
#endif
}

bool NTStart::init()
{
    
    scheduleUpdate();
    isFly=true;
	bool Res = false;
	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0,0,0, 160)));
		initValues();
		initUI();
		//schedule(schedule_selector(NTStart::updateForGold), 1.0f);
		//unschedule(schedule_selector(NTStart::updateForGold), 1.0f);
		
		Res = true;
	} while (0);

	return Res;
}

void NTStart::onEnter()
{
    
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, PRIORITY_NTLAYER_LEVEL_1,true);


}


void NTStart::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayerColor::onExit();
}


void NTStart::onEnterTransitionDidFinish()
{
    NTGameSound::sharedEngine()->playBackgroundMusic("sound/bgm_lobby.ogg",true,NTGameSave::sharedGameSave()->isSound);
	CCLayerColor::onEnterTransitionDidFinish();

}


void NTStart::initValues()
{
	m_pBg = NULL;
	m_bIsTouchMu = false;
	m_pMenu = NULL;

	m_pExtraHeartText = NULL;
	m_bIsInAnimate = false;

}
void NTStart::loadRes()
{
	//
	AnimatePacker::getInstance()->loadAnimations("start/start_animate.xml");
}
void NTStart::initUI()
{
	loadRes();

//	NTGameSound::sharedEngine()->initPlayer();
//	initPlayer
	tinyxml2::XMLDocument pdocx;
	tinyxml2::XMLElement* pSurface;
	unsigned char* mybuf = NULL;
	unsigned long bufsize = 0;
	mybuf = CCFileUtils::sharedFileUtils()->getFileData(START_XML_FILE,"r",&bufsize);
	if (!mybuf){
		return;
	}
	pdocx.Parse((const char*)mybuf,bufsize);
	if (pdocx.NoChildren()){
		return;
	}
	pSurface = pdocx.FirstChildElement();

	
	if(pSurface==NULL){
		return;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	while(pSurface)
	{
		int posx = 0;	//
		int posy = 0;	//
		int pid = 0;	//
		pSurface->QueryIntAttribute("posx",&posx);
		pSurface->QueryIntAttribute("posy",&posy);
		pSurface->QueryIntAttribute("pid",&pid);

		char filestr[80] = {0};
		sprintf(filestr,"%s",pSurface->Name());

		//=====================================================================UI===========================================//
		//=====================================================================UI===========================================//
		//≥ı ºªØ±≥æ∞
		if(strcmp(pSurface->Name(),"bj.png") == 0)
		{
			m_pBg = CCSprite::createWithSpriteFrameName(filestr);
			m_pBg->setPosition(ccp(winSize.width/2, winSize.height/2));
			this->addChild(m_pBg);

			//≥ı ºªØMENU
			m_pMenu = CCMenu::create();
			m_pMenu->setPosition(CCPointZero);
			m_pMenu->setTouchEnabled(false);
			m_pBg->addChild(m_pMenu,100);

			//≥ı ºªØ≈≈––
			NTRank *pRank = NTRank::create();
			m_pBg->addChild(pRank,1);
			pRank->setPositionY(-20);
			setRankLayer(pRank);

		}
		//ø™ º∞¥≈•
		else if(strcmp(pSurface->Name(),"start_ks.png") == 0){

			CCSprite* pSprite1 = CCSprite::createWithSpriteFrameName(filestr);
			CCSprite* pSprite2 = CCSprite::createWithSpriteFrameName(filestr);

			NTMenuItemSprite* pMenuItem = NTMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(NTStart::menu_start));
			pMenuItem->setPosition(ccp(posx,posy));
			m_pMenu->addChild(pMenuItem);
		}
		//∞Æ–ƒ
		else if(strcmp(pSurface->Name(),"start_x.png") == 0){
			m_pExtraHeartText = CCLabelAtlas::create("0","start/start_jbsz.png",14,21,'0');
			m_pExtraHeartText->setVisible(false);
            //Jerry
            m_pHeartCountless = CCSprite::create("heart/wuxian.png");
            m_pHeartCountless->setVisible(false);
            m_pBg->addChild(m_pHeartCountless);
            m_pHeartCountless->setPosition(ccp(posx+220,posy));
            
            //Jerry--HeartSchedule
            m_pMin = CCLabelAtlas::create("01","start/start_jbsz.png",14,21,'0');
            m_pMin->setPosition(ccp(posx+173,posy-10));
            m_pSec = CCLabelAtlas::create("01","start/start_jbsz.png",14,21,'0');
            m_pSec->setPosition(ccp(posx+210,posy-10));
            m_pPoint = CCLabelAtlas::create(":","start/start_jbsz.png",14,21,'0');
            m_pPoint->setPosition(ccp(posx+200,posy-8));
            m_pPoint->setScale(0.8);
            m_pMax =CCSprite::create("start/start_xmax.png");
            m_pMax->setPosition(ccp(posx+217,posy));
           // m_pMax->setScale(0.8);
            
            m_pBg->addChild(m_pMin);
            m_pBg->addChild(m_pSec);
            m_pBg->addChild(m_pPoint);
            m_pBg->addChild(m_pMax);

            
			m_pBg->addChild(m_pExtraHeartText);
			m_pExtraHeartText->setPosition(ccp(posx+200,posy-10));
			for(int j=0;j<5;j++){
				CCSprite *pHeart = CCSprite::createWithSpriteFrameName(filestr);
				m_pBg->addChild(pHeart,101);
				pHeart->setPosition(ccp(posx+j*(pHeart->getContentSize().width+5),posy));
				m_pHeart[j]= pHeart;
				pHeart->setVisible(false);
			}
//			int nSaveHeart = NTGameSave::sharedGameSave()->getDataById(_GS_HEART);
//			updateHeartView(nSaveHeart);
			
		}
		//π∫¬Ú
		else if(strcmp(pSurface->Name(),"start_dbj.png") == 0){

			CCSprite* pSprite1 = CCSprite::createWithSpriteFrameName(filestr);
			CCSprite* pSprite2 = CCSprite::createWithSpriteFrameName(filestr);
			//¬ÚΩ±“
			if(pid == 1){
				//Ω±“ ˝÷µ
				int nGold = NTGameSave::sharedGameSave()->getDataById(_GS_GOLD);
				m_pGoldText  = CCLabelAtlas::create(CCString::createWithFormat("%d",nGold)->getCString(),"start/start_jbsz1.png",15,23,'0');
				m_pBg->addChild(m_pGoldText);
				m_pGoldText->setAnchorPoint(ccp(0.5,0.5));
				m_pGoldText->setPosition(ccp(posx-110,posy));

				pMenuItem = NTMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(NTStart::menu_gold));
			}//¬Ú∞Æ–ƒ
			else if(pid == 2){
				pMenuItem = NTMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(NTStart::menu_heart));
                pMenuItem->setPosition(ccp(posx,posy));
                m_pMenu->addChild(pMenuItem);
			}
			

			
		}
		//«©µΩ∞¥≈•
		else if(strcmp(pSurface->Name(),"daily.png") == 0){

			CCSprite* pSprite1 = CCSprite::createWithSpriteFrameName(filestr);
			CCSprite* pSprite2 = CCSprite::createWithSpriteFrameName(filestr);

			NTMenuItemSprite* pMenuItem = NTMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(NTStart::menu_sign));
			pMenuItem->setPosition(ccp(posx,posy));
			m_pMenu->addChild(pMenuItem);
		}
		//…Ë÷√
		else if(strcmp(pSurface->Name(),"start_shzh.png") == 0){

			CCSprite* pSprite1 = CCSprite::createWithSpriteFrameName(filestr);
			CCSprite* pSprite2 = CCSprite::createWithSpriteFrameName(filestr);

			NTMenuItemSprite* pMenuItem = NTMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(NTStart::menu_set));
			pMenuItem->setPosition(ccp(posx,posy));
			m_pMenu->addChild(pMenuItem);
            
            CCActionInterval *jumpTo =CCJumpBy::create(1, ccp(0,0),10,4);
            CCActionInterval *stay =CCScaleBy::create(3, 1);
            CCFiniteTimeAction* seq = CCSequence::create(stay,jumpTo,NULL);
            CCActionInterval * repeatForever =CCRepeatForever::create((CCActionInterval* )seq);
            pMenuItem->runAction(repeatForever);
		}
		//«©µΩ
		else if(strcmp(pSurface->Name(),"start_lw.png") == 0){

		/*	CCSprite* pSprite1 = CCSprite::createWithSpriteFrameName(filestr);
			CCSprite* pSprite2 = CCSprite::createWithSpriteFrameName(filestr);

			NTMenuItemSprite* pMenuItem = NTMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(NTStart::menu_gift));
			pMenuItem->setPosition(ccp(posx,posy));
			m_pMenu->addChild(pMenuItem);*/
		}
		//”¢–€
		else if(strcmp(pSurface->Name(),"start_js.png") == 0){

			CCSprite* pSprite1 = CCSprite::createWithSpriteFrameName(filestr);
			CCSprite* pSprite2 = CCSprite::createWithSpriteFrameName(filestr);

			NTMenuItemSprite* pMenuItem = NTMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(NTStart::menu_hero));
			pMenuItem->setPosition(ccp(posx,posy));
			m_pMenu->addChild(pMenuItem);
            
            CCActionInterval *jumpTo =CCJumpBy::create(1, ccp(0,0),10,4);
            CCActionInterval *stay =CCScaleBy::create(3, 1);
            CCFiniteTimeAction* seq = CCSequence::create(jumpTo,stay,NULL);
            CCActionInterval * repeatForever =CCRepeatForever::create((CCActionInterval* )seq);
            pMenuItem->runAction(repeatForever);
		}
		//≥ËŒÔ
		else if(strcmp(pSurface->Name(),"start_chw.png") == 0){

			CCSprite* pSprite1 = CCSprite::createWithSpriteFrameName(filestr);
			CCSprite* pSprite2 = CCSprite::createWithSpriteFrameName(filestr);

 			NTMenuItemSprite* pMenuItem = NTMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(NTStart::menu_pet));
 			pMenuItem->setPosition(ccp(posx,posy));
 			m_pMenu->addChild(pMenuItem);
            
            
            CCActionInterval *jumpTo =CCJumpBy::create(1, ccp(0,0),10,4);
            CCActionInterval *stay =CCScaleBy::create(2, 1);
           CCFiniteTimeAction* seq = CCSequence::create(stay,jumpTo,NULL);
            CCActionInterval * repeatForever =CCRepeatForever::create((CCActionInterval* )seq);
            pMenuItem->runAction(repeatForever);
		}
		//±æ¿¥ «»ŒŒÒ£¨∏ƒ≥…«©µΩ¡À
		else if(strcmp(pSurface->Name(),"start_rw.png") == 0){

			CCSprite* pSprite1 = CCSprite::createWithSpriteFrameName(filestr);
			CCSprite* pSprite2 = CCSprite::createWithSpriteFrameName(filestr);

			NTMenuItemSprite* pMenuItem = NTMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(NTStart::menu_sign));
			pMenuItem->setPosition(ccp(posx,posy));
			m_pMenu->addChild(pMenuItem);
            
            
            CCActionInterval *jumpTo =CCJumpBy::create(1, ccp(0,0),10,4);
            CCActionInterval *stay =CCScaleBy::create(2, 1);
            CCFiniteTimeAction* seq = CCSequence::create(jumpTo,stay,NULL);
            CCActionInterval * repeatForever =CCRepeatForever::create((CCActionInterval* )seq);
            pMenuItem->runAction(repeatForever);
		}
		//Ω±“∞¥≈•
		//∆‰À˚Õº∆¨
		else
		{

			CCSprite* pSprite = CCSprite::createWithSpriteFrameName(filestr);
			pSprite->setPosition(ccp(posx, posy));
			m_pBg->addChild(pSprite);

			//»Áπ˚ «—€æ¶
			if(strcmp(pSurface->Name(),"start_beye1.PNG") == 0 ){
				pSprite->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCDelayTime::create(2.0f),
					AnimatePacker::getInstance()->getAnimate("boy_eye"))));
			}
			if(strcmp(pSurface->Name(),"start_geye1.PNG") == 0){
				pSprite->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCDelayTime::create(2.5f),
					AnimatePacker::getInstance()->getAnimate("girl_eye"))));
			}
			//»Áπ˚ «ŒßΩÌ
			if(strcmp(pSurface->Name(),"start_gj1.png") == 0){
				pSprite->runAction(CCRepeatForever::create(AnimatePacker::getInstance()->getAnimate("girl_gj")));
			}

		}
		//d=====================================================================UI===========================================//
		//=====================================================================UI===========================================//

		pSurface = pSurface->NextSiblingElement();
	}
    //Jerry--Exit
    CCSprite *pExit=CCSprite::create("share_button/nn.png");
    NTMenuItemSprite *Exit=NTMenuItemSprite::create(pExit,pExit,this,menu_selector(NTStart::menu_exit));
    Exit->setPosition(ccp(750,420));
    m_pMenu->addChild(Exit);
    //Jerry--MoreGame
    CCSprite *pMore=CCSprite::create("share_button/more.png");
    NTMenuItemSprite *More=NTMenuItemSprite::create(pMore,pMore,this,menu_selector(NTStart::menu_more));
    More->setPosition(ccp(750,360));
    //m_pMenu->addChild(More);
	// «∑Ò«©µΩ
	libao_sp= CCSprite::create("gift/gift_2.png");
	ismag = CCMenuItemSprite::create(libao_sp,libao_sp,this,menu_selector(NTStart::menu_gift));
	ismag->setPosition(ccp(45,320));
	m_pMenu->addChild(ismag);
	libao_sp->setVisible(true);
    //Jerry--Action
    CCActionInterval *scaleto =CCScaleTo::create(0.4, 1.05);
    CCActionInterval *Rescaleto =CCScaleTo::create(0.4, 1);
    CCFiniteTimeAction* seq = CCSequence::create(scaleto,Rescaleto,NULL);
    CCActionInterval * repeatForever =CCRepeatForever::create((CCActionInterval* )seq);
     libao_sp->runAction(repeatForever);
    
	int nCurDay = NTGameSave::sharedGameSave()->getSignDay();
    //Jerry
	// nCurDay= 1;
	if(nCurDay >= 0){
		//libao_sp->setVisible(true);
		//ismag->runAction(CCMoveTo::create(0.8f,ccp(45,200)));
		NTSign* pLayer = NTSign::create();
		pLayer->setSelectDay(nCurDay);
		//NTSharedJsonData::sharedJsonData()->setSignDay(nCurDay);
		NTGameSave::sharedGameSave()->updateValue(_GS_SIGN_TIMES,nCurDay);
		pLayer->bornOnLayer(this);
		
	}
	// «∑Ò–Ë“™◊¢≤·√˚◊÷
// 	if(!NTGameSave::sharedGameSave()->IsRegister()){
// 		NTJniHelper::sharedJniHelper()->setRenameDelegate(this);
// 		CCLog("do register!");
// 		NTJniHelper::sharedJniHelper()->registerName();
// 	}

//	ismag = CCMenuItemImage::create("gift/gift_2.png","gift/gift_2.png",this,menu_selector(NTStart::menu_gift));
//Jerry
    if (NTGameSave::sharedGameSave()->getDataById(_GS_HEART_COUNTLESS)==1){
        pMenuItem->setVisible(false);
        pMenuItem->setEnabled(false);
    }
	this->schedule(schedule_selector(NTStart::update_meiri),0.2f);
}
// ¬º˛º‡Ã˝µƒπ˝≥Ã
bool NTStart::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (!m_bIsTouchMu)
	{
		m_bIsTouchMu = m_pMenu->ccTouchBegan(pTouch,pEvent);
	}

	return true;
}

void NTStart::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchMoved(pTouch,pEvent);
	}
}

void NTStart::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchEnded(pTouch,pEvent);
		m_bIsTouchMu = false;
	}
}

void NTStart::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchCancelled(pTouch,pEvent);
		m_bIsTouchMu = false;
	}
}

void NTStart::menu_close( CCObject* pRender )
{
	this->runAction(CCSequence::create(CCMoveTo::create(0.2f,ccp(0,600)),
		CCCallFunc::create(this,callfunc_selector(NTStart::callback_close)),NULL));
}


void NTStart::bornOnScene()
{
	this->setPosition(ccp(0,600));
	this->runAction(CCMoveTo::create(0.2f, ccp(0, 0)));
}
void NTStart::menu_exit(CCObject* pRender)
{
//     CCDirector::sharedDirector()->end();
//   // exit(0);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/PayWrapper","Cocos_exit", "()V");
    
    if (!isHave) {
        CCLog("jni:!isHave");
    }else{
        CCLog("jni:isHave");
        //µ˜”√¥À∫Ø ˝
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
    CCLog("jni-java-succ");
#endif
}
void NTStart::menu_more(CCObject* pRender)
{
//    CCDirector::sharedDirector()->end();
//    // exit(0);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;//∂®“ÂJni∫Ø ˝–≈œ¢Ω·ππÃÂ
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/PayWrapper","Cocos_more", "()V");
    
    if (!isHave) {
        CCLog("jni:!isHave");
    }else{
        CCLog("jni:isHave");
        //µ˜”√¥À∫Ø ˝
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
    CCLog("jni-java-succ");
#endif
    
}
void NTStart::callback_close()
{
	removeFromParentAndCleanup(true);
}
//ø™ º”Œœ∑ΩÁ√Ê∞¥≈•
void NTStart::menu_start( CCObject* pRender )
{
    if (NTGameSave::sharedGameSave()->getDataById(_GS_HEART_COUNTLESS)==1) {
	//if(true){
        playHeartFly(4);
        
        NTGameSound::sharedEngine()->playEffectById(SOUND_TOWER_UPGRADE,true,
                                                    NTGameSave::sharedGameSave()->isSound);
        return;
    }
	int nSaveHeart = NTGameSave::sharedGameSave()->getDataById(_GS_HEART);
	if(nSaveHeart <=0){
        //Jerry--Edit
        NTHeart* pLayer = NTHeart::create();
        /*this->addChild(pLayer);*/
        pLayer->bornOnLayer(this);
		return;
	}
	if(m_bIsInAnimate){
		return;
	}
   
    isFly=false;
	nSaveHeart -=1;//∞Æ–ƒ--
	NTGameSave::sharedGameSave()->updateValue(_GS_HEART,nSaveHeart);//ø…ƒ‹ «Ω´œ÷‘⁄µƒ∞Æ–ƒ ˝¥Êµµ
	
	int flyId = 0;
	if(nSaveHeart<5){
		flyId = nSaveHeart;
	}else{
		flyId = 4;
	}
	playHeartFly(flyId);
	
	NTGameSound::sharedEngine()->playEffectById(SOUND_TOWER_UPGRADE,true,
		NTGameSave::sharedGameSave()->isSound);
	
}

//«©µΩΩÁ√Ê∞¥≈•
void NTStart::menu_sign( CCObject* pRender )
{
	NTSign* pLayer = NTSign::create();
    this->addChild(pLayer);
    pLayer->setPosition(ccp(0,600));
    pLayer->runAction(CCMoveTo::create(0.2f, ccp(0, 0)));
}
//…Ë÷√ΩÁ√Ê∞¥≈•
void NTStart::menu_set( CCObject* pRender )
{
	NTSet* pLayer = NTSet::create();
    this->addChild(pLayer);
    pLayer->setPosition(ccp(0,600));
    pLayer->runAction(CCMoveTo::create(0.2f, ccp(0, 0)));
}
//¿Ò∞¸ΩÁ√Ê∞¥≈•
void NTStart::menu_gift( CCObject* pRender )
{
//	//libao_sp->setVisible(false);
//	//laye = CCLayer::create();
//	meiri = CCSprite::create("gift/gift_1.png");
//	//meiri->setScale(0.8f);
//	m_pBg->addChild(meiri,90);
//    //this->addChild(laye);
//
//	img = CCMenuItemSprite::create(CCSprite::create("gift/gift_3.png"),CCSprite::create("gift/gift_3.png"),
//		this,menu_selector(NTStart::menu_back_libao));
//    img->setScale(1.25f);
//	img_caca = CCMenuItemSprite::create(CCSprite::create("gift/gift_4.png"),CCSprite::create("gift/gift_4.png"),
//		this,menu_selector(NTStart::menu_back_libao_caca));
//   // img_caca->setScale(0.8f);
//	m_pMenu->addChild(img);
//	m_pMenu->addChild(img_caca);
//
//	meiri->setPosition(ccp(400,250));
//	img->setPosition(ccp(400,150));
//	img_caca->setPosition(ccp(580,380));

NTGift* pLayer = NTGift::create();
this->addChild(pLayer);
pLayer->setPosition(ccp(0,0));
}
//------------------------------
void NTStart::menu_back_libao(CCObject* pRender){
    //Jerry

	g_OncePayLibao.target = this;
	g_OncePayLibao.func = (SYSDLG_CallFunc)(&NTStart::setupdataLibaoState);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //≈–∂œµ±«∞ «∑ÒŒ™Android∆ΩÃ®
	JniMethodInfo minfo;//∂®“ÂJni∫Ø ˝–≈œ¢Ω·ππÃÂ
	//getStaticMethodInfo ¥Œ∫Ø ˝∑µªÿ“ª∏ˆbool÷µ±Ì æ «∑Ò’“µΩ¥À∫Ø ˝
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/PayWrapper","Cocos_order", "(I)V");

	if (!isHave) {
		CCLog("jni:¥À∫Ø ˝≤ª¥Ê‘⁄");
	}else{
		CCLog("jni:¥À∫Ø ˝¥Ê‘⁄");
		//µ˜”√¥À∫Ø ˝
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,10);
	}
	CCLog("jni-java∫Ø ˝÷¥––ÕÍ±œ");
#endif

// 	libao_sp->setVisible(true);
// 	ismag->runAction(CCMoveTo::create(0.8f,ccp(45,2000)));
// 	//	this->removeAllChildrenWithCleanup(false);
 	pNode1 = (CCNode*)pRender;
// 	//	int	index = pNode->getTag();
// 	NTGameSave::sharedGameSave()->updateBuyjiaSu(pNode->getTag(),true);
// 	int nSaveJiaSu = NTGameSave::sharedGameSave()->getDataById(_GS_JIASU);
// 	NTGameSave::sharedGameSave()->updateValue(_GS_JIASU,nSaveJiaSu+1);
// 
// 	NTGameSave::sharedGameSave()->updataBuyheart(pNode->getTag(), true);
// 	int nSaveHeart =  NTGameSave::sharedGameSave()->getDataById(_GS_HEART);
// 	NTGameSave::sharedGameSave()->updateValue(_GS_HEART,nSaveHeart+1);
// 	//	closeSelf();
// 	CCLog("hhh");
// 	meiri->runAction(CCMoveTo::create(0.8f,ccp(380,1500)));	
// 	img->runAction(CCMoveTo::create(0.8f,ccp(380,1500)));
// 	img_caca->runAction(CCMoveTo::create(0.8f,ccp(380,1500)));
}
void NTStart::setupdataLibaoState(int i){
    if (i!=0) {
        const1 = 1;
    }
	
}

void NTStart::update_meiri(float f){
//	CCLog("update_meiri");
	if(const1==1){
		const1=-1;
		libao_sp->setVisible(true);
		//ismag->runAction(CCMoveTo::create(0.8f,ccp(45,2000)));
		//	this->removeAllChildrenWithCleanup(false);
		//CCNode* pNode = (CCNode*)pRender;
		//	int	index = pNode->getTag();
//		NTGameSave::sharedGameSave()->updateBuyjiaSu(pNode1->getTag(),true);
//		int nSaveJiaSu = NTGameSave::sharedGameSave()->getDataById(_GS_JIASU);
//		NTGameSave::sharedGameSave()->updateValue(_GS_JIASU,nSaveJiaSu+1);
//      Jerry
       // NTGameSave::sharedGameSave()->updataBuyheart(pNode1->getTag(), true);
        int nSaveGold =  NTGameSave::sharedGameSave()->getDataById(_GS_GOLD);
        NTGameSave::sharedGameSave()->updateValue(_GS_GOLD,nSaveGold+10000);
        
		NTGameSave::sharedGameSave()->updataBuyheart(pNode1->getTag(), true);
		int nSaveHeart =  NTGameSave::sharedGameSave()->getDataById(_GS_HEART);
		NTGameSave::sharedGameSave()->updateValue(_GS_HEART,nSaveHeart+3);
		//	closeSelf();
        this->updateHeartView(NTGameSave::sharedGameSave()->getDataById(_GS_HEART));
		meiri->runAction(CCMoveTo::create(0.8f,ccp(380,1500)));	
		img->runAction(CCMoveTo::create(0.8f,ccp(380,1500)));
		img_caca->runAction(CCMoveTo::create(0.8f,ccp(380,1500)));
		
	}

}

void NTStart::menu_back_libao_caca(CCObject* pRender){
//	libao_sp->setVisible(true);
//	libao_sp->runAction(CCMoveTo::create(0.8f,ccp(45,2000)));
	CCLog("gggg");
//	CCLayer* sp = (CCLayer*)pRender;
	meiri->runAction(CCMoveTo::create(0.8f,ccp(380,1500)));	
	img->runAction(CCMoveTo::create(0.8f,ccp(380,1500)));
	img_caca->runAction(CCMoveTo::create(0.8f,ccp(380,1500)));
	meiri->removeAllChildrenWithCleanup(true);
	img->removeAllChildrenWithCleanup(true);
	img_caca->removeAllChildrenWithCleanup(true);
}
//”¢–€ΩÁ√Ê∞¥≈•
void NTStart::menu_hero( CCObject* pRender )
{
	NTHero* pLayer = NTHero::create();
	//this->addChild(pLayer);
	pLayer->bornOnLayer(this);
}
//≥ËŒÔΩÁ√Ê∞¥≈•
void NTStart::menu_pet( CCObject* pRender )
{
	NTPet* pPet= NTPet::create();
	//this->addChild(pPet);
	pPet->bornOnLayer(this);
}
//∞Æ–ƒΩÁ√Ê∞¥≈•
void NTStart::menu_heart( CCObject* pRender )
{
    //Jerry--Edit
	NTHeart* pLayer = NTHeart::create();
	this->addChild(pLayer);
    pLayer->setPosition(ccp(0,600));
    pLayer->runAction(CCMoveTo::create(0.2f, ccp(0, 0)));
}

void NTStart::menu_props( CCObject* pRender )
{
	CCLog("buy");
}

cocos2d::CCScene* NTStart::scene()
{
	// 'scene' is an autorelease object
	CCScene *pScene = CCScene::create();

	// 'layer' is an autorelease object
	NTStart *layer = NTStart::create();

	// add layer as a child to scene
	pScene->addChild(layer);
	// return the scene
	return pScene;
}
//¬ÚΩ±“
void NTStart::menu_gold( CCObject *pRender )
{
	CCLog("buy gold");
}
//∏¸–¬∞Æ–ƒµƒ ”Õº
void NTStart::updateHeartView( int nHeart )
{
//	for(int i=0;i<5;i++){
//		if(i<nHeart){
//			m_pHeart[i]->setVisible(true);
//		}else{
//			m_pHeart[i]->setVisible(false);
//		}
//	}
    if (NTGameSave::sharedGameSave()->getDataById(_GS_HEART_COUNTLESS)==1) {
        m_pExtraHeartText->setVisible(false);
        m_pHeartCountless->setVisible(true);
        //Jerry
        pMenuItem->setVisible(false);
        pMenuItem->setEnabled(false);
        return;
        }
	if(nHeart >5){
		m_pExtraHeartText->setVisible(true);
		m_pExtraHeartText->setString(CCString::createWithFormat(";%d",nHeart-5)->getCString());
        }
	else{
		m_pExtraHeartText->setVisible(false);
	}
}
//≤˙…˙µ¿æﬂµƒ∑Ω∑® ”√µƒ «±¥»˚∂˚«˙œﬂ
void NTStart::playHeartFly(int heartId)
{
	m_bIsInAnimate = true;
	CCPoint pt =m_pHeart[heartId]->getPosition();
	ccBezierConfig bezier;
	bezier.controlPoint_1 = ccp(pt.x+100,pt.y);
	bezier.controlPoint_2 = ccp(640,53);
	bezier.endPosition	= ccp(620,53);
	CCFiniteTimeAction *beizerMove = CCBezierTo::create(2.0f/4,bezier);
	CCCallFunc *callNext = CCCallFunc::create(this,callfunc_selector(NTStart::playHeartFlyCallBack));
	m_pHeart[heartId]->runAction(CCSequence::create(beizerMove,callNext,NULL));
}
void NTStart::playHeartFlyCallBack()
{
    isFly=true;
	m_bIsInAnimate = false;
	CCDirector::sharedDirector()->replaceScene(NTGameScene::scene());
}

void NTStart::menu_task( CCObject *pRender )
{
	NTTask* pLayer = NTTask::create();

	pLayer->bornOnLayer(this);
}
//∏˙–¬Ω±“
//void NTStart::updateForGold( float dt )
//{
//	m_pGoldText->setString(CCString::createWithFormat("%d", NTGameSave::sharedGameSave()->getDataById(_GS_GOLD))->getCString());
//   
//    
////    m_pExtraHeartText->setString(CCString::createWithFormat("%d", NTGameSave::sharedGameSave()->getDataById(_GS_HEART))->getCString());
//}

//void NTStart::updateGoldView()
//{
//	m_pGoldText->setString(CCString::createWithFormat("%d", NTGameSave::sharedGameSave()->getDataById(_GS_GOLD))->getCString());
//}

void NTStart::registerMyName( std::string strName )
{
	m_sName = strName;
	this->scheduleOnce(schedule_selector(NTStart::toSaveMyName),0.1f);
}
//±£¥Ê◊‘º∫µƒ√˚◊÷
void NTStart::toSaveMyName( float dt )
{
	NTGameSave::sharedGameSave()->setRegister(true);
	NTSharedJsonData::sharedJsonData()->saveName(m_sName);
	m_pRankLayer->updateMyNameView(m_sName);
}

void NTStart::update(float dt)
{
      m_pGoldText->setString(CCString::createWithFormat("%d", NTGameSave::sharedGameSave()->getDataById(_GS_GOLD))->getCString());
    if (NTGameSave::sharedGameSave()->getDataById(_GS_HEART_COUNTLESS)==1) {
        m_pExtraHeartText->setVisible(false);
        m_pHeartCountless->setVisible(true);
        //Jerry
        pMenuItem->setVisible(false);
        pMenuItem->setEnabled(false);
        
        m_pMin->setVisible(false);
        m_pSec->setVisible(false);
        m_pPoint->setVisible(false);
        m_pMax->setVisible(false);
        for(int i = 0;i < 5;i++){
            m_pHeart[i]->setVisible(true);
        }
        return;
    }
    BloodData data = BloodTool::getContentBlood();
    if (isFly) {
        for(int i = 0;i < 5;i++){
            
            m_pHeart[i]->setVisible(i < data.contentBlood);
        }
    }
    
    
    if(data.nextTime.min == -1){
        
        m_pMin->setVisible(false);
        m_pSec->setVisible(false);
        m_pPoint->setVisible(false);
        m_pMax->setVisible(true);
    }else{
        
        m_pMin->setString(CCString::createWithFormat("0%d",data.nextTime.min)->getCString());
        if (data.nextTime.sec<10) {
            m_pSec->setString(CCString::createWithFormat("0%d",data.nextTime.sec)->getCString());
        }else
           m_pSec->setString(CCString::createWithFormat("%d",data.nextTime.sec)->getCString());
        
        m_pMin->setVisible(true);
        m_pSec->setVisible(true);
        m_pPoint->setVisible(true);
        m_pMax->setVisible(false);
    }
    if(data.contentBlood >5){
        m_pMax->setVisible(false);
       
        m_pExtraHeartText->setVisible(true);
        m_pExtraHeartText->setString(CCString::createWithFormat(";%d",data.contentBlood -5)->getCString());
    }else{
        m_pExtraHeartText->setVisible(false);
    }
  
}












