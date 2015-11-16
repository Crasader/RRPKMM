#ifndef _NTGold_H_
#define _NTGold_H_

#include "cocos2d.h"
#include "NTCoverLayer.h"
#include "GUI/CCControlExtension/CCControlSlider.h"
#include "NTMenuItem.h"
#define SET_XML_FILE "set/set.xml"
#define SET_PICTURE_PATH "set/"

USING_NS_CC;
USING_NS_CC_EXT;
class NTGold:public NTCoverLayer
{
public:
    CREATE_FUNC(NTGold);
    
    
    
    void onEnter();
    
    void initValues();
    void initUI();
    CCControlSlider *slider;
    
    void menu_buy(CCObject *pSender);
    CCMenuItemSprite *pItem1;
    CCMenuItemSprite *pItem2;
    CCMenuItemSprite *pItem3;
    CCSprite* ccsp1;
    NTMenuItemSprite *pItem;
    // 	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    // 	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    // 	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    // 	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private: 
    CCSprite *m_pBg;
    int ssss;
};

#endif /*_NTGold_H_*/