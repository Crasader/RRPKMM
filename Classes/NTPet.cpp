#include "NTPet.h"
#include "NTConstants.h"
#include "NTGameSave.h"
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
	void Java_com_ibirdgame_archirun_PayWrapper_buyPet(JNIEnv* env, jobject thiz, jint id)
	{
		CCObject* target = g_OncePayLibao.target;
		SYSDLG_CallFunc pFunc = g_OncePayLibao.func;
		(target->*pFunc)(id);
	}
#endif
}
bool NTPet::init()
{
	bool Res = false;
	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0,0,0, 160)));
		initValues();
		initUI();
		count1 = -1;		
		index1 = -1;
		Res = true;
	} while (0);

	return Res;
}

void NTPet::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, PRIORITY_NTLAYER_MSG,true);
}


void NTPet::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayerColor::onExit();
}


void NTPet::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();
}


void NTPet::initValues()
{
	m_pBg = NULL;
	m_bIsTouchMu = false;
	m_pMenu = NULL;
}

void NTPet::initUI()
{
	this->schedule(schedule_selector(NTPet::update_pet),0.2f);

	tinyxml2::XMLDocument pdocx;
	tinyxml2::XMLElement* pSurface;
	unsigned char* mybuf = NULL;
	unsigned long bufsize = 0;
	mybuf = CCFileUtils::sharedFileUtils()->getFileData(Pet_XML_FILE,"r",&bufsize);
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
		int posx = 0;	//
		int posy = 0;	//
		int pid = 0;	//
		pSurface->QueryIntAttribute("posx",&posx);
		pSurface->QueryIntAttribute("posy",&posy);
		pSurface->QueryIntAttribute("pid",&pid);

		char filestr[80] = {0};
		sprintf(filestr,"%s%s", Pet_PICTURE_PATH, pSurface->Name());
		
		//
		if(strcmp(pSurface->Name(),"stage_dk.png") == 0)
		{
			m_pBg = CCSprite::create(filestr);
			m_pBg->setPosition(ccp(winSize.width/2, winSize.height/2));
			this->addChild(m_pBg);

			//
			m_pMenu = CCMenu::create();
			m_pMenu->setPosition(CCPointZero);
			m_pMenu->setTouchEnabled(false);
			m_pBg->addChild(m_pMenu, 1);

		}
		//
		else if (strcmp(pSurface->Name(),"nn.png") == 0)
		{
			CCSprite* pSprite1 = CCSprite::create("share_button/nn.png");
			CCSprite* pSprite2 = CCSprite::create("share_button/nn.png");
			NTMenuItemSprite* pClose = NTMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(NTPet::menu_close));
			pClose->setPosition(ccp(posx,posy));
			m_pMenu->addChild(pClose);
		}
		//
		else if (strcmp(pSurface->Name(),"stage_db.png")==0)
		{
			pid -=1;
            if(NTGameSave::sharedGameSave()->isBoughtThePet(_GS_PET_IS_BUY_1+pid))
            {
			m_pSpriteBoard[pid] = CCSprite::create(filestr);
            }else{
             m_pSpriteBoard[pid] = CCSprite::create("hero/stage_db1.png");
            }
			m_pSpriteBoard[pid]->setPosition(ccp(posx, posy));
			m_pBg->addChild(m_pSpriteBoard[pid]);

			CCSprite* pFight = CCSprite::create("hero/meiri_yzh.png");
			pFight->setPosition(ccp(180, 351));
			pFight->setTag(FIGHT_LOGO);
			pFight->setVisible(false);
			m_pSpriteBoard[pid]->addChild(pFight);

			//
			if(NTGameSave::sharedGameSave()->getHeroPet()==PET_1+pid){
				pFight->setVisible(true);
			}
		}
		//
		else if (strcmp(pSurface->Name(),"stage_js4.png")==0)
		{
			initFightItem(filestr, posx, posy, 1);
		}
		else if (strcmp(pSurface->Name(),"stage_js3.png")==0)
		{
			initFightItem(filestr, posx, posy, 2);
		}
		else if (strcmp(pSurface->Name(),"stage_js5.png")==0)
		{
			initFightItem(filestr, posx, posy, 0);
		}
		//
		else if (strcmp(pSurface->Name(),"stage_lv.png") == 0)
		{
			CCSprite* pSprite = CCSprite::create(filestr);
			pSprite->setPosition(ccp(posx, posy));
			m_pBg->addChild(pSprite);
			pid -= 1;
			int iLevel = NTGameSave::sharedGameSave()->getDataById(_GS_PET1_LEVEL+pid);
			m_pPetLevel[pid] = CCLabelAtlas::create(CCString::createWithFormat("%d", iLevel)->getCString(), "hero/stage_lvnb.png", 11, 16, 48);
			m_pPetLevel[pid]->setPosition(ccp(posx+25, posy));
			m_pPetLevel[pid]->setAnchorPoint(ccp(0.5f, 0.5f));
			m_pBg->addChild(m_pPetLevel[pid]);
		}
		//
		else if (strcmp(pSurface->Name(),"stage_lvxt.png") == 0)
		{
			pid -= 1;
			int iLevel = NTGameSave::sharedGameSave()->getDataById(_GS_PET1_LEVEL+pid);
			CCSprite* pSprite = CCSprite::create(filestr);
			m_pPetLevelBar[pid]=CCProgressTimer::create(pSprite);
			m_pPetLevelBar[pid]->setType(kCCProgressTimerTypeBar);
			m_pPetLevelBar[pid]->setMidpoint(ccp(0,0)); 
			m_pPetLevelBar[pid]->setBarChangeRate(ccp(1,0));
			m_pPetLevelBar[pid]->setPosition(ccp(posx, posy));
			m_pPetLevelBar[pid]->setPercentage((((float)iLevel)/pet_info[PET_1+pid][PET_MAX_LEVEL])*100);
			m_pBg->addChild(m_pPetLevelBar[pid]);
			
		}
		//
		else if (strcmp(pSurface->Name(),"stage_wznb1.png") == 0)
		{
			CCSprite* pSprite = CCSprite::create(filestr);
			pSprite->setPosition(ccp(posx, posy));
			//m_pBg->addChild(pSprite);
			pid -= 1;
			
			
			if(pid<3){
                int iLevel = NTGameSave::sharedGameSave()->getDataById(_GS_PET1_LEVEL+pid);
				int iExtraGold = pet_info[PET_1+pid][PET_BASE_EXTRA_GOLD]+iLevel*pet_info[PET_1+pid][PET_ADD_EXTRA_GOLD];
				m_pPetExtraGold[pid] = CCLabelAtlas::create(CCString::createWithFormat("/%d:", iExtraGold)->getCString(), "hero/stage_wznb.png",  13 ,19, '/');
				m_pPetExtraGold[pid]->setPosition(ccp(posx-12, posy));
				m_pPetExtraGold[pid]->setAnchorPoint(ccp(0.5f, 0.5f));
				m_pBg->addChild(m_pPetExtraGold[pid]);
                CCSprite* pGold = CCSprite::create("hero/stage_wz.png");
                pGold->setPosition(ccp(posx-90, posy));
                pGold->setAnchorPoint(ccp(0.5f, 0.5f));
                m_pBg->addChild(pGold);
			}else{
				pid = pid%3;
                int iLevel = NTGameSave::sharedGameSave()->getDataById(_GS_PET1_LEVEL+pid);
                int iExtraMark = pet_info[PET_1+pid][PET_BASE_EXTRA_MARK]+iLevel*pet_info[PET_1+pid][PET_ADD_EXTRA_MARK];
				m_pPetExtraMark[pid] = CCLabelAtlas::create(CCString::createWithFormat("/%d:", iExtraMark)->getCString(), "hero/stage_wznb.png",  13 ,19, '/');
				m_pPetExtraMark[pid]->setPosition(ccp(posx-12, posy));
				m_pPetExtraMark[pid]->setAnchorPoint(ccp(0.5f, 0.5f));
				m_pBg->addChild(m_pPetExtraMark[pid]);
                CCSprite* pMark = CCSprite::create("hero/stage_wz1.png");
                pMark->setPosition(ccp(posx-90, posy));
                pMark->setAnchorPoint(ccp(0.5f, 0.5f));
                m_pBg->addChild(pMark);
			}
			
        }
		//
		else if (strcmp(pSurface->Name(),"stage_an2.png") == 0)
		{
			pid -= 1;
			int iLevel = NTGameSave::sharedGameSave()->getDataById(_GS_PET1_LEVEL+pid);
			//
			CCSprite* pSprite1 = CCSprite::create("hero/stage_an1.png");
			CCSprite* pSprite2 = CCSprite::create("hero/stage_an1.png");
			m_pUpgradeItem[pid] = NTMenuItemSprite::create(pSprite1, pSprite2, NULL, this, menu_selector(NTPet::menu_upgrade));
			m_pUpgradeItem[pid]->setPosition(ccp(posx, posy));
			m_pUpgradeItem[pid]->setTag(pid);
			m_pMenu->addChild(m_pUpgradeItem[pid]);
			//
			int iPriceUpgrade = pet_info[PET_1+pid][PET_BASE_LEVEL_UP_GOLD]+iLevel*pet_info[PET_1+pid][PET_ADD_LEVEL_UP_GOLD];
			m_pPetUpgrade[pid] = CCLabelAtlas::create(CCString::createWithFormat("%d", iPriceUpgrade)->getCString(), "hero/stage_an2nb.png", 12, 20, 48);
			m_pPetUpgrade[pid]->setPosition(ccp(m_pUpgradeItem[pid]->getContentSize().width/2-6, m_pUpgradeItem[pid]->getContentSize().height/2+4));
			m_pPetUpgrade[pid]->setAnchorPoint(ccp(0.5f, 0.5f));
			m_pUpgradeItem[pid]->addChild(m_pPetUpgrade[pid]);

			//
			if(!NTGameSave::sharedGameSave()->isBoughtThePet(_GS_PET_IS_BUY_1+pid)){
				CCSprite* pSprite1 = CCSprite::create("hero/stage_an3.png");
				CCSprite* pSprite2 = CCSprite::create("hero/stage_an3.png");
				m_pBuyItem[pid] = NTMenuItemSprite::create(pSprite1, pSprite2, NULL, this, menu_selector(NTPet::menu_buy));
				m_pBuyItem[pid]->setPosition(ccp(posx, posy));
				m_pBuyItem[pid]->setTag(pid);
				m_pMenu->addChild(m_pBuyItem[pid]);
				//
				int iPriceBuy = pet_info[PET_1+pid][PET_BUY_PRICE];
				m_pPetBuy[pid] = CCLabelAtlas::create(CCString::createWithFormat("%d", iPriceBuy)->getCString(), "hero/stage_an2nb.png", 12, 20, 48);
				m_pPetBuy[pid]->setPosition(ccp(m_pBuyItem[pid]->getContentSize().width/2+12, m_pBuyItem[pid]->getContentSize().height/2+4));
				m_pPetBuy[pid]->setAnchorPoint(ccp(0.5f, 0.5f));
				m_pBuyItem[pid]->addChild(m_pPetBuy[pid]);

				//
				m_pUpgradeItem[pid]->setVisible(false);
			}
		}
		//
		else
		{
			CCSprite* pSprite = CCSprite::create(filestr);
			pSprite->setPosition(ccp(posx, posy));
			m_pBg->addChild(pSprite);
		}
		pSurface = pSurface->NextSiblingElement();
	}

}

void NTPet::initFightItem( const char *name, int posx, int posy, int pid )
{
	CCSprite* pSprite1 = CCSprite::create(name);
	m_pSelectItem[pid] = NTMenuItemSprite::create(pSprite1,NULL,this,menu_selector(NTPet::menu_select));
	m_pSelectItem[pid]->setPosition(ccp(posx,posy));
	m_pSelectItem[pid]->setTag(pid);
	m_pMenu->addChild(m_pSelectItem[pid]);

	//
	if(!NTGameSave::sharedGameSave()->isBoughtThePet(_GS_PET_IS_BUY_1+pid)){
		m_pSelectItem[pid]->setEnabled(false);
	}
}

bool NTPet::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (!m_bIsTouchMu)
	{
		m_bIsTouchMu = m_pMenu->ccTouchBegan(pTouch,pEvent);
	}

	return true;
}

void NTPet::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchMoved(pTouch,pEvent);
	}
}

void NTPet::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchEnded(pTouch,pEvent);
		m_bIsTouchMu = false;
	}
}

void NTPet::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchCancelled(pTouch,pEvent);
		m_bIsTouchMu = false;
	}
}

void NTPet::menu_close( CCObject* pRender )
{
	this->runAction(CCSequence::create(CCMoveTo::create(0.2f,ccp(0,600)),
		CCCallFunc::create(this,callfunc_selector(NTPet::callback_close)),NULL));
	this->unschedule(schedule_selector(NTPet::update_pet));
}


void NTPet::bornOnScene()
{
	this->setPosition(ccp(0,600));
	this->runAction(CCMoveTo::create(0.2f, ccp(0, 0)));
}

void NTPet::callback_close()
{
	removeFromParentAndCleanup(true);
}

void NTPet::menu_buy( CCObject* pRender )
{
    CCNode* pNode = (CCNode*)pRender;
    int pid = pNode->getTag();
    int iPriceBuy = pet_info[PET_1+pid][PET_BUY_PRICE];
    int iGold = NTGameSave::sharedGameSave()->getDataById(_GS_GOLD);
    if(iGold>=iPriceBuy){
        iGold-=iPriceBuy;
    }else{
        NTGold* pLayer = NTGold::create();
        this->addChild(pLayer);
        pLayer->setPosition(ccp(0,600));
        pLayer->runAction(CCMoveTo::create(0.2f, ccp(0, 0)));
        return;
    }
    NTGameSave::sharedGameSave()->updateValue(_GS_GOLD, iGold);
    NTGameSave::sharedGameSave()->updateBuyPet(_GS_PET_IS_BUY_1+pid, true);
//	pNode = (CCNode*)pRender;
//	index1 = pNode->getTag();
//	int num = index1+6;
    //Cocos_order(num);
//	g_OncePayLibao.target = this;
//	g_OncePayLibao.func = (SYSDLG_CallFunc)(&NTPet::setupdataLibaoState);
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
//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,num);
//	}
//	CCLog("jni-java∫Ø ˝÷¥––ÕÍ±œ");
//#endif

	//
// 	NTGameSave::sharedGameSave()->updateBuyPet(_GS_PET_IS_BUY_1+pNode->getTag(), true);
// 	//
// 	pNode->setVisible(false);
// 	m_pUpgradeItem[pNode->getTag()]->setVisible(true);
// 	m_pSelectItem[pNode->getTag()]->setEnabled(true);
}

void NTPet::setupdataLibaoState(int i){
    if (i!=0) {
        count1 = 1;
    }
}
void NTPet::update_pet(float f){
//	CCLog("update_pet");
//	if(count1==1){
//		count1=-1;
//		//÷±Ω”π∫¬Ú≥…π¶
//		NTGameSave::sharedGameSave()->updateBuyPet(_GS_PET_IS_BUY_1+pNode->getTag(), true);
//		//“˛≤ÿ◊‘º∫£¨œ‘ æ…˝º∂∞¥≈•, º§ªÓ≥ˆ’Ω∞¥≈•
//		pNode->setVisible(false);
//		m_pUpgradeItem[index1]->setVisible(true);
//		m_pSelectItem[index1]->setEnabled(true);
//	}
    for (int i=0; i<3;i++) {
        if (m_pUpgradeItem[i]->isVisible()) continue;
        if ( NTGameSave::sharedGameSave()->isBoughtThePet(_GS_PET_IS_BUY_1+i)) {
//            if (pNode!=NULL) {
//                pNode->setVisible(false);
//            }
            m_pBuyItem[i]->setVisible(false);
            m_pUpgradeItem[i]->setVisible(true);
            m_pSelectItem[i]->setEnabled(true);
            }
    }
    
}


void NTPet::menu_upgrade( CCObject* pRender )
{
	CCNode* pNode = (CCNode*)pRender;
	int pid = pNode->getTag();
	int iLevel = NTGameSave::sharedGameSave()->getDataById(_GS_PET1_LEVEL+pid);

	//
	if(pet_info[PET_1+pid][PET_MAX_LEVEL]<=iLevel){
		return;
	}

	//
	int iGold = NTGameSave::sharedGameSave()->getDataById(_GS_GOLD);
	//
	int iPriceUpgrade = pet_info[PET_1+pid][PET_BASE_LEVEL_UP_GOLD]+iLevel*pet_info[PET_1+pid][PET_ADD_LEVEL_UP_GOLD];
	if(iGold>=iPriceUpgrade){
		iGold-=iPriceUpgrade;
	}else{
        NTGold* pLayer = NTGold::create();
        this->addChild(pLayer);
        pLayer->setPosition(ccp(0,600));
        pLayer->runAction(CCMoveTo::create(0.2f, ccp(0, 0)));
		return;
	}
	//
	NTGameSave::sharedGameSave()->updateValue(_GS_GOLD, iGold);
	//
	NTGameSave::sharedGameSave()->updateValue(_GS_PET1_LEVEL+pid, ++iLevel);
    //Jerry--Log
    
    if(NTGameSave::sharedGameSave()->getDataById(_GS_TASKTHREE)==8){
        CCLog("updatepet%d",NTGameSave::sharedGameSave()->getDataById(_GS_TASKTHREE));
        NTGameSave::sharedGameSave()->updateValue(_GS_TASKTHREE_FINISH,1);
    }

	//
	int iPriceUpgradeNew = pet_info[PET_1+pid][PET_BASE_LEVEL_UP_GOLD]+iLevel*pet_info[PET_1+pid][PET_ADD_LEVEL_UP_GOLD];
	m_pPetUpgrade[pid]->setString(CCString::createWithFormat("%d", iPriceUpgradeNew)->getCString());
	//
	m_pPetLevel[pid]->setString(CCString::createWithFormat("%d", iLevel)->getCString());
	m_pPetLevelBar[pid]->setPercentage((((float)iLevel)/pet_info[PET_1+pid][PET_MAX_LEVEL])*100);
	//
	int iExtraGold = pet_info[PET_1+pid][PET_BASE_EXTRA_GOLD]+iLevel*pet_info[PET_1+pid][PET_ADD_EXTRA_GOLD];
	m_pPetExtraGold[pid]->setString(CCString::createWithFormat("/%d:", iExtraGold)->getCString());
	int iExtraMark = pet_info[PET_1+pid][PET_BASE_EXTRA_MARK]+iLevel*pet_info[PET_1+pid][PET_ADD_EXTRA_MARK];
	m_pPetExtraMark[pid]->setString(CCString::createWithFormat("/%d:", iExtraMark)->getCString());
}

void NTPet::menu_select( CCObject* pRender )
{
	NTMenuItemSprite* pNode = (NTMenuItemSprite*)pRender;
	//
	NTGameSave::sharedGameSave()->updateHeroPet(PET_1+pNode->getTag());
	for(unsigned int i=0; i<PET_MAX; i++){
		if(pNode->getTag()==i){
			m_pSpriteBoard[i]->getChildByTag(FIGHT_LOGO)->setVisible(true);
		}else{
			m_pSpriteBoard[i]->getChildByTag(FIGHT_LOGO)->setVisible(false);
		}
	}
}










