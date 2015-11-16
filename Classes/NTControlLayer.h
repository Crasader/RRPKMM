#ifndef __H_NTCONTROLLAYER_H__
#define __H_NTCONTROLLAYER_H__

#include "cocos2d.h"
#include "NTActor.h"
#include "NTMiniMap.h"
#include "NTGameHud.h"
#include "NTGameSave.h"
#include "Assistant.h"
#include "NTGameSound.h"

USING_NS_CC;

class NTGameHud;

class NTControlLayer : public CCLayer
{
	typedef void (CCObject::*SYSDLG_CallFunc)(int);
	struct SDialogContent
	{
		CCObject* target;
		SYSDLG_CallFunc func;
	};
public:
    bool init();  
    CREATE_FUNC(NTControlLayer);
	void onExit();
	void onEnter();
	void onEnterTransitionDidFinish();
	char sss[10];
	void pauseGameAll( bool pFlag );
	CCLabelTTF *label;
	void menu_close(CCObject* pRender);
	void menu_reset(CCObject* pRender);
	void menu_Actor1(CCObject* pRender);
	void menu_Actor2(CCObject* pRender);
	void menu_props1(CCObject* pRender);
	void menu_props2(CCObject* pRender);
	void menu_props3(CCObject* pRender);
	void menu_close2(CCObject* p);
	void menu_back(CCObject* p);
	void resurrect(CCObject* p);
	void menu_close2_1();
	void menu_close2_2();
	void menu_close2_3();
//	void setupdataLibaoState(int i);
//	void setupdataLibaoState_2(int i);
//	void setupdataLibaoState_3(int i);
//	void setupdataLibaoState_4(int i);
    void purchaseCallBack(int i);
//	void menu_back_1(CCObject* p);

	void menu_back1(CCObject* p);
	void menu_CallBack();
	void menu_CallBack1();
	void menu_CallBack2();
	void menu_jiasu(CCObject* p);
	void menu_jiasu2();
	//…˙≥…∏¥ªÓ∞¥≈•
	void menu_fuhuo();
	CCLayer* layer1;
	CCLayer* layer;
	CCMenu* jiasuBtn;
	CCMenu* menu2;
	CCProgressTimer* left;
	CCProgressTo* progress;
private:
	// default implements are used to call script callback if exist
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void update(float dt);
	void update_button(float dt);
	void collideWithActor(NTActor* pActor);

	/*void landSpeedChange( NTActor* pNode1, NTActor* pNode2, float fValue );*/
	void landSpeedChangeCallBack(CCNode* pSender);
public:
    int m_iMiles;
    int m_iScore;
    int count2;
    void revive();
    NTGameSound* gameSound;
private:
	CCLabelTTF* m_pLabelSpeed;
	CCLabelTTF* m_pLabelLength;
	CCLabelTTF* m_pLabelMapMoveGap;
	CCLabelTTF* m_pLabelTime;
	float m_fTime;

	
	bool m_bIsGameOver;
	bool m_bIsInSuperMode;
	bool m_bIsPause;
	bool sex;
	CCSprite* m_pSlide;
	CCSprite* m_pJump;
	CCSprite* m_pJiaSu;
	int count1;
	
	int index;
	int index1;
    int m_TempScore;
	CCSprite* sp;
	
    bool isKickBoss;
private:
	void showSuperMode();
	void updateForSuperMode(float dt);
	void showGameOver();
	void showGameOverCallBack();
public:
   
	CC_SYNTHESIZE(NTActor*, m_pActor, Actor);
	CC_SYNTHESIZE(NTActor*, m_pActorNpc, NTActorNpc);
	CC_SYNTHESIZE(CCArmature*, m_pArmaturePet, ArmaturePet);
	CC_SYNTHESIZE(NTMapLayer*, m_pMapLayer, MapLayer);
	CC_SYNTHESIZE(NTMiniMap*, m_pMiniMap, MiniMap);
	CC_SYNTHESIZE(NTGameHud*, m_pGameHud, GameHud);
    CC_SYNTHESIZE(bool, m_relife, Relife);
	//“˝µº
private:
	CC_SYNTHESIZE(bool, m_bGuideOver, GuideOver);
	void initGuideLayer();
	void initGuide();
	void runGuide(CCNode* pSender, void* pData);
	void runGuideCallBack( CCNode* pSender, void* pData );
	//Ω¯»Î’˝ Ω”Œœ∑
	void goToRealGame();
public:
	bool m_bIsBegin;
	void showGameBegin();
	void showGameBeginCallBack();
	void removeSelfCallBack(CCNode* pSender);
public:

};

#endif // __H_NTMAPLAYER_H__
