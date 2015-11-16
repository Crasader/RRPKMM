/********************************************************************
 *    文件名  :    NTCOVERLAYER.H
 *    作者    :    yobo
 *    创建时间:    2013/11/22 10:05
 *    文件描述:    遮盖层基类
 *********************************************************************/
#ifndef _H_NTCOVERLAYER_H_
#define _H_NTCOVERLAYER_H_
#include "cocos2d.h"
#include "menu_nodes/CCMenuItem.h"
using namespace cocos2d;
class NTCoverLayer:public CCLayerColor
{
public:


	virtual bool init();
protected:
	virtual void registerWithTouchDispatcher();

public:
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);  
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);  
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);  
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual void bornOnLayer(CCLayer *layer);
	virtual void closeSelf();

	void closeSelfCallBack();

	CC_SYNTHESIZE(CCMenu*,m_pMenu,Menu);

	virtual void addBackMenu(const char* fileName,CCPoint pt );

	virtual void backItemClick(CCObject *pSender);

	//CCLayer* layer;
private:
	

	//触摸分发菜单的标志
	bool m_bTouchedMenu;
	bool m_bTouchEnd;


};


#endif // _H_NTCOVERLAYER_H_