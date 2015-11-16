
/********************************************************************
 *    Œƒº˛√˚  :    NTMESSAGEBOX.CPP
 *    ◊˜’ﬂ    :    cy
 *    ¥¥Ω® ±º‰:    2012/10/22 17:51
 *    Œƒº˛√Ë ˆ:    ƒ£Ã¨∂‘ª∞øÚ
 *********************************************************************/
#include "NTMessageBox.h"
#include "NTMenuItem.h"
#include "NTConstants.h"

USING_NS_CC;

bool NTMessageBox::init() {
    bool bRet = false;

    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 160)));
		m_pTouch = NULL;
		m_pMenu = NULL;
        bRet = true;
    } while (0);

	m_bTouchMenu=false;

    return bRet;
}

void NTMessageBox::onEnter() {
    CCLayerColor::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, PRIORITY_MESSAGE_BOX, true);
}

void NTMessageBox::onExit() {
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayerColor::onExit();
}

//************************************
// Method:    setSeletor
// FullName:  NTMessageBox::setSeletor
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: cocos2d::CCMenuItem * selectorOk
// Parameter: cocos2d::CCMenuItem * selectorCancel
// Desc:      ÷˜“™Ω”ø⁄: »∑∂®”Î»°œ˚∞¥≈•
//************************************
void NTMessageBox::setSeletor( cocos2d::CCMenuItem* selectorOk, cocos2d::CCMenuItem* selectorCancel ) {
    m_pMenu = CCMenu::create(selectorOk, selectorCancel, NULL);
    m_pMenu->setPosition(CCPointZero);
    addChild(m_pMenu, 3);
}

void NTMessageBox::setSeletor( cocos2d::CCMenuItem* selector0, cocos2d::CCMenuItem* selector1, cocos2d::CCMenuItem* selector2 )
{
	m_pMenu = CCMenu::create(selector0, selector1, selector2, NULL);
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu, 1);
}
void NTMessageBox::setSeletor( cocos2d::CCMenuItem* selector0, cocos2d::CCMenuItem* selector1, cocos2d::CCMenuItem* selector2 ,CCMenuItem* selector3 ,CCMenuItem* selector4)
{
    m_pMenu = CCMenu::create(selector0, selector1, selector2,selector3,selector4, NULL);
    m_pMenu->setPosition(CCPointZero);
    addChild(m_pMenu, 3);
}

bool NTMessageBox::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
	if (m_bTouchMenu)
	{
		return false;
	}

    if (m_pMenu != NULL) {
        m_pTouch = pTouch;
        m_bTouchMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    }

    return true;
}

void NTMessageBox::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (m_pTouch == pTouch ) {
        if (m_bTouchMenu) {
            m_pMenu->ccTouchMoved(pTouch, pEvent);
        }
    }
}

void NTMessageBox::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (m_pTouch == pTouch ) {
        if (m_bTouchMenu) {
            m_pMenu->ccTouchEnded(pTouch, pEvent);
            m_bTouchMenu = false;
        }
        m_pTouch = NULL;
    }
}

void NTMessageBox::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (m_pTouch == pTouch ) {
        if (m_bTouchMenu) {
            m_pMenu->ccTouchEnded(pTouch, pEvent);
            m_bTouchMenu = false;
        }
        m_pTouch = NULL;
    }
}

void NTMessageBox::setMenu( cocos2d::CCMenu* menu )
{
	if(menu != NULL) {
		m_pMenu = menu;
		addChild(m_pMenu, 1);
	}
}

//¥¥Ω®∂‘ª∞øÚ
NTMessageBox* NTMessageBox::msgInit( CCPoint pBgPos, CCPoint pInfoPos, CCPoint pOkPos, 
	SEL_MenuHandler pOkCallBack, SEL_MenuHandler pCancelCallBack, char *infoName, CCNode* pThis, int pType)
{

	NTMessageBox* pLayer = NTMessageBox::create();

	//
	CCPoint pOk;
	CCPoint pCancel;
	char okName[40];
	if(pType==MSG_DLG_TYPE_OK){

		pOk = ccpAdd(pOkPos, ccp(0, 0));
		sprintf(okName, "msg/Start_ui_offandok1.png");

		CCSprite *bg = CCSprite::create("guide/info_bg1.png");
		bg->setPosition(pBgPos);
		pLayer->addChild( bg );

		CCSprite *txt;
		txt = CCSprite::create(infoName);
		txt->setPosition(pInfoPos);
		pLayer->addChild( txt );

		CCSprite* ok1 = CCSprite::create(okName);
		CCSprite* ok2 = CCSprite::create(okName);
		NTMenuItemSprite* continueBtn = NTMenuItemSprite::create(
			ok1,
			ok2,
			NULL,
			pThis,
			pOkCallBack
			);
		continueBtn->setPosition(pOk);	
		continueBtn->setTag(OK_TAG);

		CCMenu *pMenu = CCMenu::create( continueBtn,NULL);
		pMenu->setPosition( CCPointZero );

		pLayer->setMenu(pMenu);
		return pLayer;

	}else{
		NTMessageBox* pLayer = NTMessageBox::create();

		CCSprite *bg = CCSprite::create("msg/Start_ui_offandok0.png");
		bg->setPosition(pBgPos);

		CCSprite* ok1 = CCSprite::create("msg/Start_ui_offandok1.png");
		CCSprite* ok2 = CCSprite::create("msg/Start_ui_offandok1.png");
		NTMenuItemSprite* continueBtn = NTMenuItemSprite::create(
			ok1,
			ok2,
			NULL,
			pThis,
			pOkCallBack
			);
		continueBtn->setPosition(ccpAdd(pOkPos, ccp(-60, 0)));	
		continueBtn->setTag(OK_TAG);

		CCSprite* cancel1 = CCSprite::create("msg/Start_ui_offandok2.png");
		CCSprite* cancel2 = CCSprite::create("msg/Start_ui_offandok2.png");
		NTMenuItemSprite* skipBtn = NTMenuItemSprite::create(
			cancel1,
			cancel2,
			NULL,
			pThis,
			pCancelCallBack
			);
		skipBtn->setPosition(ccpAdd(pOkPos, ccp(60, 0)));
		skipBtn->setTag(CANCEL_TAG);

		CCMenu *pMenu = CCMenu::create( continueBtn, skipBtn, NULL );
		pMenu->setPosition( CCPointZero );

		pLayer->addChild( bg );
		pLayer->setMenu(pMenu);

		return pLayer;
	}

}



