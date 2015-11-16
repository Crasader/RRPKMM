#include "NTGold.h"
#include "NTGameSave.h"
#include "NTConstants.h"

void NTGold::onEnter()
{
    NTCoverLayer::onEnter();
    initValues();
    initUI();
}



void NTGold::initValues()
{
    
}

void NTGold::initUI()
{
 
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  
            m_pBg = CCSprite::create("Gold/stage_dk.png");
            m_pBg->setPosition(ccp(winSize.width/2, winSize.height/2));
            this->addChild(m_pBg);
            
            //≥ı ºªØMENU
            m_pMenu = CCMenu::create();
            m_pMenu->setPosition(CCPointZero);
            m_pMenu->setAnchorPoint(CCPointZero);
            m_pMenu->setTouchEnabled(false);
            this->addChild(m_pMenu,100);
            
            //πÿ±’∞¥≈•
            addBackMenu("share_button/nn.png",ccp(710,430));
            pItem=NTMenuItemSprite::create(
                                           CCSprite::create("heart/bank_an.png"),
                                           CCSprite::create("heart/bank_an.png"),
                                           NULL,this,menu_selector(NTGold::menu_buy));
            
            pItem->setPosition(ccp(394,80));
            m_pMenu->addChild(pItem);

}


void NTGold::menu_buy( CCObject *pSender )
{
    Cocos_order(9);
}





