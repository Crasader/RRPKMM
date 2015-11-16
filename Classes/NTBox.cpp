#include "NTBox.h"
#include "NTConstants.h"
#include "AnimatePacker.h"
#include "NTMapLayer.h"

NTBox::NTBox()
{
	reset();
	m_fSpeedScale = 1.0f;
}

NTBox* NTBox::createBox( int iType)
{
	char pszSpriteFrameName[30];
	sprintf(pszSpriteFrameName, getTypeName(iType));

	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
	//CCAssert(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame, iType);
}

NTBox* NTBox::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame, int iType)
{
	NTBox *pobSprite = new NTBox();
	if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
	{
		pobSprite->initData(iType);
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}


void NTBox::initData( int iType )
{
	setType(iType);
	updatePervious();
	initEffect();
}

void NTBox::initEffect()
{
	//BUFF
	if(getType()>=BOX_BUFF_START&&getType()<=BOX_BUFF_END){
		CCSprite* pCircle = CCSprite::createWithSpriteFrameName("fireball_normal.png");
		pCircle->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
		addChild(pCircle);
	}
	//∑…––’œ∞≠
	else if(getType()==BOX_FLY_BLOCK){
// 		CCSprite* pCircle = CCSprite::createWithSpriteFrameName("eff_stufffly.png");
// 		pCircle->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
// 		pCircle->setAnchorPoint(ccp(0.25f, 0.5f));
// 		addChild(pCircle);
	}
}

const char* NTBox::getTypeName( int iType )
{
	switch(iType)
	{
		case BOX_GOLDAREA_PROP1:
			{
				return "jk_zyj_0.png";
			}break;
		case BOX_GOLDAREA_PROP2:
			{
				return "jk_zj_0.png";
			}break;
		case BOX_GOLDAREA_PROP3:
			{
				return "jk_zj_1.png";
			}break;
		case BOX_GOLDAREA_PROP4:
			{
				return "jk_zj_2.png";
			}break;
		case BOX_BALLOON1:
			{
				return "gd_qqiu_0.png";
			}break;
		case BOX_BALLOON2:
			{
				return "gd_qqiu_1.png";
			}break;
		case BOX_ROAD:
			{
				return "Stein.png";
			}break;
		case BOX_LIQUID:
			{
				return "game_dj_yao.png";
			}break;
		case BOX_BLOCK1:
			{
				return "za_xiang.png";
			}break;
		case BOX_BLOCK2:
			{
				return "za_shitou.png";
			}break;
		case BOX_BLOCK3:
			{
				return "za_yout.png";
			}break;
		case BOX_BLOCK4:
			{
				return "za_ni.png";
			}break;
		case BOX_FLY_BLOCK:
			{
// 				switch(((int)(CCRANDOM_0_1()*10))%4)
// 				{
// 					case 0:return "Plane22.png";
// 					case 1:return "sui_boli.png";
// 					case 2:return "sui_mu.png";
// 					case 3:return "sui_shitou.png";
// 				}
				return "Plane22.png";
			}break;
		case BOX_HOOK1:
			{
				return "za_diaol.png";
			}break;
		case BOX_HOOK2:
			{
				return "za_diaoc.png";
			}break;
		case BOX_HOOK3:
			{
				return "za_diaoy.png";
			}break;
		case BOX_COIN:
			{
				return "coin01_0000.png";
			}break;
		case BOX_SPRING:
			{
				return "block-bounce-stone03.png";
			}break;
		case BOX_ENGINE:
			{
				return "game_dj_ccy.png";
			}break;
		case BOX_MAGNET:
			{
				return "magnet-super.png";
			}break;
		case BOX_SUPER_COIN:
			{
				return "game_dj_ys.png";
			}break;
		case BOX_DEFENSE:
			{
				return "game_dj_dp.png";
			}break;
		case BOX_BANANA_SKIN:
			{
				return "block-spike-sky.png";
			}break;
		case BOX_BOMB:
			{
				return "ballchain48.png";
			}break;
		case BOX_MOUNT_HORSE:
			{
				return "mount.png";
			}break;
		case BOX_MOUNT_BEAR:
			{
				return "bear.png";
			}break;
		case BOX_BRICK:
			{
				return "za_zhuan.png";
			}break;
		case BOX_ICE_BOX:
			{
				return "za_boli.png";
			}break;
	}

	return NULL;
}

CCPoint NTBox::getLeftPos()
{
	return ccp(getPositionX()-getContentSize().width/2, getPositionY());
}

CCPoint NTBox::getRightPos()
{
	return ccp(getPositionX()+getContentSize().width/2, getPositionY());
}

CCPoint NTBox::getUpPos()
{
	return ccp(getPositionX(), getPositionY()+getContentSize().height/2);
}

CCPoint NTBox::geBottomPos()
{
	return ccp(getPositionX(), getPositionY()-getContentSize().height/2);
}

void NTBox::draw()
{
	CCNode::draw();
	ccDrawColor4B(255, 0, 0, 255);

	CCRect r = boundingBox();
	ccDrawRect(
		r.origin,
		ccp((r.getMaxX()-r.getMinX()), (r.getMaxY()-r.getMinY())));
}

void NTBox::changeToOthers( int iType )
{
	setType(iType);
	setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(getTypeName(iType)));
}

void NTBox::remove()
{
	m_bIsRemove=true;
	unschedule(schedule_selector(NTBox::updateForMoveToAim));
	stopAllActions();
}

void NTBox::reset()
{
	m_bIsRemove = false;
	m_bIsFlyToDie = false;
	m_bIsGiveCoin = false;
}

bool NTBox::shouldBeRecycle()
{
	if(getIsRemove() || getRightPos().x<=0){
		return true;
	}
	return false;
}

bool NTBox::shouldBeMoveWithMap()
{
	if(getIsFlyToDie()){
		return false;
	}
	return true;
}

void NTBox::flyToAim(CCNode* pAimNode)
{
	if(!getIsFlyToDie())
	{
		m_bIsFlyToDie = true;
		m_pAimNode = pAimNode;
		schedule(schedule_selector(NTBox::updateForMoveToAim));
	}
}

void NTBox::updateForMoveToAim( float dt )
{
	NTMapLayer* pMapLayer = getMapLayer();
	float pSpeed = dt*1000;
	CCPoint pBase = ccpNormalize(ccpSub(m_pAimNode->getPosition(), getPosition()));
	setPosition(ccpAdd(getPosition(), ccp(pBase.x*pSpeed, pBase.y*pSpeed)));
}

void NTBox::updatePervious()
{
	//¬∑£¨µØª…£¨’œ∞≠ŒÔ
	if(getType()==BOX_ROAD || getType()==BOX_ROAD_1 || getType()==BOX_ROAD_2 || getType()==BOX_ROAD_3
		 || getType()==BOX_SPRING || getType()==BOX_BLOCK1 || getType()==BOX_BLOCK2
		  || getType()==BOX_BLOCK3 || getType()==BOX_BLOCK4 || getType()==BOX_FLY_BLOCK || getType()==BOX_HOOK1
		 || getType()==BOX_HOOK2 || getType()==BOX_HOOK3 || getType()==BOX_BRICK || getType()==BOX_ICE_BOX )
	{
		m_bIsPervious = false;
	}
	else
	{
		m_bIsPervious = true;
	}
}

void NTBox::showCollideEffect()
{
	if(getType()==BOX_SPRING || getType()==BOX_BRICK){
		showLandEffect();
	}
	else{
		showBombEffect();
	}

}


void NTBox::showLandEffect( CCPoint pPos/*=CCPointZero*/ )
{
	switch(getType())
	{
		case BOX_SPRING:
			{
				this->runAction(AnimatePacker::getInstance()->getAnimate("jump"));
			}break;
		case BOX_BRICK:
			{
				int iLength = getPositionY()+getContentSize().height/2;
				this->runAction(CCMoveBy::create(iLength/40, ccp(0, -iLength)));
			}break;
	}
		
}

void NTBox::showBombEffect(CCPoint pPos)
{
    //Jerry--task-hitbox
    
    if ( getType()==BOX_BLOCK1 || getType()==BOX_BLOCK2
        || getType()==BOX_BLOCK3 || getType()==BOX_BLOCK4 ||  getType()==BOX_BRICK || getType()==BOX_ICE_BOX ) {
        if (NTGameSave::sharedGameSave()->getDataById(_GS_TASKTWO)==2){
            int hitbox;
            
            hitbox=NTGameSave::sharedGameSave()->getDataById(_GS_BOX_HIT)+1;
            CCLog("hitbox--%d",hitbox);
            NTGameSave::sharedGameSave()->updateValue(_GS_BOX_HIT,hitbox+1);
            if (hitbox>9) {
                NTGameSave::sharedGameSave()->updateValue(_GS_TASKTWO_FINISH,1);
            }
        }
    }
   
   
	switch(getType())
	{
	case BOX_BLOCK1:
		{
			m_pMapLayer->showEffect(getPosition(), EFFECT_WOOD_BOMB);
			this->remove();
		}break;
	case BOX_BLOCK2:
		{
			m_pMapLayer->showEffect(getPosition(), EFFECT_SMOKE);
			this->remove();
		}break;
	case BOX_BLOCK3:
		{
			m_pMapLayer->showEffect(getPosition(), EFFECT_SMOKE);
			this->remove();
		}break;
	case BOX_BLOCK4:
		{
			m_pMapLayer->showEffect(getPosition(), EFFECT_SMOKE);
			this->remove();
		}break;
	case BOX_SPRING:
		{
			m_pMapLayer->showEffect(getPosition(), EFFECT_SMOKE);
			this->remove();
		}break;
	case BOX_FLY_BLOCK:
		{
			m_pMapLayer->showEffect(getPosition(), EFFECT_SMOKE);
			this->remove();
		}break;
	case BOX_HOOK1:
		{
			m_pMapLayer->showEffect(ccpAdd(getPosition(), ccp(0, 80)), EFFECT_SMOKE);
			m_pMapLayer->showEffect(ccpAdd(getPosition(), ccp(0, 0)), EFFECT_SMOKE);
			m_pMapLayer->showEffect(ccpAdd(getPosition(), ccp(0, -80)), EFFECT_SMOKE);
			this->remove();
		}break;
	case BOX_HOOK2:
		{
			m_pMapLayer->showEffect(ccpAdd(getPosition(), ccp(0, 80)), EFFECT_SMOKE);
			m_pMapLayer->showEffect(ccpAdd(getPosition(), ccp(0, 0)), EFFECT_SMOKE);
			m_pMapLayer->showEffect(ccpAdd(getPosition(), ccp(0, -80)), EFFECT_SMOKE);
			this->remove();
		}break;
	case BOX_HOOK3:
		{
			m_pMapLayer->showEffect(ccpAdd(getPosition(), ccp(0, 80)), EFFECT_SMOKE);
			m_pMapLayer->showEffect(ccpAdd(getPosition(), ccp(0, 0)), EFFECT_SMOKE);
			m_pMapLayer->showEffect(ccpAdd(getPosition(), ccp(0, -80)), EFFECT_SMOKE);
			this->remove();
		}break;
	case BOX_COIN:
		{
			m_pMapLayer->showEffect(getPosition(), EFFECT_EAT_GOLD);
			this->remove();
		}break;
	case BOX_ICE_BOX:
		{
			m_pMapLayer->showEffect(getPosition(), EFFECT_GLASS_BOMB);
			this->remove();
		}break;
	case BOX_ENGINE:
		{
			m_pMapLayer->showEffect(getPosition(), EFFECT_BUFF_BOMB);
			this->remove();
		}break;
	case BOX_LIQUID:
		{
			m_pMapLayer->showEffect(getPosition(), EFFECT_BUFF_BOMB);
			this->remove();
		}break;
	case BOX_MAGNET:
		{
			m_pMapLayer->showEffect(getPosition(), EFFECT_BUFF_BOMB);
			this->remove();
		}break;
	case BOX_SUPER_COIN:
		{
			m_pMapLayer->showEffect(getPosition(), EFFECT_BUFF_BOMB);
			this->remove();
		}break;
	}
}

void NTBox::showSelfEffect(float dt)
{
	runAction(CCSequence::create(
		CCDelayTime::create(dt),
		CCCallFunc::create(this, callfunc_selector(NTBox::showSelfEffectCallBack)),NULL));
}

void NTBox::showSelfEffectCallBack()
{
	switch(getType())
	{
	case BOX_HOOK1:
		{
			this->runAction(CCRepeatForever::create(CCSequence::create(
				CCMoveBy::create(0.5f, ccp(0, 40)),
				CCMoveBy::create(0.5f, ccp(0, -40)),
				NULL)));
		}break;
	case BOX_HOOK2:
		{
			this->runAction(CCRepeatForever::create(CCSequence::create(
				CCMoveBy::create(0.5f, ccp(0, 40)),
				CCMoveBy::create(0.5f, ccp(0, -40)),
				NULL)));
		}break;
	case BOX_HOOK3:
		{
			this->runAction(CCRepeatForever::create(CCSequence::create(
				CCMoveBy::create(0.5f, ccp(0, 40)),
				CCMoveBy::create(0.5f, ccp(0, -40)),
				NULL)));
		}break;
	case BOX_BALLOON1:
		{
			this->runAction(CCRepeatForever::create(CCSequence::create(
				CCMoveBy::create(10.1f, ccp(0, 40)),
				CCMoveBy::create(10.1f, ccp(0, -40)),
				NULL)));
		}break;
	case BOX_BALLOON2:
		{
			this->runAction(CCRepeatForever::create(CCSequence::create(
				CCMoveBy::create(10.1f, ccp(0, 40)),
				CCMoveBy::create(10.1f, ccp(0, -40)),
				NULL)));
		}break;
	case BOX_FLY_BLOCK:
		{
			CCSprite* pLight = CCSprite::createWithSpriteFrameName("eff_stufffly.png");
			pLight->setAnchorPoint(ccp(0.2f, 0.5f));
			pLight->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
			addChild(pLight);
		}break;
	}
}

bool NTBox::isShouldInFreeArray()
{
	int iType = getType();
// 	if(iType>BOX_ROAD_3){
// 		return true;
// 	}
	if(iType==BOX_COIN){
		return true;
	}

	return false;
}

bool NTBox::isShouldInFreeArray( int iType )
{
	int myType = iType;
	if(myType==BOX_COIN){
		return true;
	}

	return false;
}








