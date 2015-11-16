#ifndef _NTGAMEHUD_H_
#define _NTGAMEHUD_H_

#include "cocos2d.h"
#include "NTControlLayer.h"
#include "NTMessageBox.h"
#include "NTMenuItem.h"

USING_NS_CC;

class NTControlLayer;

class NTGameHud:public CCLayer
{
public:
	CREATE_FUNC(NTGameHud);
	void updateScores(int iScore);
	void updateDistance(int iMiles);
    void updateGameSaveDistance();
	void updateNpcHp(int iCurrentBlood, int iType);
	void updatePlayerHp(int iCurrentBlood);
    void showKickBoss();
public:
	void showGameOverMsg(int iScore, int iMiles);
    void pause(bool pFlag);
private:
	CCMenu* m_pMenu;
	bool m_bIsTouchMu;
    NTMessageBox* pMsg;
    int index;
	void replayCallBack( cocos2d::CCObject* pSender );
	void backToStateCallBack(cocos2d::CCObject* pSender);
	void musicSwitchCallBack(cocos2d::CCObject* pSender);
	void pauseItemCallBack( cocos2d::CCObject* pSender);
	
	void pauseItemLock();
	bool m_bIsPauseLock;
	CC_SYNTHESIZE(bool, m_bIsPause, IsPause);
	CCMenuItemToggle* m_pPauseItem;
	CC_SYNTHESIZE(NTControlLayer*, m_pControlLayer, ControlLayer);

private:
    void update(float dt);
	bool init();
	void onEnter();
	void onExit();
	void onEnterTransitionDidFinish();
	CCMenuItemToggle* toggleMusic;
	//¥•√˛ ¬º˛
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	//≥ı ºªØ ˝æ›
	void initValues();
	//≥ı ºªØUI
	void initUI();
    bool isCall;
    NTMenuItemSprite* getMenuItem;
    NTMenuItemSprite* pTitleGet;

private:
	CCLabelAtlas* m_pScoreLabel;
	CCLabelAtlas* m_pMilesLabel;
	CCProgressTimer* m_pPlayerHp;
	CCProgressTimer* m_pNpcHp;
private:
	void onMsgOkCallBack(CCObject *pSender);
    void onMsgReCallBack(CCObject *pSender);
    void onGetCallBack(CCObject *pSender);
    void menu_gift(CCObject *pSender);

};

#endif /*_NTGAMEHUD_H_*/