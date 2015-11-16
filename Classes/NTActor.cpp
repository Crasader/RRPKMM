

#include "NTActor.h"
#include "NTRoad.h"
#include "NTConstants.h"
#include "AnimatePacker.h"
#include "NTGameSound.h"
#include "NTGameSave.h"
#include "NTControlLayer.h"


NTActor* NTActor::createActor( int iType)
{
	char pszSpriteFrameName[30];
	sprintf(pszSpriteFrameName, "game_dj_mb.png");

	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame, iType);
}

NTActor* NTActor::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame, int iType)
{
	NTActor *pobSprite = new NTActor();
	pobSprite->setType(iType);
	if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
	{
		pobSprite->initChildSprite();
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}


void NTActor::initChildSprite()
{
	m_bIsOnLand=false;
	m_bIsOnBlock=false;
	m_fSpeed = 0;

	m_iMaxJumpTimes = actor_data[getType()][ACTOR_DATA_JUMP_TIMES];
	m_iCurrentJumpTimes = 0;

	m_iBaseJumpHigh = actor_data[getType()][ACTOR_DATA_JUMP_HIGH];

	m_fActorGravity = GRAVITY_G;
	m_bIsFlying = false;
	m_bIsAutoCoin = false;
	m_bIsHuge = false;

	m_iStandHighLevel = 0;

	m_bIsAutoPlay = false;

	m_iMaxLeftPosX = ACTOR_BASE_MAX_LEFT_POSX;

	m_bIsDoAutoPlay = false;

	m_fLandSpeedChangeValue = 0;

	m_bIsIgnoreGravity = false;

	m_iEquipType = 0;

	m_pEnemy = NULL;

	m_pMount = NULL;
  
 m_iScore=0;

	m_ilandCollideType = COLLIDE_TYPE_BASE_BLOCK;

	m_iCanOutOfLeftScreen = actor_data[getType()][ACTOR_DATA_CAN_OUT_OF_LEFT_SCREEN]==1?true:false;

	m_iHp = actor_data[getType()][ACTOR_DATA_HP];

	m_bIsWithDefense = false;

	this->setOpacity(0);

	m_pArmature = CCArmature::create(getArmatureName(getType())/*"hero"*/);
	m_pArmature->getAnimation()->play("runfast");
	m_pArmature->setScale(actor_armture_data[getType()][ACTOR_ARMTURE_SCALE]);
	m_pArmature->setPosition(ccp(getContentSize().width/2, 0));
	m_pArmature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(NTActor::animationEvent));
	m_pArmature->getAnimation()->setSpeedScale(actor_armture_data[getType()][ACTOR_ARMTURE_ARMATURE_SCALE]);
	this->addChild(m_pArmature);

	//–ßπ˚æ´¡È
	m_pEffectSprite = CCSprite::createWithSpriteFrameName("eff_slide0.png");
	m_pEffectSprite->setVisible(false);
	this->addChild(m_pEffectSprite, m_pArmature->getZOrder()-1);

	//∑¿ª§’÷æ´¡È
	m_pDefenseSprite = CCSprite::createWithSpriteFrameName("eff_herogq.png");
	m_pDefenseSprite->setVisible(false);
	this->addChild(m_pDefenseSprite, m_pArmature->getZOrder()+1);

	updateState(STATE_JUMP);

	scheduleUpdate();
}

void NTActor::animationEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
	std::string id = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if (id.compare("fastrun") == 0)
		{

		}
	}
	else if(movementType == COMPLETE)
	{
		if (id.compare("fastrun") == 0)
		{

		}
	}
}

void NTActor::updateState( int iState, bool bForce)
{
	//m_iState Œ™…œ¥Œµƒ◊¥Ã¨
	if(m_iState==STATE_DEATH){
		return;
	}

	//»Áπ˚∏˙…œ“ª¥Œ◊¥Ã¨œ‡Õ¨
	if(m_iState==iState && !bForce){
		//»Áπ˚ «ø…“‘«ø÷∆À¢–¬µƒ∂Ø◊˜£¨¿˝»ÁÃ¯‘æ
		if(iState==STATE_JUMP){

		}
		//»Áπ˚≤ª÷ß≥÷«ø÷∆À¢–¬µƒ∂Ø◊˜£¨¿˝»Á≈‹≤Ω,∑…œË,œ¬ª¨
		else{
			return;
		}
	}
	
	//œ¬ª¨◊¥Ã¨≤ªƒ‹±ª≈‹≤Ω»°¥˙£¨≥˝∑«bforce
	if(getActorState()==STATE_SLIDE){
		if(iState==STATE_RUN_FAST && !bForce){
			return;
		}
	}

	//»Áπ˚ «∑…œË◊¥Ã¨÷ªƒ‹◊™Ã¯‘æ◊¥Ã¨
	if(getActorState()==STATE_FLY){
		if(iState!=STATE_JUMP){
			return;
		}
	}

	if(iState==STATE_SLIDE){
		changeContentSize(ACTOR_CONTENTSIZE_TYPE_SLIDE);
	}else{
		changeContentSize(ACTOR_CONTENTSIZE_TYPE_NORMAL);
	}

	setActorState(iState);

	updateDefense();

	switch(iState)
	{
	case STATE_JUMP:
		{
			m_pEffectSprite->stopAllActions();
			m_pEffectSprite->setVisible(true);
			m_pEffectSprite->setOpacity(0);
			m_pEffectSprite->setAnchorPoint(ccp(0.5f, 0.5f));
			m_pEffectSprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
			m_pEffectSprite->runAction(CCSequence::create(
				CCSpawn::createWithTwoActions(AnimatePacker::getInstance()->getAnimate("jump_effect"),
				CCFadeIn::create(0.05f)),
				CCCallFunc::create(this, callfunc_selector(NTActor::showEffectCallBack)),
				NULL));
			playAnimateByName("jump");
		}break;
	case STATE_RUN:
		{
			playAnimateByName("run");
		}break;
	case STATE_RUN_FAST:
		{
			playAnimateByName("runfast");
		}break;
	case STATE_FLY:
		{
			m_pEffectSprite->stopAllActions();
			m_pEffectSprite->setVisible(true);
			m_pEffectSprite->setOpacity(255);
			m_pEffectSprite->setAnchorPoint(ccp(0.8f, 0.4f));
			m_pEffectSprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
			m_pEffectSprite->runAction(CCRepeatForever::create(
				AnimatePacker::getInstance()->getAnimate("fly_effect")));
			playAnimateByName("fly");
		}break;
	case STATE_SLIDE:
		{
			m_pEffectSprite->stopAllActions();
			m_pEffectSprite->setVisible(true);
			m_pEffectSprite->setOpacity(255);
			m_pEffectSprite->setAnchorPoint(ccp(0.72f, 0.2f));
			m_pEffectSprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
			m_pEffectSprite->runAction(CCRepeatForever::create(
				AnimatePacker::getInstance()->getAnimate("slide_effect")));
			playAnimateByName("slide");
		}break;
	case STATE_HANG:
		{
			/*playAnimateByName("hang");*/
		}break;
	case STATE_DEATH:
		{
			/*setVisible(false);*/
			unscheduleAllSelectors();
		}break;
	}
}


const char* NTActor::getTypeName( int iType )
{
	switch(iType)
	{
		case ACTOR_1:
			{
				return "game_dj_mb.png";
			}break;
		case ACTOR_2:
			{
				return "game_dj_mb.png";
			}break;
		case ACTOR_3:
			{
				return "game_dj_mb.png";
			}break;
	}

	return NULL;
}

const char* NTActor::getArmatureName( int iType )
{
	switch(iType)
	{
	case ACTOR_1:
		{
			return "boy";
		}break;
	case ACTOR_2:
		{
			return "baby";
		}break;
	case ACTOR_3:
		{
			return "girl";
		}break;
	}

	return NULL;
}



CCPoint NTActor::getLeftPos()
{
	return ccp(getPositionX()+getContentSize().width/2, getPositionY());
	return ccp(0,0);
}

CCPoint NTActor::getRightPos()
{
	return ccp(getPositionX()-getContentSize().width/2, getPositionY());
	return ccp(0,0);
}

CCPoint NTActor::getUpPos()
{
	return ccp(getPositionX(), getPositionY()+getContentSize().height/2);
	//return ccp(0,0);
}

CCPoint NTActor::getBottomPos()
{
	return ccp(getPositionX(), getPositionY()-getContentSize().height/2);
	//return ccp(0,0);
}

void NTActor::setPosition( const CCPoint& pos )
{
	CCSprite::setPosition(pos);
}

//∏ƒ±‰Œ™Ã¯‘æ◊¥Ã¨
void NTActor::jump(float fSpeed/*=0*/ )
{
	if(getIsFlying()){
		return;
	}

	if(m_fSpeed==0 || m_iCurrentJumpTimes<m_iMaxJumpTimes){

		if(fSpeed==0){
			m_fSpeed = m_iBaseJumpHigh-m_iCurrentJumpTimes*50;
			m_iCurrentJumpTimes++;
		}else{
			m_fSpeed = fSpeed;
			m_iCurrentJumpTimes=0;
		}
		
		setIsOnLand(false);
		updateState(STATE_JUMP);
	}
	
}

void NTActor::jumpCallBack()
{
	/*setActorState(STATE_RUN);*/
}
//∏ƒ±‰Œ™œ¬ª¨◊¥Ã¨
void NTActor::slide()
{
	//∑…––◊¥Ã¨≤ªƒ‹ª¨∂Ø
	if(getIsFlying()){
		return;
	}
	updateState(STATE_SLIDE);
}

//∏ƒ±‰Œ™øÏÀŸ±º≈‹◊¥Ã¨
void NTActor::slideOver()
{
	updateState(STATE_RUN_FAST, true);
	showEffectCallBack();
}

//À¿Õˆ(∏ƒ±‰Ω«…´◊¥Ã¨)
void NTActor::death()
{
	updateState(STATE_DEATH);
}

void NTActor::update( float dt )
{
	m_iScore+=1;

	updateGravityEffect(dt);
	updateCollide(dt);
	autoPlay();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCRect r2 = boundingBox();
	if(r2.getMaxX()<=0 || r2.getMinX()>=winSize.width)
	{
		setIsIgnoreGravity(true);
		setPositionY(420);
		if(getPositionX()<-100){
			setPositionX(-100);
		}else if(getPositionX()>winSize.width+100){
			setPositionX(winSize.width+100);
		}
	}else{
		setIsIgnoreGravity(false);
	}
	
	//≥¨≥ˆ◊Û±ﬂ∆¡ƒª£¨≥¨≥ˆœ¬±ﬂ∆¡ƒª
	if(r2.getMaxX()<=0&&!m_iCanOutOfLeftScreen || r2.getMaxY()<=0){
		updateHp(-actor_data[getType()][ACTOR_DATA_HP]);
	}
	
	//»Áπ˚…˙√¸÷µŒ™0
	if(m_iHp==0){
		updateState(STATE_DEATH);
	}

}

void NTActor::updateGravityEffect( float dt )
{
	//»Áπ˚’‚“ª÷°µƒ ±º‰π˝æ√£¨Œ™∑¿÷πΩ«…´≥ˆœ÷À≤“∆œ÷œÛ£¨∫ˆ¬‘µÙ∏√÷°µƒ÷ÿ¡¶–ßπ˚
	if(dt>=0.03f){
// 		CCLOG("^^^^^^^^^^^%d", getMapLayer()->getBoxBatchNode()->getChildrenCount());
// 		CCLOG("^^^^^^^^%d", getMapLayer()->getBoxArray()->count());
// 		CCLOG("^^^^^%d", getMapLayer()->getBoxFreeArray()->count());
// 		CCLOG("^^%f", dt);
		return;
	}

	if(getIsIgnoreGravity()){
		return;
	}

	//ªπ√ª”–¬‰µÿ, ‹µΩ÷ÿ¡¶–ßπ˚
	if(!getIsOnLand()){
		
		CCPoint pReal = getPosition();
		float fOffY = 0;

		
		fOffY = m_fSpeed*dt-0.5f*m_fActorGravity*dt*dt;
		
		m_fSpeed -= m_fActorGravity*dt;

		pReal = ccpAdd(pReal, ccp(0, fOffY));
		setPosition(pReal);
	}
	//¬‰µÿ¡À
	else
	{
		m_fSpeed=0;
		m_iCurrentJumpTimes=0;
		updateState(STATE_RUN_FAST);
	}
}


void NTActor::updateCollide(float dt)
{
	CCPoint pReal = getPosition();
	landCollide=false;
	verticalCollide=false;

	//∏˙Œﬁ∑®¥©‘ΩµƒŒÔÃÂΩ¯––≈ˆ◊≤ºÏ≤‚, æÕΩ¸ªπ‘≠≤ªΩª≤Êµƒ◊¥Ã¨
	CCArray* pBoxArray = getMapLayer()->getBoxArray();
	CCObject* pObj;
	CCARRAY_FOREACH(pBoxArray, pObj){
		NTBox* pBox = (NTBox*)pObj;
		CCRect pBoxRect = pBox->boundingBox();
		CCRect pThisRect = boundingBox();

		//¥≈Ã˙Œ¸Ω±“
		autoCoinGet(pBox);

		//”–ΩªºØ£¨¡ŸΩÁ◊¥Ã¨ªÚ’ﬂ«∂»Î◊¥Ã¨
		if(pBoxRect.intersectsRect(pThisRect)){

			//»Áπ˚≈ˆµΩµƒ «œ˚∫ƒ∆∑
			if(collideWithGift(pBox)){
				continue;
			}

			//∑…œË◊¥Ã¨≤ª±ª≈ˆ◊≤◊Ë»˚
			if(getIsFlying()){
				continue;
			}

			//»Áπ˚ «ø…¥©‘Ωµƒ
			if(pBox->getIsPervious()){
				continue;
			}

			bool bIsForceVertical = false;
			int interRectX = ((this->getContentSize().width/2+pBox->getContentSize().width/2)
				-fabs(pReal.x-pBox->getPositionX()))*(pReal.x>pBox->getPositionX()?1:-1);
			int interRectY = ((this->getContentSize().height/2+pBox->getContentSize().height/2)
				-fabs(pReal.y-pBox->getPositionY()))*(pReal.y>pBox->getPositionY()?1:-1);

			if(abs(interRectX)<abs(interRectY) && !landCollide){				

				//¡ŸΩÁ◊¥Ã¨
				if(interRectX==-1){
					landCollide=true;
				}
				//«∂»Î◊¥Ã¨
				else{

					//»Áπ˚ « ˙÷±œÚœ¬µƒÀŸ∂», ≤ª «π≥◊”£¨≤ª «¬∑
					if(getSpeed()<0 && 
						!(pBox->getType()<=BOX_ROAD&&pBox->getType()<=BOX_ROAD_3) && 
						!(pBox->getType()<=BOX_HOOK1&&pBox->getType()<=BOX_HOOK3)){
						bIsForceVertical = true;
					}else{
						pReal.x += interRectX;
						if(interRectX<0){
							pReal.x+=1;
							landCollide=true;
							landSpeedChange(-400);
							getMapLayer()->extraSpeed(0.3f, -100);
							getMapLayer()->shake(0.1f);

							//»Áπ˚ «’œ∞≠ŒÔ£¨‘Úø€“ªµ„—™
							if(pBox->getType()>=BOX_BLOCK1 && pBox->getType()<=BOX_BLOCK4){
								//»Áπ˚”–∑¿ª§’÷
								if(!m_bIsWithDefense){
									updateHp(-1);
								}else{
									hideDefense();
								}
								
							}
						}
					}
				}

			}


			// ˙÷±≥Â◊≤
			if(abs(interRectX)>abs(interRectY) || bIsForceVertical){

				// ˙÷±∑ΩœÚ…œªπ√ª”–≈ˆ◊≤
				if(!verticalCollide){

					//=============================================»Áπ˚◊≤µΩ‘⁄¬∑…œ
					if(pBox->getType()>=BOX_ROAD && pBox->getType()<=BOX_ROAD_3){

	// 					//»Áπ˚ «¡ŸΩÁ◊¥Ã¨
	// 					if(abs(interRectY)<=4 && m_fSpeed==0){
	// 						verticalCollide=true;
	// 						continue;
	// 					}

						//œ¬Ωµ ±≤≈ ’µΩ≥Â◊≤
						if(m_fSpeed<=0){
							//œ˚≥˝«∂»Î◊¥Ã¨
							pReal.y += interRectY;

							NTRoad* pRoad = (NTRoad*)pBox;
							//Ω¯»Î¡ŸΩÁ◊¥Ã¨
							pReal.y += interRectY<0?1:-1;
							verticalCollide=true;
							m_iStandHighLevel = pRoad->getHight();
							//”Î¬∑∑¢…˙≈ˆ◊≤£¨‘ÚÀŸ∂»ºıŒ™0
							m_fSpeed=0;

							pRoad->standEffect(getMapLayer()->getSpeed());
						}
					}
					//============================================»Áπ˚ «◊≤µΩ∆‰À˚ŒÔ∆∑…œ
					else{

						pBox->showCollideEffect();
						//œ˚≥˝«∂»Î◊¥Ã¨
						pReal.y += interRectY;	

						 if(pBox->getType()==BOX_SPRING){
							 //œ¬Ωµ ±≤≈ ’µΩ≥Â◊≤
							 if(m_fSpeed<=0){
								 m_fSpeed=0;
								 jump(m_iBaseJumpHigh*1.3f);
								 /*getMapLayer()->extraSpeed(1.0f, getMapLayer()->getSpeed()/2);*/
							 }
						 }else{
							 //œ¬Ωµ ±≤≈ ’µΩ≥Â◊≤
							 if(m_fSpeed<=0){
								 m_fSpeed=0;
								 jump(m_iBaseJumpHigh*0.8f);
							 }
						 }
					}
				}
			}
		}

		//»Áπ˚¡Ω±ﬂµƒ≈ˆ◊≤∂º”–£¨Ã¯≥ˆ
		if(verticalCollide && landCollide){
			break;
		}
	}

	setIsOnLand(verticalCollide);
	setIsOnBlock(landCollide);

	float fOffX = 0;
	float fOffY = 0;
	float fMoveGap = getMapLayer()->getSpeed()*dt;
	//±ª◊Ë»˚¡À
	if(getIsOnBlock()){
		fOffX = -fMoveGap;
	}else
	{
		if(getPositionX()<getMaxLeftPosX())
		{
			fOffX = fMoveGap/4;
		}
		else if(getPositionX()-getMaxLeftPosX()>10)
		{
			fOffX = -fMoveGap/4;
		}
	}

	pReal = ccpAdd(pReal, ccp(fOffX, fOffY));
	setPosition(pReal);
}


void NTActor::collideWithRoad(NTBox* pBox)
{
	if(pBox->getType()==BOX_ROAD_1){

	}
}

bool NTActor::collideWithGift(NTBox* pBox)
{
	//∑÷ ˝‘ˆº”
	if(pBox->getType()>=BOX_ROAD){
		if(!pBox->getIsGiveCoin()){
			pBox->setIsGiveCoin(true);
			m_iScore+=box_count_coin[pBox->getType()];
			pBox->getIsGiveCoin();
			NTGameSound::sharedEngine()->playEffectById(SOUND_GAME_LOSE,true,NTGameSave::sharedGameSave()->isSound);
		}
	}
	
	//»Áπ˚ «æﬁ»À◊¥Ã¨, ªÚ «∑…––◊¥Ã¨
	if(getIsHuge() || getIsFlying()){
		if(pBox->getType()>BOX_ROAD_3){
			pBox->showBombEffect();
			pBox->remove();
			return true;
		}
	}

	if(pBox->getType()==BOX_COIN){
		pBox->showBombEffect();
		pBox->remove();
		return true;
	}

	if(pBox->getType()==BOX_ENGINE){
		pBox->showBombEffect();
		pBox->remove();
		landSpeedChange(400);
		fly(4.0f);
		getMapLayer()->extraSpeed(4.0f);

		return true;
	}

	if(pBox->getType()==BOX_LIQUID){
		pBox->showBombEffect();
		pBox->remove();
		huge(5.0f);
		return true;
	}

	if(pBox->getType()==BOX_MAGNET){
		pBox->showBombEffect();
		pBox->remove();
		autoCoin(4.0f);
		return true;
	}

	if(pBox->getType()==BOX_SUPER_COIN){
		pBox->showBombEffect();
		pBox->remove();
		/*getMapLayer()->showSuperMode();*/
		return true;
	}

	if(pBox->getType()==BOX_DEFENSE){
		pBox->remove();
		showDefense();
		return true;
	}

	if(pBox->getType()==BOX_BANANA_SKIN){
		pBox->remove();
		setLandSpeedChangeValue(-400);
		return true;
	}

	if(pBox->getType()==BOX_MOUNT_HORSE){
		pBox->remove();
		changeMount(CCArmature::create("horse"));
		return true;
	}

	if(pBox->getType()==BOX_MOUNT_BEAR){
		pBox->remove();
		changeMount(CCArmature::create("bear"));
		return true;
	}

	if(pBox->getType()==BOX_FLY_BLOCK){
		pBox->showBombEffect();
		pBox->remove();
		//»Áπ˚√ª”–∑¿ª§’÷
		if(!m_bIsWithDefense){
			updateHp(-1);
		}else{
			hideDefense();
		}
		return true;
	}

	return false;
}

void NTActor::draw()
{
	CCSprite::draw();
	ccDrawColor4B(255, 0, 0, 255);

// 	CCRect r = boundingBox();
// 	ccDrawRect(
// 		ccp(0, 0),
// 		ccp((r.getMaxX()-r.getMinX()), (r.getMaxY()-r.getMinY())));
}

void NTActor::fly(float dt, bool bIsForce)
{
	if(getIsFlying() && !bIsForce){
		return;
	}
	stopActionByTag(ACTOR_ACTION_FLYING);

	m_fActorGravity = 0;
	m_fSpeed = 0;
	m_bIsFlying = true;
	/*setPositionY(getPositionY()+200>420?420:getPositionY()+200);*/

	float fPosY = 300;
	CCSequence* seq = CCSequence::create(
		CCMoveTo::create(0.5f, ccp(getPositionX(), fPosY)),
		CCDelayTime::create(dt),
		CCCallFunc::create(this, callfunc_selector(NTActor::flyCallBack)),
		NULL);
	seq->setTag(ACTOR_ACTION_FLYING);
	this->runAction(seq);
	
	updateState(STATE_FLY);
}

void NTActor::flyCallBack()
{
	m_fActorGravity = GRAVITY_G;
	m_bIsFlying = false;
	jump(m_iBaseJumpHigh/2);
}

void NTActor::huge( float dt )
{
	if(getIsHuge()){
		return;
	}
	m_bIsHuge = true;
	m_pArmature->setScale(actor_armture_data[getType()][ACTOR_ARMTURE_SCALE]*1.5f);
	changeContentSize(ACTOR_CONTENTSIZE_TYPE_HUGE);
	/*setScale(2.0f);*/
	
	CCRepeatForever* pRepeat = CCRepeatForever::create(CCSequence::create(
		CCTintTo::create(0.2f, 200, 100, 100),
		CCTintTo::create(0.2f, 255, 255, 255),
		NULL));
	pRepeat->setTag(ACTOR_ACTION_HUGE_BLINK);
	m_pArmature->runAction(pRepeat);
	this->runAction(CCSequence::create(
		CCDelayTime::create(dt),
		CCCallFunc::create(this, callfunc_selector(NTActor::hugeCallBack)),
		NULL));
}

void NTActor::hugeCallBack()
{
	m_bIsHuge = false;
	/*setScale(1.0f);*/
	m_pArmature->stopActionByTag(ACTOR_ACTION_HUGE_BLINK);
	m_pArmature->setColor(ccc3(255, 255, 255));
	m_pArmature->setScale(actor_armture_data[getType()][ACTOR_ARMTURE_SCALE]);
	changeContentSize(ACTOR_CONTENTSIZE_TYPE_NORMAL);
	updateDefense();
}


void NTActor::autoCoin( float dt )
{
	m_bIsAutoCoin = true;
	this->runAction(CCSequence::create(
		CCDelayTime::create(dt),
		CCCallFunc::create(this, callfunc_selector(NTActor::autoCoinCallBack)),
		NULL));
}

void NTActor::autoCoinGet( NTBox* pBox )
{
	if(getIsAutoCoin() || getIsFlying()){
		if(pBox->getType()==BOX_COIN){
			if(!pBox->getIsRemove())
			{
				if(ccpDistance(pBox->getPosition(), getPosition())<400){
					pBox->flyToAim(this);
				}
			}
		}
	}
}

void NTActor::autoCoinCallBack()
{
	m_bIsAutoCoin = false;
}

//vt-1/2*g*t*t = -y≥…¡¢ ±µΩ¥Ô∆¡ƒªœ¬±ﬂΩÁ
void NTActor::autoPlay()
{
	if(!getIsAutoPlay()){
		return;
	}

	// Õ∑≈µ¿æﬂ
	useEquip();

	if(m_bIsDoAutoPlay){
		return;
	}

	bool bIsShouldJump = false;
	bool bIsShouldSlide = false;
	bool bIsShouldRun = false;

	//¬‰µÿ¡ÀªÚ’ﬂ ‹◊Ë»˚¡À
	if(getIsOnLand() || getIsOnBlock()){

		float fBaseT = 0.016f;
		float fSpeed = 1000;
		float fTime = (sqrt(fSpeed*fSpeed+2*m_fActorGravity*getPositionY())+fSpeed)/(m_fActorGravity);
		float fTimeGap = fTime/10;

		bool bLandNothing = false;
		bool bGetSomething = false;
		bool bLand = false;
		bool bLowPosY = false;
		bool bSamePosY = false;
		bool bUpPosY = false;
		bool bIsBlock = false;
		bool bIsOnSpring = false;

		CCPoint pCurrentPos = getPosition();
		for(unsigned int i=0; i<10; i++){
			float fTimeCurrent = (i+1)*fTimeGap;
			float fSpeedCurrent = m_fSpeed-m_fActorGravity*fTimeCurrent;
			float x = getMapLayer()->getSpeed()*fTimeCurrent+getPositionX();
			float y = fSpeed*fTimeCurrent-0.5f*m_fActorGravity*fTimeCurrent*fTimeCurrent+getPositionY();

			int iCollideType = COLLIDE_TYPE_NOTHING;

			//ÀÆ∆Ω∑ΩœÚ≥÷–¯‘À∂Øµƒ∫Ûπ˚
			if(i<3){

				// ‘◊≈’æ∆¿¥µƒ∫Ûπ˚
				//¥¶”⁄œ¬ª¨◊¥Ã¨
				if(getActorState()==STATE_SLIDE){
					//…Ë÷√≈ˆ◊≤«¯”ÚŒ™’˝≥£’æ¡¢
					changeContentSize(ACTOR_CONTENTSIZE_TYPE_NORMAL);
				}

// 				getMapLayer()->removeChildByTag(878+i);
// 				CCSprite* pSprite = CCSprite::createWithSpriteFrameName("starblue_0000.png");
// 				pSprite->setPosition(ccp(x, getPositionY()));
// 				pSprite->setColor(ccc3(255, 0, 0));
// 				getMapLayer()->addChild(pSprite, 878+i, 878+i);

				CCPoint pPos = ccp(x, getPositionY());

				setPosition(pPos);
				iCollideType= isCanGetSomething(pPos, 111, PRE_COLLIDE_TYPE_LAND);
				setPosition(pCurrentPos);

				//¥¶”⁄œ¬ª¨◊¥Ã¨
				if(getActorState()==STATE_SLIDE){
					//…Ë÷√≈ˆ◊≤«¯”ÚŒ™œ¬ª¨
					changeContentSize(ACTOR_CONTENTSIZE_TYPE_SLIDE);
				}

				if(iCollideType==COLLIDE_TYPE_BASE_BLOCK && !getIsHuge()){
					bIsShouldJump = true;
					break;
				}else if(iCollideType==COLLIDE_TYPE_HOOK_BLOCK && !getIsHuge()){
					bIsShouldSlide = true;
					break;
				}
				else if(iCollideType==COLLIDE_TYPE_LAND_NOTHING)
				{
					bLandNothing = true;
				}

				//¥¶”⁄œ¬ª¨◊¥Ã¨
				if(getActorState()==STATE_SLIDE){
					if(i==2)
					{
						bIsShouldRun = true;
						break;
					}else
					{
						continue;
					}
				}
				
			}


			//Ã¯‘æ‘À∂Øµƒ∫Ûπ˚
			CCPoint pPos = ccp(x, y);
			setPosition(pPos);
			iCollideType= isCanGetSomething(pPos, fSpeedCurrent);
			setPosition(pCurrentPos);
			switch(iCollideType)
			{
			case COLLIDE_TYPE_GIFT:bGetSomething=true;break;
			case COLLIDE_TYPE_LOWER_ROAD:bLand=true;bLowPosY=true;break;
			case COLLIDE_TYPE_SAME_HIGH_ROAD:bLand=true;bSamePosY=true;break;
			case COLLIDE_TYPE_HIGHER_ROAD:bLand=true;bUpPosY=true;break;
			case COLLIDE_TYPE_BASE_BLOCK:bIsBlock=true;break;
			case COLLIDE_TYPE_SPRING:bIsOnSpring=true;break;
			}

			if(bIsBlock){
				break;
			}

			if(bUpPosY || (bGetSomething && bLand) || bIsOnSpring || (bLandNothing&&(bSamePosY||bUpPosY||bLowPosY))){
				bIsShouldJump = true;
				break;
			}
		}


		//”¶∏√œ¬ª¨
		if(bIsShouldSlide){
			doAutoPlay(STATE_SLIDE);
			return;
		}

		//”¶∏√’æ∆¿¥≈‹
		if(bIsShouldRun){
			doAutoPlay(STATE_RUN_FAST);
			return;
		}

		//”¶∏√Ã¯‘æ
		if(bIsShouldJump){
			doAutoPlay(STATE_JUMP);
			return;
		}

		//±ª◊Ë»˚¡À
		if(getIsOnBlock()){
			bIsShouldJump = true;
			doAutoPlay(STATE_JUMP);
			return;
		}
	}
}

int NTActor::isCanGetSomething( CCPoint pPos, float fSpeed, int iType)
{

	CCPoint pReal = pPos;
	bool bCollideNothing = true;

	//∏˙Œﬁ∑®¥©‘ΩµƒŒÔÃÂΩ¯––≈ˆ◊≤ºÏ≤‚, æÕΩ¸ªπ‘≠≤ªΩª≤Êµƒ◊¥Ã¨
	CCArray* pBoxArray = getMapLayer()->getBoxArray();
	CCObject* pObj;
	CCARRAY_FOREACH(pBoxArray, pObj){
		NTBox* pBox = (NTBox*)pObj;
		CCRect pBoxRect = pBox->boundingBox();
		CCRect pThisRect = boundingBox();

		//”–ΩªºØ,”≈œ»∂„±‹’œ∞≠£¨‘Ÿøº¬«≥‘giftµƒ«Èøˆ
		if(pBoxRect.intersectsRect(pThisRect)){

			bCollideNothing = false;

			//∆’Õ®’œ£¨ œ„Ω∂∆§etc
			if(pBox->getType()==BOX_BANANA_SKIN || pBox->getType()==BOX_FLY_BLOCK 
				|| pBox->getType()==BOX_BRICK || pBox->getType()==BOX_ICE_BOX 
				|| pBox->getType()==BOX_BLOCK1 || pBox->getType()==BOX_BLOCK2
				|| pBox->getType()==BOX_BLOCK3 || pBox->getType()==BOX_BLOCK4/* && iType==PRE_COLLIDE_TYPE_LAND && fSpeed==111*/){
				return COLLIDE_TYPE_BASE_BLOCK;
			}

			//–¸π“’œ∞≠, π≥◊”etc
			if(pBox->getType()>=BOX_HOOK1 && pBox->getType()<=BOX_HOOK3/* && iType==PRE_COLLIDE_TYPE_LAND && fSpeed==111*/){
				return COLLIDE_TYPE_HOOK_BLOCK;
			}

			//Ω±“
			//∂Ø¡¶“˝«Ê
			//¥≈Ã˙
			//≥¨º∂Ω±“
			//»Áπ˚≈ˆµΩµƒ «¿Ò∆∑
			if(pBox->getType()==BOX_COIN || 
				pBox->getType()==BOX_ENGINE || 
				pBox->getType()==BOX_MAGNET ||
				pBox->getType()==BOX_SUPER_COIN)
			{
				return COLLIDE_TYPE_GIFT;
			}


			//»Áπ˚ «ø…¥©‘Ωµƒ
			if(pBox->getIsPervious()){
				continue;
			}

			//»Áπ˚ «±ª’œ∞≠ŒÔ◊Ë»˚
			float interRectX = ((this->getContentSize().width/2+pBox->getContentSize().width/2)
				-fabs(pReal.x-pBox->getPositionX()))*(pReal.x>pBox->getPositionX()?1:-1);
			float interRectY = ((this->getContentSize().height/2+pBox->getContentSize().height/2)
				-fabs(pReal.y-pBox->getPositionY()))*(pReal.y>pBox->getPositionY()?1:-1);

// 			//ÀÆ∆Ω≥Â◊≤
// 			if(fabs(interRectX)<fabs(interRectY)){
// 
// 				if(interRectX<0){
// 					CCSprite* pSprite = CCSprite::createWithSpriteFrameName("starblue_0000.png");
// 					pSprite->setPosition(pBox->convertToNodeSpace(pReal));
// 					pSprite->setColor(ccc3(255, 0, 0));
// 					pBox->addChild(pSprite);
// 					return COLLIDE_TYPE_BLOCK;
// 				}
// 			}

			// ˙÷±≥Â◊≤
			if(fabs(interRectX)>fabs(interRectY)){

				//◊›œÚ≥Â◊≤µΩ£®…œ…˝Ω◊∂Œ≤ª≈ˆ◊≤£©
				if(fSpeed<=0){

					//»Áπ˚ «¬‰‘⁄µØª……œ
					if(pBox->getType()==BOX_SPRING)
					{
						return COLLIDE_TYPE_SPRING;
					}

					//»Áπ˚ «¬‰‘⁄µÿ√Ê…œ
					if(pBox->getType()>=BOX_ROAD && pBox->getType()<=BOX_ROAD_3){
						NTRoad* pRoad = (NTRoad*)pBox;

						if(pRoad->getHight()>getStandHighLevel())
						{
							return COLLIDE_TYPE_HIGHER_ROAD;
						}else if(pRoad->getHight()==getStandHighLevel()){
							return COLLIDE_TYPE_SAME_HIGH_ROAD;
						}else{
							return COLLIDE_TYPE_LOWER_ROAD;
						}
				}
			}
		}
		
		}
	}


	if(iType==PRE_COLLIDE_TYPE_LAND && bCollideNothing){
		return COLLIDE_TYPE_LAND_NOTHING;
	}
	return COLLIDE_TYPE_NOTHING;

}

void NTActor::doAutoPlay(int iState)
{
// 	m_bIsDoAutoPlay=true;
// 	this->runAction(
// // 		CCSequence::createWithTwoActions(
// // 		CCDelayTime::create(0.01f),
// // 		CCCallFunc::create(this, callfunc_selector(NTActor::doAUtoPlayCallBack)))
// 		CCCallFunc::create(this, callfunc_selector(NTActor::doAUtoPlayCallBack))
// 		);

	m_bIsDoAutoPlay = false;
	switch(iState)
	{
	case STATE_JUMP:
		{
			jump(m_iBaseJumpHigh);
		}break;
	case STATE_SLIDE:
		{
			slide();
		}break;
	case STATE_RUN_FAST:
		{
			slideOver();
		}break;
	}

}

void NTActor::doAUtoPlayCallBack()
{
// 	m_bIsDoAutoPlay = false;
// 	jump(m_iBaseJumpHigh);
}

void NTActor::landSpeedChange( float fValue )
{
	m_fLandSpeedChangeValue = fValue;
}

void NTActor::useEquip()
{
	//0.5f%∏≈¬  Õ∑≈µ¿æﬂ
	if(CCRANDOM_0_1()<0.01f){
		switch(m_iEquipType)
		{
		case BOX_BANANA_SKIN:getMapLayer()->addProps(
								 BOX_BANANA_SKIN, ccp(getEnemy()->getPositionX()+250, getEnemy()->getPositionY()));
			m_iEquipType = 0;
			break;
		}
	}
}


void NTActor::changeMount(CCArmature *armature)
{
	if (armature == NULL)
	{
		m_pArmature->retain();

		playAnimateByIndex(0);
		//Remove hero from display list
		m_pMount->getBone("hero")->removeDisplay(0);
		m_pMount->stopAllActions();

		//Set position to current position
		m_pArmature->setPosition(m_pMount->getPosition());
		//Add to layer
		addChild(m_pArmature);

		m_pArmature->release();

		m_pMount->removeFromParentAndCleanup(true);

		setMount(armature);
	}
	else
	{
		if(getMount()!=NULL){
			stopActionByTag(ACTOR_ACTION_WITH_MOUNT);
			changeMount(NULL);
		}

		setMount(armature);

		m_pArmature->retain();
		//Remove from layer
		m_pArmature->removeFromParentAndCleanup(false);

		//Get the hero bone
		CCBone *bone = armature->getBone("hero");
		//Add hero as a display to this bone
		bone->addDisplay(m_pArmature, 0);
		//Change this bone's display
		bone->changeDisplayByIndex(0, true);
		bone->setIgnoreMovementBoneData(true);
		armature->setPosition(ccp(m_pArmature->getPositionX(), 0));
		addChild(armature);
		//Change animation
		playAnimateByIndex(1);
		m_pArmature->setPosition(ccp(0, 0));
		m_pArmature->release();
		
		CCSequence* seq = CCSequence::createWithTwoActions(
			CCDelayTime::create(3.0f), 
			CCCallFunc::create(this, callfunc_selector(NTActor::changeMountCallBack)));
		seq->setTag(ACTOR_ACTION_WITH_MOUNT);
		runAction(seq);
	}

}

void NTActor::playAnimateByIndex(int index)
{
	m_pArmature->getAnimation()->playByIndex(index);
	if (m_pMount)
	{
		m_pMount->getAnimation()->playByIndex(index);
	}
}

void NTActor::playAnimateByName(const char* animateName)
{
	m_pArmature->getAnimation()->play(animateName);
	if (m_pMount)
	{
		m_pMount->getAnimation()->play(animateName);
	}
}

void NTActor::changeMountCallBack()
{
	changeMount(NULL);
}

void NTActor::changeContentSize( int iType )
{
	if(iType==ACTOR_CONTENTSIZE_TYPE_SLIDE)
	{
		float width=m_pArmature->getContentSize().width*m_pArmature->getScaleX()*actor_armture_data[getType()][ACTOR_ARMTURE_CONTENSIZE_SCALEX];
		float heigt=m_pArmature->getContentSize().height*m_pArmature->getScaleY()*actor_armture_data[getType()][ACTOR_ARMTURE_CONTENSIZE_SCALEY];
		this->setContentSize(CCSizeMake(width,heigt/2));
	}
	else if(iType==ACTOR_CONTENTSIZE_TYPE_NORMAL)
	{
		float width=m_pArmature->getContentSize().width*m_pArmature->getScaleX()*actor_armture_data[getType()][ACTOR_ARMTURE_CONTENSIZE_SCALEX];
		float heigt=m_pArmature->getContentSize().height*m_pArmature->getScaleY()*actor_armture_data[getType()][ACTOR_ARMTURE_CONTENSIZE_SCALEY];
		this->setContentSize(CCSizeMake(width,heigt));
	}else if(iType==ACTOR_CONTENTSIZE_TYPE_HUGE)
	{
		float width=m_pArmature->getContentSize().width*m_pArmature->getScaleX()*actor_armture_data[getType()][ACTOR_ARMTURE_CONTENSIZE_SCALEX];
		float heigt=m_pArmature->getContentSize().height*m_pArmature->getScaleY()*actor_armture_data[getType()][ACTOR_ARMTURE_CONTENSIZE_SCALEY];
		this->setContentSize(CCSizeMake(width, heigt));
	}
	
}

void NTActor::updateHp( int iValue )
{
	m_iHp += iValue;
	if(m_iHp<0){
		m_iHp=0;
	}else if(m_iHp>actor_data[getType()][ACTOR_DATA_HP]){
		m_iHp=actor_data[getType()][ACTOR_DATA_HP];
	}
}

void NTActor::showEffectCallBack()
{
	m_pEffectSprite->stopAllActions();
	m_pEffectSprite->setVisible(false);
}

void NTActor::showDefense()
{
	m_bIsWithDefense = true;
	m_pDefenseSprite->setVisible(true);
	updateDefense();
}

void NTActor::hideDefense()
{
	m_bIsWithDefense = false;
	m_pDefenseSprite->setVisible(false);
}

void NTActor::updateDefense()
{
	if(m_bIsWithDefense){
		if(getActorState()!=STATE_SLIDE){
			m_pDefenseSprite->setPosition(ccp(getContentSize().width*(0.5f+actor_defense_offx[getType()]), getContentSize().height/2));
			m_pDefenseSprite->setScale(getContentSize().height/m_pDefenseSprite->getContentSize().height+0.2f);
		}
		
		if(getIsFlying()){
			m_pDefenseSprite->setVisible(false);
		}else{
			m_pDefenseSprite->setVisible(true);
		}
	}
}
















