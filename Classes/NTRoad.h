

#ifndef _H_NTROAD_H_
#define _H_NTROAD_H_

#include "cocos2d.h"
#include "NTBox.h"

USING_NS_CC;

enum{
	ROAD_ACTION_TAG_SHAKE,
	ROAD_ACTION_TAG_HIDE
};

class NTRoad : public NTBox{

public:
	static NTRoad* createRoad(int iType);
	static NTRoad* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame, int iType);
	//创建道路，传入类型，长度
	void initRoad(int iType, int iLength, int iHigh);
	void standEffect(float fSpeed);
public:
	CCPoint getLeftPos();
	CCPoint getRightPos();
	CCPoint getUpPos();
	CCPoint geBottomPos();
public:
	void shake(float fSpeed);
	void down(float fSpeed);
	void up(float fSpeed);
protected:
	CC_SYNTHESIZE(int, m_iLength, RoadLength);
	CC_SYNTHESIZE(int, m_iHigh, Hight);
	CC_SYNTHESIZE(int, m_iLengthLine, LengthLine);
	CC_SYNTHESIZE(int, m_iHightLine, HightLine);
	CC_SYNTHESIZE(bool, m_bIsCanStand, IsCanStand);
private:
	const char* getTypeName(int iType);
	int getBaseLayerCount();

	void initRoad();
};

#endif // _H_NTROAD_H_
