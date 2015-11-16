#ifndef _NTSTART_H_
#define _NTSTART_H_

#include "cocos2d.h"
#include "NTJniHelper.h"
#include "NTRank.h"
#include "NTTask.h"


#define START_XML_FILE "start/start_ui.xml"
#define START_PICTURE_PATH "start/"

USING_NS_CC;

class NTStart:public CCLayerColor,public NTRenameDelegate
{
	typedef void (CCObject::*SYSDLG_CallFunc)(int);
	struct SDialogContent
	{
		CCObject* target;
		SYSDLG_CallFunc func;
	};
public:
   
	CREATE_FUNC(NTStart);
	void bornOnScene();
	static cocos2d::CCScene* scene();
	void updateHeartView(int nHeart);
	void updateGoldView();
	void setupdataLibaoState(int i);
	void update_meiri(float f);
	int const1;
	CCNode* pNode1;
//	CCLayer* laye;
private:
	CCSprite* m_pBg;
	CCMenu* m_pMenu;
	bool m_bIsTouchMu;
	CCMenuItemSprite* img_caca;
	CCMenuItemSprite* img;
	CCMenuItemSprite* ismag;
	CCSprite* libao_sp;
	CCSprite* meiri;
    CCMenuItemSprite* pMenuItem;
private:
    bool isFly;
	bool init();
	void loadRes();
	void onEnter();
	void onExit();
	void onEnterTransitionDidFinish();
    //Jerry
    void update(float dt);
    
	//¥•√˛ ¬º˛
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	//≥ı ºªØ ˝æ›
	void initValues();
	//≥ı ºªØUI
	void initUI();
	
	//∞¥≈•ªÿµ˜ ¬º˛
	void menu_close(CCObject* pRender);
	void callback_close();
    void menu_exit(CCObject* pRender);
	void menu_start(CCObject* pRender);
	void menu_sign(CCObject* pRender);
	void menu_set(CCObject* pRender);
	void menu_gift(CCObject* pRender);
	void menu_hero(CCObject* pRender);
	void menu_pet(CCObject* pRender);
	void menu_heart(CCObject* pRender);
	void menu_props(CCObject* pRender);
	void menu_gold(CCObject *pRender);
	void menu_back_libao_caca(CCObject* pRender);
	void menu_back_libao(CCObject* pRender);
    void menu_more(CCObject* pRender);
    void menu_task(CCObject* pRender);
	//Ω±“
	CCLabelAtlas *m_pGoldText;



	//∞Æ–ƒ
	CCSprite *m_pHeart[5];
	CCLabelAtlas *m_pExtraHeartText;
    
    //Jerry--HeartSchedule
    CCLabelAtlas *m_pMin;
    CCLabelAtlas *m_pSec;
    CCLabelAtlas *m_pPoint;
    CCSprite *m_pMax;

    
    CCSprite *m_pHeartCountless;
 
    

	void playHeartFly(int heartId);

	void playHeartFlyCallBack();



	CCParticleSystemQuad *m_pLzStart;

	bool m_bIsInAnimate;
	
private:
	void updateForGold(float dt);

	virtual void registerMyName( std::string strName );

	void toSaveMyName(float dt);

	std::string m_sName;

	CC_SYNTHESIZE(NTTask*,m_pTask,Task);
	CC_SYNTHESIZE(NTRank*,m_pRankLayer,RankLayer);

};

#endif /*_NTSTART_H_*/