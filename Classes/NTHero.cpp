#include "NTHero.h"
#include "NTConstants.h"
#include "NTGameSave.h"
#include "Assistant.h"
#include "NTGold.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

static SDialogContent g_OncePayLibao;

extern "C" {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeDealCompleteLibao 
	void Java_com_ibirdgame_archirun_PayWrapper_buyHero(JNIEnv* env, jobject thiz, jint id)
	{
		CCObject* target = g_OncePayLibao.target;
		SYSDLG_CallFunc pFunc = g_OncePayLibao.func;
		(target->*pFunc)(id);
	}
#endif
}

bool NTHero::init()
{
	const1 = 0;
	inxde = -1;
	bool Res = false;
	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0,0,0, 160)));
		initValues();
		initUI();
		Res = true;
		this->schedule(schedule_selector(NTHero::update_hero),0.2f);
	} while (0);

	return Res;
}

void NTHero::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, PRIORITY_NTLAYER_MSG,true);
}


void NTHero::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayerColor::onExit();
}


void NTHero::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();
}


void NTHero::initValues()
{
	m_pBg = NULL;
	m_bIsTouchMu = false;
	m_pMenu = NULL;
}

void NTHero::initUI()
{
	tinyxml2::XMLDocument pdocx;
	tinyxml2::XMLElement* pSurface;
	unsigned char* mybuf = NULL;
	unsigned long bufsize = 0;
	mybuf = CCFileUtils::sharedFileUtils()->getFileData(HERO_XML_FILE,"r",&bufsize);
	if (!mybuf){
		return;
	}
	pdocx.Parse((const char*)mybuf,bufsize);
	if (pdocx.NoChildren()){
		return;
	}
	pSurface = pdocx.FirstChildElement();

	/*tinyxml2::XMLElement* pSurface = initUiDataFromXmlFile();*/
	if(pSurface==NULL){
		return;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	while(pSurface)
	{
		int posx = 0;	//XŒª÷√
		int posy = 0;	//YŒª÷√
		int pid = 0;	//±‡∫≈
		pSurface->QueryIntAttribute("posx",&posx);
		pSurface->QueryIntAttribute("posy",&posy);
		pSurface->QueryIntAttribute("pid",&pid);

		char filestr[80] = {0};
		sprintf(filestr,"%s%s", HERO_PICTURE_PATH, pSurface->Name());

		//≥ı ºªØ±≥æ∞
		if(strcmp(pSurface->Name(),"stage_dk.png") == 0)
		{
			m_pBg = CCSprite::create(filestr);
			m_pBg->setPosition(ccp(winSize.width/2, winSize.height/2));
			this->addChild(m_pBg);

			//≥ı ºªØMENU
			m_pMenu = CCMenu::create();
			m_pMenu->setPosition(CCPointZero);
			m_pMenu->setTouchEnabled(false);
			m_pBg->addChild(m_pMenu, 1);

		}
		//πÿ±’∞¥≈•
		else if (strcmp(pSurface->Name(),"nn.png") == 0)
		{
			CCSprite* pSprite1 = CCSprite::create("share_button/nn.png");
			CCSprite* pSprite2 = CCSprite::create("share_button/nn.png");
			NTMenuItemSprite* pClose = NTMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(NTHero::menu_close));
			pClose->setPosition(ccp(posx,posy));
			m_pMenu->addChild(pClose);
		}
		//≥ˆ’Ω±Í ∂
		else if (strcmp(pSurface->Name(),"stage_db1.png")==0)
		{
			pid -=1;
            if(!NTGameSave::sharedGameSave()->isBoughtTheHero(_GS_HERO_IS_BUY_1+pid)){
			m_pSpriteBoard[pid] = CCSprite::create(filestr);
            }else{
            m_pSpriteBoard[pid] = CCSprite::create("hero/stage_db.png");
            }
			m_pSpriteBoard[pid]->setPosition(ccp(posx, posy));
			m_pBg->addChild(m_pSpriteBoard[pid]);

			CCSprite* pFight = CCSprite::create("hero/meiri_yzh.png");
			pFight->setPosition(ccp(180, 351));
			pFight->setTag(FIGHT_LOGO);
			pFight->setVisible(false);
			m_pSpriteBoard[pid]->addChild(pFight);
            CCSprite *pTitle;
            CCSprite *pTag;
            if (pid==1) {
                pTitle =CCSprite::create("hero/stage_lll.png");
                m_pSpriteBoard[pid]->addChild(pTitle);
                pTitle->setPosition(ccp(40, 260));
                pTag =CCSprite::create("hero/stage_xg1.png");
                 m_pSpriteBoard[pid]->addChild(pTag);
                pTag->setScale(0.8f);
                pTag->setPosition(ccp(180, 150));
            }else if(pid==2)
            {
               pTitle =CCSprite::create("hero/stage_mv1.png");
                 m_pSpriteBoard[pid]->addChild(pTitle);
                pTitle->setPosition(ccp(40, 260));
                pTag =CCSprite::create("hero/stage_xg.png");
                m_pSpriteBoard[pid]->addChild(pTag);
                pTag->setScale(0.8f);
                pTag->setPosition(ccp(180, 150));
            }
            
			//»Áπ˚≥ˆ’Ω¡À
			if(NTGameSave::sharedGameSave()->getHeroSelect()==ACTOR_1+pid){
				pFight->setVisible(true);
			}
		}
		//—°‘Ò”¢–€
		else if (strcmp(pSurface->Name(),"stage_js.png")==0)
		{
           
			initFightItem(filestr, posx, posy, 1);
		}
		else if (strcmp(pSurface->Name(),"stage_js1.png")==0)
		{
           
			initFightItem(filestr, posx, posy, 2);
		}
		else if (strcmp(pSurface->Name(),"stage_js2.png")==0)
		{
			initFightItem(filestr, posx, posy, 0);
		}
		//”¢–€µ»º∂
		else if (strcmp(pSurface->Name(),"stage_lv.png") == 0)
		{
			CCSprite* pSprite = CCSprite::create(filestr);
			pSprite->setPosition(ccp(posx, posy));
			m_pBg->addChild(pSprite);
			pid -= 1;
			int iLevel = NTGameSave::sharedGameSave()->getDataById(_GS_HERO1_LEVEL+pid);
			m_pHeroLevel[pid] = CCLabelAtlas::create(CCString::createWithFormat("%d", iLevel)->getCString(), "hero/stage_lvnb.png", 11, 16, 48);
			m_pHeroLevel[pid]->setPosition(ccp(posx+25, posy));
			m_pHeroLevel[pid]->setAnchorPoint(ccp(0.5f, 0.5f));
			m_pBg->addChild(m_pHeroLevel[pid]);
		}
		//”¢–€µ»º∂Ãı
		else if (strcmp(pSurface->Name(),"stage_lvxt.png") == 0)
		{
			pid -= 1;
			int iLevel = NTGameSave::sharedGameSave()->getDataById(_GS_HERO1_LEVEL+pid);
			CCSprite* pSprite = CCSprite::create(filestr);
			m_pHeroLevelBar[pid]=CCProgressTimer::create(pSprite);
			m_pHeroLevelBar[pid]->setType(kCCProgressTimerTypeBar);
			m_pHeroLevelBar[pid]->setMidpoint(ccp(0,0)); 
			m_pHeroLevelBar[pid]->setBarChangeRate(ccp(1,0));
			m_pHeroLevelBar[pid]->setPosition(ccp(posx, posy));
			m_pHeroLevelBar[pid]->setPercentage((((float)iLevel)/actor_info[ACTOR_1+pid][ACTOR_MAX_LEVEL])*100);
			m_pBg->addChild(m_pHeroLevelBar[pid]);
			
		}
		//∂ÓÕ‚Ω±“
		else if (strcmp(pSurface->Name(),"stage_wznb1.png") == 0)
		{
			CCSprite* pSprite = CCSprite::create(filestr);
			pSprite->setPosition(ccp(posx, posy));
			//m_pBg->addChild(pSprite);
			pid -= 1;
			
			
			if(pid<3){
                int iLevel = NTGameSave::sharedGameSave()->getDataById(_GS_HERO1_LEVEL+pid);
				int iExtraGold = actor_info[ACTOR_1+pid][ACTOR_BASE_EXTRA_GOLD]+iLevel*actor_info[ACTOR_1+pid][ACTOR_ADD_EXTRA_GOLD];
				m_pHeroExtraGold[pid] = CCLabelAtlas::create(CCString::createWithFormat("/%d:", iExtraGold)->getCString(), "hero/stage_wznb.png", 13 ,19, '/');
				m_pHeroExtraGold[pid]->setPosition(ccp(posx-12, posy));
				m_pHeroExtraGold[pid]->setAnchorPoint(ccp(0.5f, 0.5f));
				m_pBg->addChild(m_pHeroExtraGold[pid]);
                CCSprite* pGold = CCSprite::create("hero/stage_wz.png");
                pGold->setPosition(ccp(posx-90, posy));
                pGold->setAnchorPoint(ccp(0.5f, 0.5f));
                m_pBg->addChild(pGold);
			}else{
				pid = pid%3;
                int iLevel = NTGameSave::sharedGameSave()->getDataById(_GS_HERO1_LEVEL+pid);
				int iExtraMark = actor_info[ACTOR_1+pid][ACTOR_BASE_EXTRA_MARK]+iLevel*actor_info[ACTOR_1+pid][ACTOR_ADD_EXTRA_MARK];
				m_pHeroExtraMark[pid] = CCLabelAtlas::create(CCString::createWithFormat("/%d:", iExtraMark)->getCString(), "hero/stage_wznb.png", 13,19,'/');
				m_pHeroExtraMark[pid]->setPosition(ccp(posx-12, posy));
				m_pHeroExtraMark[pid]->setAnchorPoint(ccp(0.5f, 0.5f));
				m_pBg->addChild(m_pHeroExtraMark[pid]);
                CCSprite* pMark = CCSprite::create("hero/stage_wz1.png");
                pMark->setPosition(ccp(posx-90, posy));
                pMark->setAnchorPoint(ccp(0.5f, 0.5f));
                m_pBg->addChild(pMark);
			}
			
		}
		//π∫¬Ú∞¥≈•∫Õ…˝º∂∞¥≈•
		else if (strcmp(pSurface->Name(),"stage_an2.png") == 0)
		{
			pid -= 1;
			int iLevel = NTGameSave::sharedGameSave()->getDataById(_GS_HERO1_LEVEL+pid);
			//…˝º∂∞¥≈•∫Õ«Æ
			CCSprite* pSprite1 = CCSprite::create("hero/stage_an1.png");
			CCSprite* pSprite2 = CCSprite::create("hero/stage_an1.png");
			m_pUpgradeItem[pid] = NTMenuItemSprite::create(pSprite1, pSprite2, NULL, this, menu_selector(NTHero::menu_upgrade));
			m_pUpgradeItem[pid]->setPosition(ccp(posx, posy));
			m_pUpgradeItem[pid]->setTag(pid);
			m_pMenu->addChild(m_pUpgradeItem[pid]);
			//º€«Æ
			int iPriceUpgrade = actor_info[ACTOR_1+pid][ACTOR_BASE_LEVEL_UP_GOLD]+iLevel*actor_info[ACTOR_1+pid][ACTOR_ADD_LEVEL_UP_GOLD];
			m_pHeroUpgrade[pid] = CCLabelAtlas::create(CCString::createWithFormat("%d", iPriceUpgrade)->getCString(), "hero/stage_an2nb.png", 12, 20, 48);
			m_pHeroUpgrade[pid]->setPosition(ccp(m_pUpgradeItem[pid]->getContentSize().width/2-6, m_pUpgradeItem[pid]->getContentSize().height/2+4));
			m_pHeroUpgrade[pid]->setAnchorPoint(ccp(0.5f, 0.5f));
			m_pUpgradeItem[pid]->addChild(m_pHeroUpgrade[pid]);

			//»Áπ˚√ª”–¬Ú,…˙≥…π∫¬Ú∞¥≈•
			if(!NTGameSave::sharedGameSave()->isBoughtTheHero(_GS_HERO_IS_BUY_1+pid)){
				CCSprite* pSprite1 = CCSprite::create(filestr);
				CCSprite* pSprite2 = CCSprite::create(filestr);
				m_pBuyItem[pid] = NTMenuItemSprite::create(pSprite1, pSprite2, NULL, this, menu_selector(NTHero::menu_buy));
				m_pBuyItem[pid]->setPosition(ccp(posx, posy));
				m_pBuyItem[pid]->setTag(pid);
				m_pMenu->addChild(m_pBuyItem[pid]);
				//º€«Æ
				int iPriceBuy = actor_info[ACTOR_1+pid][ACTOR_BUY_PRICE];
				m_pHeroBuy[pid] = CCLabelAtlas::create(CCString::createWithFormat("%d", iPriceBuy)->getCString(), "hero/stage_an2nb.png",12, 20, 48);
				m_pHeroBuy[pid]->setPosition(ccp(m_pBuyItem[pid]->getContentSize().width/2+12, m_pBuyItem[pid]->getContentSize().height/2+4));
				m_pHeroBuy[pid]->setAnchorPoint(ccp(0.5f, 0.5f));
				m_pBuyItem[pid]->addChild(m_pHeroBuy[pid]);

				//“˛≤ÿ…˝º∂∞¥≈•
				m_pUpgradeItem[pid]->setVisible(false);
			}
		}
		//∆‰À˚Õº∆¨
		else
		{
			CCSprite* pSprite = CCSprite::create(filestr);
			pSprite->setPosition(ccp(posx, posy));
			m_pBg->addChild(pSprite);
		}
		pSurface = pSurface->NextSiblingElement();
	}

}

void NTHero::initFightItem( const char *name, int posx, int posy, int pid )
{
	CCSprite* pSprite1 = CCSprite::create(name);
	m_pSelectItem[pid] = NTMenuItemSprite::create(pSprite1,NULL,this,menu_selector(NTHero::menu_select));
	m_pSelectItem[pid]->setPosition(ccp(posx,posy-20));
	m_pSelectItem[pid]->setTag(pid);
    m_pSelectItem[pid]->setScale(0.8f);
	m_pMenu->addChild(m_pSelectItem[pid]);

	//»Áπ˚√ª”–π∫¬Ú
	if(!NTGameSave::sharedGameSave()->isBoughtTheHero(_GS_HERO_IS_BUY_1+pid)){
		m_pSelectItem[pid]->setEnabled(false);
	}
}
void NTHero::initFightItem( const char *name, int posx, int posy, int pid,CCSprite *sprite )
{
    CCSprite* pSprite1 = CCSprite::create(name);
    pSprite1->addChild(sprite);
    sprite->setPosition(ccp(-10,150));
    m_pSelectItem[pid] = NTMenuItemSprite::create(pSprite1,NULL,this,menu_selector(NTHero::menu_select));
    m_pSelectItem[pid]->setPosition(ccp(posx,posy));
    m_pSelectItem[pid]->setTag(pid);
    m_pMenu->addChild(m_pSelectItem[pid]);
    
    
    //»Áπ˚√ª”–π∫¬Ú
    if(!NTGameSave::sharedGameSave()->isBoughtTheHero(_GS_HERO_IS_BUY_1+pid)){
        m_pSelectItem[pid]->setEnabled(false);
    }
}

bool NTHero::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (!m_bIsTouchMu)
	{
		m_bIsTouchMu = m_pMenu->ccTouchBegan(pTouch,pEvent);
	}

	return true;
}

void NTHero::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchMoved(pTouch,pEvent);
	}
}

void NTHero::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchEnded(pTouch,pEvent);
		m_bIsTouchMu = false;
	}
}

void NTHero::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchCancelled(pTouch,pEvent);
		m_bIsTouchMu = false;
	}
}

void NTHero::menu_close( CCObject* pRender )
{
	this->runAction(CCSequence::create(CCMoveTo::create(0.2f,ccp(0,600)),
		CCCallFunc::create(this,callfunc_selector(NTHero::callback_close)),NULL));
	this->unschedule(schedule_selector(NTHero::update_hero));
}


void NTHero::bornOnScene()
{
	this->setPosition(ccp(0,600));
	this->runAction(CCMoveTo::create(0.2f, ccp(0, 0)));
}

void NTHero::callback_close()
{
	removeFromParentAndCleanup(true);
}

void NTHero::menu_buy( CCObject* pRender )
{
	pNode = (CCNode*)pRender;
	inxde = pNode->getTag();
	int strss = inxde+3;
	//µ˜”√∏∂∑—Ω”ø⁄£®π∫¬Ú»ÀŒÔΩÁ√Ê∞¥≈•£©
	//º«¬ºjava∑µªÿ ±”¶÷¥––µƒ∑Ω∑®
    Cocos_order(strss);
//	g_OncePayLibao.target = this;
//	g_OncePayLibao.func = (SYSDLG_CallFunc)(&NTHero::setupdataLibaoState);
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //≈–∂œµ±«∞ «∑ÒŒ™Android∆ΩÃ®
//	JniMethodInfo minfo;//∂®“ÂJni∫Ø ˝–≈œ¢Ω·ππÃÂ
//	//getStaticMethodInfo ¥Œ∫Ø ˝∑µªÿ“ª∏ˆbool÷µ±Ì æ «∑Ò’“µΩ¥À∫Ø ˝
//    
//    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/PayWrapper","Cocos_order", "(I)V");
//    
//    if (!isHave) {
//        CCLog("jni:¥À∫Ø ˝≤ª¥Ê‘⁄");
//    }else{
//        CCLog("jni:¥À∫Ø ˝¥Ê‘⁄");
//        //µ˜”√¥À∫Ø ˝
//        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,strss);
//    }
//    CCLog("jni-java∫Ø ˝÷¥––ÕÍ±œ");
//#endif
	
	//÷±Ω”π∫¬Ú≥…π¶
// 	NTGameSave::sharedGameSave()->updateBuyHero(_GS_HERO_IS_BUY_1+pNode->getTag(), true);
// 	//“˛≤ÿ◊‘º∫£¨œ‘ æ…˝º∂∞¥≈•, º§ªÓ≥ˆ’Ω∞¥≈•
// 	pNode->setVisible(false);
// 	m_pUpgradeItem[pNode->getTag()]->setVisible(true);
// 	m_pSelectItem[pNode->getTag()]->setEnabled(true);
}
void NTHero::setupdataLibaoState(int i){
    if (i!=0) {
        const1 = 1;
    }
}

void NTHero::menu_upgrade( CCObject* pRender )
{
	CCNode* pNode = (CCNode*)pRender;
	int pid = pNode->getTag();
	int iLevel = NTGameSave::sharedGameSave()->getDataById(_GS_HERO1_LEVEL+pid);

	// «∑Ò“—æ≠¥ÔµΩ◊Ó∏ﬂµ»º∂
	if(actor_info[ACTOR_1+pid][ACTOR_MAX_LEVEL]<=iLevel){
		return;
	}

	// «∑Ò”–◊„πªΩ±“
	int iGold = NTGameSave::sharedGameSave()->getDataById(_GS_GOLD);
	int iPriceUpgrade = actor_info[ACTOR_1+pid][ACTOR_BASE_LEVEL_UP_GOLD]+iLevel*actor_info[ACTOR_1+pid][ACTOR_ADD_LEVEL_UP_GOLD];
	if(iGold>=iPriceUpgrade){
		iGold-=iPriceUpgrade;
	}else{
        NTGold* pLayer = NTGold::create();
        this->addChild(pLayer);
        pLayer->setPosition(ccp(0,600));
        pLayer->runAction(CCMoveTo::create(0.2f, ccp(0, 0)));
        return;
	}
	//¥Ê¥¢Ω±“
	NTGameSave::sharedGameSave()->updateValue(_GS_GOLD, iGold);
	//∏¸–¬µ»º∂
	NTGameSave::sharedGameSave()->updateValue(_GS_HERO1_LEVEL+pid, ++iLevel);
    if(NTGameSave::sharedGameSave()->getDataById(_GS_TASKTHREE)==1){
        CCLog("updatepet%d",NTGameSave::sharedGameSave()->getDataById(_GS_TASKTHREE));
        NTGameSave::sharedGameSave()->updateValue(_GS_TASKTHREE_FINISH,1);
    }

	//∏¸–¬…˝º∂º€∏Ò
	int iPriceUpgradeNew = actor_info[ACTOR_1+pid][ACTOR_BASE_LEVEL_UP_GOLD]+iLevel*actor_info[ACTOR_1+pid][ACTOR_ADD_LEVEL_UP_GOLD];
	m_pHeroUpgrade[pid]->setString(CCString::createWithFormat("%d", iPriceUpgradeNew)->getCString());
	//∏¸–¬µ»º∂Ãı∫Õœ‘ æµ»º∂
	m_pHeroLevel[pid]->setString(CCString::createWithFormat("%d", iLevel)->getCString());
	m_pHeroLevelBar[pid]->setPercentage((((float)iLevel)/actor_info[ACTOR_1+pid][ACTOR_MAX_LEVEL])*100);
	//∏¸–¬∂ÓÕ‚Ω±“ ˝∫Õ∂ÓÕ‚∑÷ ˝
	int iExtraGold = actor_info[ACTOR_1+pid][ACTOR_BASE_EXTRA_GOLD]+iLevel*actor_info[ACTOR_1+pid][ACTOR_ADD_EXTRA_GOLD];
	m_pHeroExtraGold[pid]->setString(CCString::createWithFormat("/%d:", iExtraGold)->getCString());
	int iExtraMark = actor_info[ACTOR_1+pid][ACTOR_BASE_EXTRA_MARK]+iLevel*actor_info[ACTOR_1+pid][ACTOR_ADD_EXTRA_MARK];
	m_pHeroExtraMark[pid]->setString(CCString::createWithFormat("/%d:", iExtraMark)->getCString());
}

void NTHero::menu_select( CCObject* pRender )
{
	NTMenuItemSprite* pNode = (NTMenuItemSprite*)pRender;
	//¥Ê¥¢≥ˆ’Ω±Í ∂
	NTGameSave::sharedGameSave()->updateHeroSelect(ACTOR_1+pNode->getTag());
	for(unsigned int i=0; i<ACTOR_MAX; i++){
		if(pNode->getTag()==i){
			m_pSpriteBoard[i]->getChildByTag(FIGHT_LOGO)->setVisible(true);
		}else{
			m_pSpriteBoard[i]->getChildByTag(FIGHT_LOGO)->setVisible(false);
		}
	}
}

void NTHero::update_hero(float f){
    
//	CCLog("update_hero");
//	if(const1==1){
//		//÷±Ω”π∫¬Ú≥…π¶
//		const1=-1;
//		NTGameSave::sharedGameSave()->updateBuyHero(_GS_HERO_IS_BUY_1+inxde, true);
//		//“˛≤ÿ◊‘º∫£¨œ‘ æ…˝º∂∞¥≈•, º§ªÓ≥ˆ’Ω∞¥≈•
//		pNode->setVisible(false);
    
//		m_pUpgradeItem[pNode->getTag()]->setVisible(true);
//		m_pSelectItem[pNode->getTag()]->setEnabled(true);
//	}
    for (int i=1; i<3;i++) {
        if (m_pUpgradeItem[i]->isVisible()) continue;
        if ( NTGameSave::sharedGameSave()->isBoughtTheHero(_GS_HERO_IS_BUY_1+i)) {
            if (pNode!=NULL) {
                pNode->setVisible(false);
            }            m_pUpgradeItem[i]->setVisible(true);
            m_pSelectItem[i]->setEnabled(true);
            CCLog("update_hero_%d",i);
        }
    }
   
}












