#include "NTGift.h"
#include "NTMenuItem.h"
#include "NTConstants.h"

void NTGift::onEnter()
{
	NTCoverLayer::onEnter();
	initUI();
}
void NTGift::initUI()
{
    CCSprite* bg =CCSprite::create("gift/gift_1.png");
    this->addChild(bg);
    CCMenu *pMenu = CCMenu::create();
    this->addChild(pMenu,2);
    pMenu->setAnchorPoint(CCPointZero);
    pMenu->setPosition(CCPointZero);
    setMenu(pMenu);
    NTMenuItemSprite* pGet= NTMenuItemSprite::create(CCSprite::create("heart/bank_an.png"),CCSprite::create("heart/bank_an.png"),this,
                                                      menu_selector(NTGift::pGetCallback));
    NTMenuItemSprite* pExit= NTMenuItemSprite::create(CCSprite::create("share_button/nn.png"),CCSprite::create("share_button/nn.png"),this,
                                                     menu_selector(NTGift::pExitCallback));
    pMenu->addChild(pGet);
    pMenu->addChild(pExit);
    bg->setPosition(ccp(350,250));
    pGet->setPosition(ccp(420,100));
    pExit->setPosition(ccp(630,380));
}
void NTGift::pGetCallback(CCObject *p)
{
    Cocos_order(10);
    
}
void NTGift::pExitCallback(CCObject *p)
{
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
}

