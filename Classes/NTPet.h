/*宠物类*/
#ifndef _NTPET_H_
#define _NTPET_H_

#include "cocos2d.h"
#include "NTConstants.h"
#include "NTMenuItem.h"
#include "Assistant.h"
#include "NTCoverLayer.h"

#define Pet_XML_FILE "hero/pet.xml"
#define Pet_PICTURE_PATH "hero/"

USING_NS_CC;

class NTPet:public NTCoverLayer
{
	typedef void (CCObject::*SYSDLG_CallFunc)(int);
	struct SDialogContent
	{
		CCObject* target;
		SYSDLG_CallFunc func;
	};
public:
	CREATE_FUNC(NTPet);
	void bornOnScene();
private:
	CCSprite* m_pBg;
	CCMenu* m_pMenu;
	bool m_bIsTouchMu;
private:

	bool init();
	void onEnter();
	void onExit();
	void onEnterTransitionDidFinish();

	//触摸事件
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	void setupdataLibaoState(int i);
	void update_pet(float f);
	int count1;
	int index1;
	CCNode* pNode;
	//初始化数据
	void initValues();
	//初始化UI
	void initUI();
	//生成出战按钮
	void initFightItem(const char *name, int posx, int posy, int pid);
	
	//按钮回调事件
	void menu_close(CCObject* pRender);
	void callback_close();
private:
	//宠物等级
	CCLabelAtlas* m_pPetLevel[ACTOR_MAX];
	CCProgressTimer* m_pPetLevelBar[ACTOR_MAX];

	CCLabelAtlas* m_pPetExtraMark[ACTOR_MAX];
	CCLabelAtlas* m_pPetExtraGold[ACTOR_MAX];
	
	CCLabelAtlas* m_pPetBuy[ACTOR_MAX];
	CCLabelAtlas* m_pPetUpgrade[ACTOR_MAX];

	NTMenuItemSprite* m_pBuyItem[ACTOR_MAX];
	NTMenuItemSprite* m_pUpgradeItem[ACTOR_MAX];
	NTMenuItemSprite* m_pSelectItem[ACTOR_MAX];
	CCSprite* m_pSpriteBoard[ACTOR_MAX];
private:
	//回调函数
	void menu_buy(CCObject* pRender);
	void menu_upgrade(CCObject* pRender);
	void menu_select(CCObject* pRender);
};

#endif /*_NTPET_H_*/