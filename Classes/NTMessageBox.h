
/********************************************************************
 *    文件名  :    NTMESSAGEBOX.H
 *    作者    :    cy
 *    创建时间:    2012/10/22 17:45
 *    文件描述:    模态对话框 - 可作通用类
 *********************************************************************/

#ifndef _H_NTMESSAGEBOX_H_
#define _H_NTMESSAGEBOX_H_

#include "cocos2d.h"

#define OK_TAG	   100
#define CANCEL_TAG 101
#define GameLayerMSG	1012
#define TEST_MODE 0

enum{
	MSG_BUY_SKILL1 = 1,
	MSG_BUY_SKILL2,
	MSG_BUY_SKILL3,
	MSG_BUY_GIFT,
	MSG_BUY_BOOM,
	MSG_BUY_LEVEL_LIMIT,
	MSG_BUY_ENERY
};

USING_NS_CC;

enum{
	MSG_DLG_TYPE_OK,
	MSG_DLG_TYPE_OK_CANCEL,
	MSG_DLG_TYPE_CALL_US
};

class NTMessageBox : public cocos2d::CCLayerColor {
public:	
	CREATE_FUNC(NTMessageBox);
public:
	void setSeletor(cocos2d::CCMenuItem* selectorOk, cocos2d::CCMenuItem* selectorCancel);
	// 战斗界面-结算过程 扩展
	void setSeletor(cocos2d::CCMenuItem* selector0, cocos2d::CCMenuItem* selector1, cocos2d::CCMenuItem* selector2);
	// 游戏暂停界面-扩展
    void setSeletor(CCMenuItem* selector0, CCMenuItem* selector1,CCMenuItem* selector2,CCMenuItem* selector3,CCMenuItem* selector4);
    
	void setMenu(cocos2d::CCMenu* menu);

	//MR.YAN	
	//---------------------------------------------------
	static NTMessageBox* msgInit(
		CCPoint pBgPos, CCPoint pInfoPos, CCPoint pOkPos, 
		SEL_MenuHandler pOkCallBack, SEL_MenuHandler pCancelCallBack, char *infoName, 
		CCNode* pThis, int pType=-1);
	//---------------------------------------------------

private:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

//	void setWaitTime(float time, cocos2d::CCCallFunc* callFun);
private:
	cocos2d::CCMenu* m_pMenu;
	bool m_bTouchMenu;
	cocos2d::CCTouch* m_pTouch;
};

#endif // _H_NTMESSAGEBOX_H_