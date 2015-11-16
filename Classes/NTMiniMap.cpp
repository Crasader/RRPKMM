#include "NTMiniMap.h"
#include "NTConstants.h"

bool NTMiniMap::init()
{
	bool Res = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		initValues();
		initUI();
		Res = true;
	} while (0);

	return Res;
}

void NTMiniMap::onEnter()
{
	CCLayer::onEnter();
	/*CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, PRIORITY_NTLAYER_MSG,true);*/
}


void NTMiniMap::onExit()
{
	/*CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);*/
	CCLayer::onExit();
}


void NTMiniMap::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}


void NTMiniMap::initValues()
{
	m_bIsTouchMu = false;
	m_pMenu = NULL;
	m_fPowerPercent = 0;
}

void NTMiniMap::initUI()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

// 	//±≥æ∞Ãı
// 	roadScrollEffect();
// 
// 	//NPCÕ∑œÒ
// 	m_pNPCHead = CCSprite::create("game/girl_head.png");
// 	m_pNPCHead->setPosition(ccp(352, 77));
// 	this->addChild(m_pNPCHead);
// 	//÷˜Ω«Õ∑œÒ
// 	m_pPlayerHead = CCSprite::create("game/boy_head.png");
// 	m_pPlayerHead->setPosition(ccp(327, 77));
// 	this->addChild(m_pPlayerHead);
// 	//∆¡ƒª ”“∞øÚ
// 	m_pScreenRect = CCSprite::create("game/screen_rect.png");
// 	m_pScreenRect->setPosition(ccp(400, 62));
// 	this->addChild(m_pScreenRect);
// 
// 	//∆¡ƒªµƒ–Èƒ‚∆ ºµ„
// 	m_pScreenStartPos = ccp(m_pScreenRect->getPositionX()-m_pScreenRect->getContentSize().width/2, m_pScreenRect->getPositionY());
// 	//∆¡ƒªÀı∑≈±∂ ˝
// 	m_fScreenScale = winSize.width/m_pScreenRect->getContentSize().width;

	//ƒ‹¡øΩ¯∂»Ãı±≥æ∞
	CCSprite* pPowerBar = CCSprite::create("game/game_jdt.png");
	pPowerBar->setPosition(ccp(395, winSize.height-439.0f));
	this->addChild(pPowerBar);
   
	//ƒ‹¡øΩ¯∂»Ãı«∞æ∞
	CCSprite* pPowerBarFg=CCSprite::create("game/game_jdt1.png");
	m_pPowerBar=CCProgressTimer::create(pPowerBarFg);
	m_pPowerBar->setType(kCCProgressTimerTypeBar);
	m_pPowerBar->setMidpoint(ccp(0,0)); 
	m_pPowerBar->setBarChangeRate(ccp(1,0));
	m_pPowerBar->setPosition(ccp(405, winSize.height-438.0f));
	m_pPowerBar->setPercentage(m_fPowerPercent);
	this->addChild(m_pPowerBar);
    CCSprite* pPowerTitle =CCSprite::create("game/game_jdt2.png");
    pPowerTitle->setPosition(ccp(13,12));
    m_pPowerBar->addChild(pPowerTitle,2);
	// ˝÷µ
	m_pPowerAtlas = CCLabelAtlas::create("0:", "game/game_jdt_sz.png", 13, 21,'0');
	m_pPowerAtlas->setPosition(ccp(410, winSize.height-438.0f));
	m_pPowerAtlas->setAnchorPoint(ccp(0.5f, 0.5f));
	this->addChild(m_pPowerAtlas);
}

void NTMiniMap::roadScrollEffect()
{
	
	m_pMiniRoad = CCSprite::create("game/mini_road.png");
	m_pMiniRoad->setPosition(ccp(400, 62));
	CCClippingNode* pClipingNode = CCClippingNode::create();
	pClipingNode->addChild(m_pMiniRoad);
	this->addChild(pClipingNode);
	CCSprite* pStencil = CCSprite::create("game/mini_road.png");
	pStencil->setPosition(ccp(400, 62));
	pStencil->setScaleX(0.955f);
	pClipingNode->setStencil(pStencil);

	for(unsigned int i=0; i<6; i++){
		m_pRoadLine[i] = CCSprite::create("game/road_line.png");
		m_pRoadLine[i]->setPosition(ccp(41+84*i, 20));
		m_pMiniRoad->addChild(m_pRoadLine[i]);
	}

	schedule(schedule_selector(NTMiniMap::updateForRoadLine));
}

bool NTMiniMap::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (!m_bIsTouchMu)
	{
		m_bIsTouchMu = m_pMenu->ccTouchBegan(pTouch,pEvent);
	}

	return true;
}

void NTMiniMap::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchMoved(pTouch,pEvent);
	}
}

void NTMiniMap::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchEnded(pTouch,pEvent);
		m_bIsTouchMu = false;
	}
}

void NTMiniMap::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bIsTouchMu)
	{
		m_pMenu->ccTouchCancelled(pTouch,pEvent);
		m_bIsTouchMu = false;
	}
}

void NTMiniMap::updatePlayerPos( CCPoint pPos )
{
	float pRealPosX = (pPos.x/m_fScreenScale)+m_pScreenStartPos.x;
	m_pPlayerHead->setPositionX(pRealPosX);
}

void NTMiniMap::updateNpcPos( CCPoint pPos )
{
	float pRealPosX = (pPos.x/m_fScreenScale)+m_pScreenStartPos.x;
	m_pNPCHead->setPositionX(pRealPosX);
}

void NTMiniMap::updateForRoadLine( float dt )
{
	float fMoveGap = -2.8f;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	for(unsigned int i=0; i<6; i++){
		//“∆∂Ø
		m_pRoadLine[i]->setPositionX(m_pRoadLine[i]->getPositionX()+fMoveGap);

		// «∑ÒµΩ¥Ô÷’µ„
		float pGap = m_pRoadLine[i]->getPositionX()+m_pRoadLine[i]->getContentSize().width/2;
		if(pGap<=0){
			//÷√ªÿ
			m_pRoadLine[i]->setPosition(
				ccpAdd(
				ccp(m_pMiniRoad->getContentSize().width+m_pRoadLine[i]->getContentSize().width/2, m_pRoadLine[i]->getPositionY()), 
				ccp(pGap, 0)));
		}
	}
}

void NTMiniMap::updatePowerBar( float fPercentAdd )
{
	//POWER_ADD
	m_fPowerPercent += fPercentAdd;
	if(m_fPowerPercent<0){
		m_fPowerPercent=0;
	}else if(m_fPowerPercent>100){
		m_fPowerPercent = 100;
	}

	m_pPowerBar->setPercentage(m_fPowerPercent);
	m_pPowerAtlas->setString(CCString::createWithFormat("%d:", (int)m_fPowerPercent)->getCString());
}

float NTMiniMap::getPercentOfPowerBar()
{
	return m_fPowerPercent;
}










