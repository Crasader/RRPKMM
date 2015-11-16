

#include "NTAutoScrollLayer.h"



NTAutoScrollLayer::NTAutoScrollLayer()
{

}

bool NTAutoScrollLayer::init()
{
	m_iDirection=NT_DIR_LEFT;
	m_fSpeed=2;
	m_pAimPos = CCPointZero;
	m_pBackPos = CCPointZero;
    
	m_pShadow = CCSprite::create(getFileName().c_str());
	m_pShadow->setPosition(getPicturePos());
	/*shadow->getTexture()->setAliasTexParameters();*/
    this->addChild(m_pShadow);
    
    schedule(schedule_selector(NTAutoScrollLayer::update));
    
    return true;
}

NTAutoScrollLayer *NTAutoScrollLayer::create(const char *fileName, CCPoint pPos)
{
    NTAutoScrollLayer *pRet = new NTAutoScrollLayer();
    pRet->setFileName(fileName);
	pRet->setPicturePos(pPos);
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

void NTAutoScrollLayer::update(float dt)
{
	float fMoveGap = m_fSpeed*dt;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//移动
    setPositionX(getPositionX()+fMoveGap);
	//是否到达终点
	float pGap = getPositionX()-getAimPos().x;
	if(pGap<=0){
		//置回
		setPosition(ccpAdd(getBackPos(), ccp(pGap, 0)));
	}
}

void NTAutoScrollLayer::onEnter()
{
    CCLayer::onEnter();
}

void NTAutoScrollLayer::onExit()
{
    CCLayer::onExit();
}

void NTAutoScrollLayer::stop()
{
    unschedule(schedule_selector(NTAutoScrollLayer::update));
}

void NTAutoScrollLayer::start()
{
    schedule(schedule_selector(NTAutoScrollLayer::update));
}

void NTAutoScrollLayer::showFadeIn()
{
	m_pShadow->setOpacity(0);
	m_pShadow->runAction(CCFadeIn::create(1.0f));
}










