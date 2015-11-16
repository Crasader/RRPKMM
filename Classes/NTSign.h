#ifndef _NTSIGN_H_
#define _NTSIGN_H_

#include "cocos2d.h"
#include "NTCoverLayer.h"
#include "NTMenuItem.h"
#define SIGN_XML_FILE "sign/sign.xml"
#define SIGN_PICTURE_PATH "sign/"

USING_NS_CC;
enum{
    TASK_HERO_LEVELUP=1,
    TASK_HIT_BOX,
    TASK_GOLD_MODE,
    TASK_SCORE_10000,
    TASK_SCORE_30000,
    TASK_SCORE_50000,//6
    TASK_HEART_BUY,
    TASK_PET_LEVELUP,
    TASK_REVIVE,
    TASK_SCORE_80000,
    TASK_HEART_USEUP,//11
    TASK_KICK_BOSS
};

class NTSign:public NTCoverLayer
{
public:
	CREATE_FUNC(NTSign);
	NTSign();

	void onEnter();
    void initValue();
	void initUI();
	CC_SYNTHESIZE(int,m_nSelectDay,SelectDay);
	void setSignDay(int nday);
    int m_taskId[3];
    bool m_taskFinish[3];
    CCSprite *pSignBg;
    CCSprite *pTaskBg;
private:
 

	CCSprite *m_pSelect[7];
	CCSprite *m_pUnSelect[7];
	CCSprite *m_pSelectLogo[7];
    CCSprite *m_pRewardGot[3];
    CCSprite *m_pTaskNo[3];
    CCSprite *m_pTaskYes[3];
    CCSprite *m_pTaskDec[3];
    CCLabelAtlas *m_pTaskLabel[3];
    CCSprite *m_pTaskDec0[3];
    CCLabelAtlas *m_pTaskLabel0[3];
	void menu_complete(CCObject *pSender);
    void menu_signBg(CCObject *pSender);
    void menu_taskBg(CCObject *pSender);
    NTMenuItemSprite *pTaskButton;
    NTMenuItemSprite *pSignButton;
    int taskcomplish;
};

#endif /*_NTSIGN_H_*/