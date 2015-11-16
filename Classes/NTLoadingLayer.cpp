

#include "NTLoadingLayer.h"
#include "AnimatePacker.h"

void NTLoadingLayer::onEnterTransitionDidFinish() {
	CCLayer::onEnterTransitionDidFinish();

	AnimatePacker::getInstance()->loadAnimations("loading/loading.xml");

	initForLoading();
}


void NTLoadingLayer::initForLoading()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
// 	//笑脸
// 	CCSprite* pFace = CCSprite::create("loading/game_huarui.png");
// 	pFace->setPosition(ccp(winSize.width/2, winSize.height*0.55f));
// 	/*pFace->setScale(0.7f);*/
// 	this->addChild(pFace,20);
// 
// 
// 	//花瓣1
// 	for(unsigned int i=0; i<10; i++){
// 		CCSprite* pLeaf = CCSprite::create("loading/game_huaban_0.png");
// 		pLeaf->setPosition(ccp(winSize.width/2, winSize.height*0.55f));
// 		pLeaf->setAnchorPoint(ccp(0.5f,-0.25f));
// 		pLeaf->setRotation(i*36.0f);
// 		this->addChild(pLeaf,1);
// 	}
// 	//花瓣2
// 	CCSprite* pLeaf = CCSprite::create("loading/game_huaban_1.png");
// 	pLeaf->setPosition(ccp(winSize.width/2, winSize.height*0.55f));
// 	pLeaf->setAnchorPoint(ccp(0.5f,-0.1f));
// 	this->addChild(pLeaf,10);
// 	showLight(pLeaf);
// 
// 	//字样
// 	CCSprite* pText = CCSprite::create("loading/game_loading_T.png");
// 	pText->setPosition(ccp(winSize.width/2, winSize.height*0.42f));
// 	this->addChild(pText);

	//tips
	CCSprite* pTips = CCSprite::create("loading/game_loading_1.png");
	pTips->setPosition(ccp(400, winSize.height-171));
	this->addChild(pTips);
	//进度条背景
	CCSprite* pProgressBg = CCSprite::create("loading/game_loading_3.png");
	pProgressBg->setPosition(ccp(400, winSize.height-216));
	this->addChild(pProgressBg);
	//进度条
	m_pProgress = CCProgressTimer::create(CCSprite::create("loading/game_loading_4.png"));
	m_pProgress->setType(kCCProgressTimerTypeBar);
	m_pProgress->setMidpoint(ccp(0, 0));
	m_pProgress->setBarChangeRate(ccp(1, 0));
	m_pProgress->setPercentage(0);
	m_pProgress->setPosition(ccp(400, winSize.height-216));
	this->addChild(m_pProgress);
	m_pProgress->runAction(CCProgressTo::create(6, 80));
	//英雄走路
	CCSprite* pHero = CCSprite::createWithSpriteFrameName("loading_hero_walk0.png");
	pHero->setPositionY(m_pProgress->getContentSize().height/2);
	pHero->setFlipX(true);
	pHero->setScale(0.8f);
	pHero->setAnchorPoint(ccp(0.5f, 0.4f));
	pHero->runAction(CCRepeatForever::create(AnimatePacker::getInstance()->getAnimate("walk_loading")));
	m_pProgress->addChild(pHero, 3, 3);
	pHero->runAction(CCMoveBy::create(6, ccp(m_pProgress->getContentSize().width*0.8f, 0)));

	//进度条前景
	CCSprite* pProgressFg = CCSprite::create("loading/game_loading_2.png");
	pProgressFg->setPosition(ccp(m_pProgress->getContentSize().width/2, m_pProgress->getContentSize().height*0.7f));
	m_pProgress->addChild(pProgressFg);

	//字样
	CCSprite* pText = CCSprite::create("loading/game_loading_0.png");
	pText->setPosition(ccp(400, winSize.height-256));
	this->addChild(pText);
}



void NTLoadingLayer::showLight( CCNode* pSender )
{
	CCRepeatForever* rep = CCRepeatForever::create(
		CCSequence::create(
		CCRotateBy::create(0.0f, 36.0f),
		CCDelayTime::create(0.15f/m_iLoadSpeed),
		NULL
		));
	pSender->runAction(rep);
}

void NTLoadingLayer::setSpeed( float pSpeed )
{
	m_iLoadSpeed = pSpeed;
}

float NTLoadingLayer::getSpeed()
{
	return m_iLoadSpeed;
}

bool NTLoadingLayer::init()
{
	bool Res = false;

	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(255,0,0,0)));
		Res = true;
	} while (0);

	return Res;
}

void NTLoadingLayer::showToEnd(CCFiniteTimeAction* pCallBack)
{
	m_pProgress->runAction(
		CCSequence::createWithTwoActions(
		CCProgressTo::create(1.0f, 100),
		pCallBack
		));
	m_pProgress->getChildByTag(3)->runAction(CCMoveBy::create(1, ccp(m_pProgress->getContentSize().width*0.2f, 0)));
}

void NTLoadingLayer::showToEndCallBack()
{
	this->removeFromParentAndCleanup(true);
}
