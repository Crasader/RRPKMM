#ifndef _NTSET_H_
#define _NTSET_H_

#include "cocos2d.h"
#include "NTCoverLayer.h"
#include "GUI/CCControlExtension/CCControlSlider.h"
#include "NTMenuItem.h"
#define SET_XML_FILE "set/set.xml"
#define SET_PICTURE_PATH "set/"

USING_NS_CC;
USING_NS_CC_EXT;
class NTSet:public NTCoverLayer
{
public:
	CREATE_FUNC(NTSet);
	


	void onEnter();


	//初始化数据
	void initValues();
	//初始化UI
	void initUI();
	CCControlSlider *slider;
	//-------  按钮回调
	void menu_show(CCObject *pSender);
	
	void backgroudMusicChanged(CCObject *sender, CCControlEvent controlEvent);

	void effectChanged(CCObject *sender, CCControlEvent controlEvent);

	void menu_about(CCObject *pSender);
	void menu_about2(CCObject *pSender);
	void menu_about3(CCObject *pSender);
	void menu_back_about(CCObject* p);
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

#endif /*_NTSET_H_*/