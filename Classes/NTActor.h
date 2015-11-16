
/********************************************************************
 *    �ļ���  :    NTENEMY.H
 *    ����    :    http://www.cnblogs.com/andyque/archive/2011/07/06/2099548.html
 *    ����ʱ��:    2013/7/2 16:58
 *    �ļ�����:    �о�
 *********************************************************************/

#ifndef _H_NTACTOR_H_
#define _H_NTACTOR_H_

#include "cocos2d.h"
#include "NTMapLayer.h"
#include "CocoStudio/Armature/CCArmature.h"
#include "NTConstants.h"

USING_NS_CC_EXT;
USING_NS_CC;


enum{
	ACTOR_ACTION_ROTATE = 9,
	ACTOR_ACTION_CHANGE_LAND_SPEED,
	ACTOR_ACTION_HUGE_BLINK,
	ACTOR_ACTION_FLYING,
	ACTOR_ACTION_WITH_MOUNT
};

enum{
	COLLIDE_TYPE_NOTHING = 2,		//ʲô��ûײ��
	COLLIDE_TYPE_LAND_NOTHING,		//ˮƽ������ʲôҲû��ײ��
	COLLIDE_TYPE_GIFT,				//ײ�����������Ʒ
	COLLIDE_TYPE_BASE_BLOCK,		//ײ�����ϰ�
	COLLIDE_TYPE_HOOK_BLOCK,		//ײ���������ϰ�
	COLLIDE_TYPE_LOWER_ROAD,		//ײ���˵ͼ���·
	COLLIDE_TYPE_SAME_HIGH_ROAD,	//ײ����ƽ����·
	COLLIDE_TYPE_HIGHER_ROAD,		//ײ���˸߼���·
	COLLIDE_TYPE_SPRING				//ײ���˵���
};

enum{
	PRE_COLLIDE_TYPE_LAND,
	PRE_COLLIDE_TYPE_JUMP
};

enum{
	STATE_JUMP,		//��Ծ
	STATE_RUN,		//�ܲ�
	STATE_RUN_FAST,	//���ܲ�
	STATE_FLY,		//����
	STATE_SLIDE,	//�»�
	STATE_HANG,		//����
	STATE_DEATH		//����
};

enum{
	ACTOR_CONTENTSIZE_TYPE_NORMAL,
	ACTOR_CONTENTSIZE_TYPE_SLIDE,
	ACTOR_CONTENTSIZE_TYPE_HUGE,
	ACTOR_CONTENTSIZE_TYPE_BEAR,
	ACTOR_CONTENTSIZE_TYPE_HORSE
};

class NTActor : public CCSprite{
public:
	//������ɫ����������
	static NTActor* createActor(int iType);
	static NTActor* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame, int iType);
	static const char* getTypeName(int iType);
	static const char* getArmatureName(int iType);
public:
	bool landCollide;
	bool verticalCollide;
private:
	void initChildSprite();
	void update(float dt);
	void updateCollide(float dt);
	void updateGravityEffect(float dt);
	void animationEvent(cocos2d::extension::CCArmature *armature, cocos2d::extension::MovementEventType movementType, const char *movementID);
public:
	void collideWithRoad(NTBox* pBox);
	bool collideWithGift(NTBox* pBox);

	void autoPlay();
	int isCanGetSomething(CCPoint pPos, float fSpeed, int iType=PRE_COLLIDE_TYPE_JUMP);

	bool m_bIsDoAutoPlay;
	void doAutoPlay(int iState);
	void doAUtoPlayCallBack();

public:
	CCPoint getLeftPos();
	CCPoint getRightPos();
	CCPoint getUpPos();
	CCPoint getBottomPos();
public:
	void landSpeedChange(float fValue);
	void setPosition(const CCPoint& pos);
public:
	CC_SYNTHESIZE(CCArmature*, m_pArmature, Armature);
	/*CC_SYNTHESIZE(CCSprite*, m_pSprite, Sprite);*/
	CC_SYNTHESIZE(int, m_iType, Type);
	CC_SYNTHESIZE(bool, m_bIsOnLand, IsOnLand);
	CC_SYNTHESIZE(bool, m_bIsOnBlock, IsOnBlock);
	CC_SYNTHESIZE(float, m_fSpeed, Speed);
	CC_SYNTHESIZE(float, m_fActorGravity, ActorGravity);
	CC_SYNTHESIZE(bool, m_bIsFlying, IsFlying);
	CC_SYNTHESIZE(bool, m_bIsHuge, IsHuge);
	CC_SYNTHESIZE(bool, m_bIsAutoCoin, IsAutoCoin);
	CC_SYNTHESIZE(int, m_iStandHighLevel, StandHighLevel);
	CC_SYNTHESIZE(bool, m_bIsAutoPlay, IsAutoPlay);
	CC_SYNTHESIZE(float, m_iMaxLeftPosX, MaxLeftPosX);
	CC_SYNTHESIZE(int, m_iMaxJumpTimes, MaxJumpTimes);
	CC_SYNTHESIZE(int, m_iBaseJumpHigh, BaseJumpHigh);
	CC_SYNTHESIZE(float, m_fLandSpeedChangeValue, LandSpeedChangeValue);
	CC_SYNTHESIZE(bool, m_bIsIgnoreGravity, IsIgnoreGravity);
	CC_SYNTHESIZE(int, m_iEquipType, EquipType);
	CC_SYNTHESIZE(NTActor*, m_pEnemy, Enemy);
	CC_SYNTHESIZE(int, m_iScore, Score);
	CC_SYNTHESIZE(bool, m_iCanOutOfLeftScreen, CanOutOfLeftScreen);
	CC_SYNTHESIZE(int, m_iHp, Hp);
	CC_SYNTHESIZE(int, m_ilandCollideType, LandCollideType);
	CC_SYNTHESIZE(bool, m_bIsWithDefense, IsWithDefense);
     CC_SYNTHESIZE(bool, m_brelife, Life);
  


protected:
	CC_SYNTHESIZE(NTMapLayer*, m_pMapLayer, MapLayer);
public:
	CC_SYNTHESIZE(int, m_iState, ActorState);
	void updateState(int iState, bool bForce=false);
public:
	int m_iCurrentJumpTimes;
	void jump(float fSpeed=0);
	void jumpCallBack();
	void slide();
	void slideOver();
	void death();

	void changeContentSize(int iType);

	void fly(float dt, bool bIsForce=false);
	void flyCallBack();

	void huge(float dt);
	void hugeCallBack();

	void autoCoin(float dt);
	void autoCoinGet(NTBox* pBox);
	void autoCoinCallBack();

	void updateHp(int iValue);

private:
	void draw();
	void useEquip();
	CCSprite* m_pEffectSprite;
	void showEffectCallBack();

	CCSprite* m_pDefenseSprite;
	void showDefense();
	void updateDefense();
	void hideDefense();
private:	
	void changeMount(cocos2d::extension::CCArmature *armature);
	void playAnimateByIndex(int index);
	void playAnimateByName(const char* animateName);
	CC_SYNTHESIZE(cocos2d::extension::CCArmature*, m_pMount, Mount);
	void changeMountCallBack();
};

#endif // _H_NTACTOR_H_
