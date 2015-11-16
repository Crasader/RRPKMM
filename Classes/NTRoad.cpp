

#include "NTRoad.h"
#include "NTConstants.h"


NTRoad* NTRoad::createRoad( int iType)
{
	char pszSpriteFrameName[30];
	sprintf(pszSpriteFrameName, "TileMap_0_0.png");

	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame, iType);
}

NTRoad* NTRoad::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame, int iType)
{
	NTRoad *pobSprite = new NTRoad();
	pobSprite->initData(iType);
	if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}


const char* NTRoad::getTypeName( int iType )
{
	switch(iType)
	{
		case BOX_ROAD_1:
			{
				return "TileMap";
			}break;
		case BOX_ROAD_2:
			{
				return "TileMap_up";
			}break;
		case BOX_ROAD_3:
			{
				return "TileMap_gold";
			}break;
	}

	return NULL;
}


int NTRoad::getBaseLayerCount()
{
	switch(m_iHigh)
	{
	case ROAD_POSY_HIGH:
		{
			return 2;
		}break;
	case ROAD_POSY_MED:
		{
			return 1;
		}break;
	case ROAD_POSY_LOW:
		{
			return 0;
		}break;
	}

	return 2;
}

CCPoint NTRoad::getLeftPos()
{
	return ccp(getPositionX()-getContentSize().width/2, getPositionY());
}

CCPoint NTRoad::getRightPos()
{
	return ccp(getPositionX()+getContentSize().width/2, getPositionY());
}

CCPoint NTRoad::getUpPos()
{
	return ccp(getPositionX(), getPositionY()+getContentSize().height/2);
}

CCPoint NTRoad::geBottomPos()
{
	return ccp(getPositionX(), getPositionY()-getContentSize().height/2);
}

void NTRoad::standEffect(float fSpeed)
{
// 	if(!getIsCanStand()){
// 		down(fSpeed);
// 	}
}

void NTRoad::shake(float fSpeed)
{
	if(getActionByTag(ROAD_ACTION_TAG_SHAKE)==NULL){
		CCJumpBy* jb = CCJumpBy::create(0.3f, ccp(0, 0), fSpeed/200, 1);
		jb->setTag(ROAD_ACTION_TAG_SHAKE);
		runAction(jb);
	}
}


void NTRoad::down( float fSpeed )
{
	if(getActionByTag(ROAD_ACTION_TAG_HIDE)==NULL){
		CCMoveBy* mb = CCMoveBy::create(2000/fabs(fSpeed), ccp(0, -getContentSize().height-100));
		mb->setTag(ROAD_ACTION_TAG_HIDE);
		runAction(mb);
	}
}

void NTRoad::up( float fSpeed )
{
	if(getActionByTag(ROAD_ACTION_TAG_HIDE)==NULL){
		CCMoveBy* mb = CCMoveBy::create(2000/fabs(fSpeed), ccp(0, -getContentSize().height-100));
		mb->setTag(ROAD_ACTION_TAG_HIDE);
		runAction(mb);
	}
}



void NTRoad::initRoad( int iType, int iLength, int iHigh )
{
	setIsCanStand(true);
	scheduleUpdate();
	setOpacity(0);
	setType(iType);
	setRoadLength(iLength);
	setHight(iHigh);

	m_iHightLine = 0;

	//初始化路面
	initRoad();

	setContentSize(CCSizeMake(m_iLengthLine, m_iHightLine-15));
	setAnchorPoint(ccp(0.5, 0.5));

	m_iHightLine = road_posy[getHight()];
}

void NTRoad::initRoad()
{
	m_iLengthLine = 0;

	//a+b+b+b+c
	//生成a
	CCSprite* pSpriteA = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s_0_0.png", getTypeName(getType()))->getCString());
	pSpriteA->setAnchorPoint(ccp(0, 0));
	pSpriteA->setPosition(ccp(m_iLengthLine, m_iHightLine));
	this->addChild(pSpriteA);

	m_iLengthLine += pSpriteA->getContentSize().width;

	//生成b
	for(unsigned int j=0; j<m_iLength; j++){
		CCSprite* pSpriteB = CCSprite::createWithSpriteFrameName(
			CCString::createWithFormat("%s_0_%d.png", getTypeName(getType()), j%2+1)->getCString());
		pSpriteB->setAnchorPoint(ccp(0, 0));
		pSpriteB->setPosition(ccp(m_iLengthLine, m_iHightLine));
		this->addChild(pSpriteB);
		m_iLengthLine += pSpriteB->getContentSize().width;
	}

	//生成c
	CCSprite* pSpriteC = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("%s_0_3.png", getTypeName(getType()))->getCString());
	pSpriteC->setAnchorPoint(ccp(0, 0));
	pSpriteC->setPosition(ccp(m_iLengthLine, m_iHightLine));
	this->addChild(pSpriteC);
	m_iLengthLine += pSpriteA->getContentSize().width;


	m_iHightLine += pSpriteA->getContentSize().height;
}




