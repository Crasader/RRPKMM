//
//  AutoScrollLayer.cpp
//  BombExpert_box2d
//
//  Created by soul on 13-3-28.
//
//

#include "AutoScrollLayer.h"

AutoScrollLayer::AutoScrollLayer()
{
    CCLOG("AutoScrollLayer");
}

AutoScrollLayer::~AutoScrollLayer()
{
    CCLOG("~AutoScrollLayer");
}

bool AutoScrollLayer::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_iDirection=DIR_LEFT;
	m_fSpeed=2;

	CCSprite *shadow1 = CCSprite::create(fileName.c_str());
	shadow1->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(shadow1, 0, 0);
	CCSprite *shadow2 = CCSprite::create(fileName.c_str());
	shadow2->setPosition(ccp(winSize.width/2-m_iDirection*shadow1->getContentSize().width, winSize.height/2));
	this->addChild(shadow2, 1, 1);

	schedule(schedule_selector(AutoScrollLayer::update));

	return true;
}

AutoScrollLayer *AutoScrollLayer::create(const char *fileName)
{
    AutoScrollLayer *pRet = new AutoScrollLayer();
    pRet->fileName=fileName;
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

void AutoScrollLayer::update(float dt)
{
	float fMoveGap = m_fSpeed*dt;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *shadow1 = (CCSprite *)getChildByTag(0);

    {
        shadow1->setPositionX(shadow1->getPositionX()+m_iDirection*fMoveGap);
    }
    
    CCSprite *shadow2 = (CCSprite *)getChildByTag(1);

    {
        shadow2->setPositionX(shadow2->getPositionX()+m_iDirection*fMoveGap);
    }

	if((shadow1->getPositionX()+shadow1->getContentSize().width/2<=0 && m_iDirection==DIR_LEFT)
		|| 
		(shadow1->getPositionX()-shadow1->getContentSize().width/2>=winSize.width && m_iDirection==DIR_RIGHT)
		)
	{
		shadow1->setPositionX(shadow2->getPositionX()-m_iDirection*shadow1->getContentSize().width);
	}
    
	if((shadow2->getPositionX()+shadow2->getContentSize().width/2<=0 && m_iDirection==DIR_LEFT)
		|| 
		(shadow2->getPositionX()-shadow2->getContentSize().width/2>=winSize.width && m_iDirection==DIR_RIGHT)
		)
	{
		shadow2->setPositionX(shadow1->getPositionX()-m_iDirection*shadow2->getContentSize().width);
	}
}

void AutoScrollLayer::onEnter()
{
    CCLOG("AutoScrollLayer-onEnter");
    CCLayer::onEnter();
}

void AutoScrollLayer::onExit()
{
    CCLOG("AutoScrollLayer-onExit");
    CCLayer::onExit();
}

void AutoScrollLayer::stop()
{
    unschedule(schedule_selector(AutoScrollLayer::update));
}

void AutoScrollLayer::start()
{
    schedule(schedule_selector(AutoScrollLayer::update));
}







