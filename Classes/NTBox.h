
#ifndef _H_NTBOX_H_
#define _H_NTBOX_H_

#include "cocos2d.h"
/*#include "NTMapLayer.h"*/

USING_NS_CC;

class NTMapLayer;

class NTBox : public CCSprite{

public:
	NTBox();
	//创建盒子，传入类型
	static NTBox* createBox(int iType);
public:
	//左边缘的pos
	CCPoint getLeftPos();
	//左边缘的pos
	CCPoint getRightPos();
	//上边缘的pos
	CCPoint getUpPos();
	//下边缘的pos
	CCPoint geBottomPos();
public:
	//自身效果
	void showSelfEffect(float dt);
	void showSelfEffectCallBack();

	//碰撞效果
	void showCollideEffect();
	//踩踏效果
	void showLandEffect(CCPoint pPos=CCPointZero);
	//爆炸效果
	void showBombEffect(CCPoint pPos=CCPointZero);

	//变成其他类型的box
	void changeToOthers(int iType);
	//标记自己为去除状态
	void remove();
	//重置内部状态
	void reset();
	//是否应该被回收
	bool shouldBeRecycle();
	//是否应该有跟随地图移动的效果
	bool shouldBeMoveWithMap();
	//飞向目标
	void flyToAim(CCNode* pAimNode);
	//是否可穿越
	void updatePervious();
	//是否可以重复利用
	bool isShouldInFreeArray();
	static bool isShouldInFreeArray(int iType);
protected:
	CC_SYNTHESIZE(NTMapLayer*, m_pMapLayer, MapLayer);	//地图
	CC_SYNTHESIZE(CCNode*, m_pAimNode, AimNode);		//目标
	CC_SYNTHESIZE(int, m_iType, Type);					//类型
	CC_SYNTHESIZE(bool, m_bIsFlyToDie, IsFlyToDie);		//flyToDie状态
	CC_SYNTHESIZE(bool, m_bIsRemove, IsRemove);			//去除状态
	CC_SYNTHESIZE(bool, m_bIsPervious, IsPervious);		//是否可穿越
	CC_SYNTHESIZE(float, m_fSpeedScale, SpeedScale);	//相对道路的速度比例，默认是1
	CC_SYNTHESIZE(bool, m_bIsGiveCoin, IsGiveCoin);	//相对道路的速度比例，默认是1
//====================================================================================//
private:
	static NTBox* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame, int iType);
	static const char* getTypeName(int iType);
public:
	virtual void initData(int iType);
	void initEffect();
private:
	void updateForMoveToAim(float dt);
	void draw();
//====================================================================================//
};

#endif // _H_NTBOX_H_
