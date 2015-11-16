#include "NTHeart.h"
#include "NTMenuItem.h"
#include "NTConstants.h"
#include "NTMenuItem.h"
#include "NTStart.h"
#include "NTGameSave.h"
#include "Assistant.h"
#include "CocoStudio/Armature/CCArmature.h"


const int ci_price[]={2,4,6,8};
const int xinshuliang[] = {5,12,30,60};
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

static SDialogContent g_OncePayLibao;

extern "C" {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeDealCompleteLibao 
	void Java_com_ibirdgame_archirun_PayWrapper_buyHeart(JNIEnv* env, jobject thiz, jint id)
	{
		CCObject* target = g_OncePayLibao.target;
		SYSDLG_CallFunc pFunc = g_OncePayLibao.func;
		(target->*pFunc)(id);
	}
#endif
}

void NTHeart::initValues()
{

}
void NTHeart::onEnter()
{
	NTCoverLayer::onEnter();
	initValues();
	initUI();
}
void NTHeart::initUI()
{
	count1 = 0;
	index = -1;

	CCMenu *pMenu = CCMenu::create();
	this->addChild(pMenu,2);
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	setMenu(pMenu);
	

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *pBg = CCSprite::create("heart/bank_dk.png");
	this->addChild(pBg);
	pBg->setPosition(ccp(winSize.width/2,winSize.height/2));

/*	int xinshuliang[] = {2,10,50};*/

	for(int i = 0;i < 4; i++){

		CCSprite *pItem = CCSprite::create("heart/bank_db.png");
		pBg->addChild(pItem );
		pItem ->setPosition(ccp(96+i*(pItem->getContentSize().width),180));

		CCSprite *pHeart = CCSprite::create(CCString::createWithFormat("heart/bank_%d.png",i+1)->getCString());
		pItem->addChild(pHeart);
		pHeart->setPosition(ccp(pItem->getContentSize().width/2,pItem->getContentSize().height/2));


//		CCSprite *pNumLogo = CCSprite::create("heart/bank_x.png");
//		pItem->addChild(pNumLogo);
//		pNumLogo->setPosition(ccp(50,280));
//        if (i==3) {
//            CCSprite *pNumText=CCSprite::create("heart/wuxian.png");
//            pItem->addChild(pNumText);
//            pNumText->setPosition(ccp(100,280));
//        }else{
//            CCLabelAtlas *pNumText = CCLabelAtlas::create(CCString::createWithFormat("/%d",xinshuliang[i])->getCString(),"heart/nb.png",15,24,'0'-1);
        CCSprite *pNumText=CCSprite::create(CCString::createWithFormat("heart/bank_xz%d.png",i+1)->getCString());
                    pItem->addChild(pNumText);
                    pNumText->setPosition(ccp(80,280));
       
		

		NTMenuItemSprite *pBuyItem=NTMenuItemSprite::create(
									CCSprite::create("heart/bank_an.png"),
									CCSprite::create("heart/bank_an.png"),
									NULL,this,menu_selector(NTHeart::menu_buy));
		pBuyItem->setPosition(ccp(pItem->getPositionX()+75,100));
		pBuyItem->setTag(i);
		pMenu->addChild(pBuyItem);


		//CCSprite *pCoinBg = CCSprite::create("hero/stage_an2.png");
		//pBuyItem->addChild(pCoinBg);
		//pCoinBg->setPosition(ccp(pBuyItem->getContentSize().width/2-30,pBuyItem->getContentSize().height/2));
		//---------------------
//		CCLabelAtlas *pPrice = CCLabelAtlas::create(CCString::createWithFormat("%d",ci_price[i])->getCString(),"heart/nb.png",15,24,'0'-1);
//		pBuyItem->addChild(pPrice);
//		pPrice->setAnchorPoint(ccp(0.5,0.5));
//		pPrice->setPosition(ccp(pBuyItem->getContentSize().width/2+20,pBuyItem->getContentSize().height/2));

		//this->schedule(schedule_selector(NTHeart::update_heart),0.2f);
		
	}

	addBackMenu("share_button/nn.png",ccp(715,415));
// 	CCSprite* pSprite1 = CCSprite::create("share_button/nn.png");
// 	CCSprite* pSprite2 = CCSprite::create("share_button/nn.png");
// 	NTMenuItemSprite* pClose = NTMenuItemSprite::create(pSprite1,pSprite2,NULL,this,menu_selector(NTHeart::menu_close));
// 	pClose->setPosition(ccp(660,420));
// 	pMenu->addChild(pClose);
    
    
  
}
void NTHeart::menu_close(CCObject* p){
	this->runAction(CCSequence::create(CCMoveTo::create(0.2f,ccp(0,600)),
		CCCallFunc::create(this,callfunc_selector(NTHeart::callback_close)),NULL));
	this->unschedule(schedule_selector(NTHeart::update_heart));
}
void NTHeart::callback_close(){
	removeAllChildrenWithCleanup(true);
}

void NTHeart::menu_buy( CCObject* pRender )
{
    //Jerry
    
	CCNode* pNode = (CCNode*)pRender;
	index = pNode->getTag();
    Cocos_order(index);
//	
//	
//	g_OncePayLibao.target = this;
//	g_OncePayLibao.func = (SYSDLG_CallFunc)(&NTHeart::setupdataLibaoState);
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	JniMethodInfo minfo;
//	
////	bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/TestJni","ShowToast", "(I)V");
////
////	if (!isHave) {
////		CCLog("jni:");
////	}else{
////		CCLog("");
////		
////		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,index);
////	}
////	CCLog("");
//    
//    	bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/PayWrapper","Cocos_order", "(I)V");
//    
//    	if (!isHave) {
//    		CCLog("");
//    	}else{
//    		CCLog("");
//    		
//    		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,index);
//    	}
//    	CCLog("");
//    
//    
//#endif


}

void NTHeart::setupdataLibaoState(int i){
    if (i!=0) {
      count1=1;
    }
	
}

void NTHeart::update_heart(float f){
	if(count1==1){
		count1=-1;
        if (index==3) {
            NTGameSave::sharedGameSave()->updateValue(_GS_HEART_COUNTLESS, 1);
            NTStart *pLayer =( NTStart*)this->getParent();
            pLayer->updateHeartView(6);
            return;
        }
		NTGameSave::sharedGameSave()->updataBuyheart(index, true);

		int nSaveHeart =  NTGameSave::sharedGameSave()->getDataById(_GS_HEART);
		NTGameSave::sharedGameSave()->updateValue(_GS_HEART,nSaveHeart+xinshuliang[index]);

		//NTStart *pLayer =( NTStart*)this->getParent();
		//pLayer->updateHeartView(NTGameSave::sharedGameSave()->getDataById(_GS_HEART));
		//pLayer->updateGoldView();
	}
}









