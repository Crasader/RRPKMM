#ifndef _KICKBOSS_H_
#define _KICKBOSS_H_
#include "cocos-ext.h"
#include "cocos2d.h"
#include "NTCoverLayer.h"
#include "CocoStudio/Armature/CCArmature.h"
#include "NTEffectLayer.h"
#include "NTControlLayer.h"

USING_NS_CC_EXT;
USING_NS_CC;

class KickBoss:public NTCoverLayer
{
public:
    //Jerry--Aizou
    CC_SYNTHESIZE(CCArmature*, m_pArmature, Armature);
	CREATE_FUNC(KickBoss);
    bool m_bIsTouchMu;
     int timeCount;
private:
    CCMenu* m_pMenu;
CCSprite* m_pBg;
    CCLabelAtlas* m_pCount;
    CCLabelAtlas* m_pTimeleft;
    CCProgressTimer* pPowerLeft;
    //CCProgressTimer* pLeft;
    int kickCount;
   
private:
   
	void onEnter();
	void initUI();
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void animationEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
    void update(float dt);
    void timeUpdate(float dt);
    CC_SYNTHESIZE(NTEffectLayer*, m_pEffectLayer, EffectLayer);
   CC_SYNTHESIZE(NTControlLayer*, m_pControlLayer, ControlLayer);
    void coinHitCallBack();
	void hintCallBack(CCNode* pSender);
	
};

#endif