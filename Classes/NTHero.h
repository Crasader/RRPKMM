/*游戏准备界面的英雄购买界面***/
#ifndef _NTHERO_H_
#define _NTHERO_H_

#include "cocos2d.h"
#include "NTConstants.h"
#include "NTMenuItem.h"
#include "NTCoverLayer.h"
#include "Assistant.h"

#define HERO_XML_FILE "hero/hero.xml"
#define HERO_PICTURE_PATH "hero/"


USING_NS_CC;

class NTHero:public NTCoverLayer
{
public:
	CREATE_FUNC(NTHero);
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
	void setupdataLibaoState(int i);
	int const1;
	void update_hero(float f);
    void update_button();
	int inxde;
	CCNode* pNode;
	//触摸事件
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	//初始化数据
	void initValues();
	//初始化UI
	void initUI();
	//生成出战按钮
	void initFightItem(const char *name, int posx, int posy, int pid);
	void initFightItem(const char *name, int posx, int posy, int pid,CCSprite *sprite);
	//按钮回调事件
	void menu_close(CCObject* pRender);
	void callback_close();
private:
	CCLabelAtlas* m_pHeroLevel[ACTOR_MAX];
	CCProgressTimer* m_pHeroLevelBar[ACTOR_MAX];

	CCLabelAtlas* m_pHeroExtraMark[ACTOR_MAX];
	CCLabelAtlas* m_pHeroExtraGold[ACTOR_MAX];
	
	CCLabelAtlas* m_pHeroBuy[ACTOR_MAX];
	CCLabelAtlas* m_pHeroUpgrade[ACTOR_MAX];

	NTMenuItemSprite* m_pBuyItem[ACTOR_MAX];
	NTMenuItemSprite* m_pUpgradeItem[ACTOR_MAX];
	NTMenuItemSprite* m_pSelectItem[ACTOR_MAX];
	CCSprite* m_pSpriteBoard[ACTOR_MAX];
private:
	void menu_buy(CCObject* pRender);
	void menu_upgrade(CCObject* pRender);
	void menu_select(CCObject* pRender);
};

#endif /*_NTHERO_H_*/