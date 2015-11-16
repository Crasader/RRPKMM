#ifndef __H_NTMAPLAYER_H__
#define __H_NTMAPLAYER_H__

#include "cocos2d.h"
#include "NTAutoScrollLayer.h"
#include "NTRoad.h"
#include "NTEffectLayer.h"

USING_NS_CC;

enum{
	MAP_ACTION_EXTRASPEED = 9,
};

#define BASE_SPEED 500  //400
#define ADD_SPEED 0.02f  //0.01f
#define UP_SPEED 800	//600

class NTEffectLayer;

class NTMapLayer : public cocos2d::CCLayer
{
public:
	~NTMapLayer();
    CREATE_FUNC(NTMapLayer);
public:
	void extraSpeed(float dt, int iAdd=400);
	void extraSpeedCallBack();

	void showSuperMode();
	void showSuperModeCallBack();


	void backToNormalRoad();

	//’π æΩø‚
	void showGoldArea();
	void showGoldAreaCallBack();
	void addGoldRoad();
	void fromGoldAreaBackToNormalRoad();

	//÷ÿ÷√leftLine
	void resetLeftLine();

	//“˝µº≤ø∑÷
	void showGuideRoad();

	void reset();

	CC_SYNTHESIZE(bool, m_bIsMapStop, IsMapStop);
	CC_SYNTHESIZE(float, m_fSpeed, Speed);
	CC_SYNTHESIZE(CCSpriteBatchNode*, m_pBoxBatchNode, BoxBatchNode);

	void addProps(int iType, CCPoint pPos);

	//’∂Ø∆¡ƒª
private:
	bool m_bIsShake;
	void resetShake();
public:
	void shake(float dt);
	float m_fLength;
	CC_SYNTHESIZE(int, m_iMapLevel, MapLevel);
public:
	void showSpecialHit(CCPoint pPos);


private:
	void showLightPre(CCPoint pPos);
	void showLightPreCallBack(CCNode* pSender);
private:
	void updateMapLevel();
private:
	bool init();  
	void update(float dt);
	
	float m_fLeftLine;

	float m_fGoldAreaLine1;
	float m_fGoldAreaLine2;
	float m_fGoldAreaLine3;

	NTAutoScrollLayer* m_pAutoBg[8];
	CCSprite* m_pSkyBg;
	CCSprite* m_pSuperModeLight;
public:
	CC_SYNTHESIZE(bool, m_bSuperMode, SuperMode);
	CC_SYNTHESIZE(float, m_fSpeedExtra, SpeedExtra);
	CC_SYNTHESIZE(float, m_fSpeedOrginal, SpeedOrginal);
private:
	void initValues();
	void createBaseMap();

	void createMapForSupperMode();

	NTBox* createBoxWithType(int pType);
	NTRoad* createRoad();

	//Ω±“∂—…˙≥…
	bool createBoxInRect(CCPoint pStartPos, CCPoint pEndPos, bool bForce=false);
	void createBoxCrowd(CCPoint pStartPos, int iType);
	int getRandomBuffInBoxCrowd();
	void addGameCoinInSin(CCPoint pos, float sinMAX, float length, float fSinOffx=0, bool bWithBuff=true);

	//¬∑…œµƒ‘™Àÿ…˙≥…
	void createBoxOnRoad(NTRoad* pRoad);

	//’œ∞≠ŒÔ…˙≥…
	//ø’œ∂…œµƒ’œ∞≠ŒÔ
	void createBlockOnAir(CCPoint pPos);
	//µ¿¬∑…œµƒ’œ∞≠ŒÔ
	void createBlockOnRoad(NTRoad* pRoad);

	void removeSelfCallBack(CCNode* pSender);

private:
	CC_SYNTHESIZE(CCArray*, m_pBoxArray, BoxArray);
	CC_SYNTHESIZE(CCArray*, m_pBoxFreeArray, BoxFreeArray);
	int iCurrentRoadHigh;
	int iCurrentBlank;
protected:
	CC_SYNTHESIZE(NTEffectLayer*, m_pEffectLayer, EffectLayer);
	void showEffect(CCPoint pPos, int iType);
};

#endif // __H_NTMAPLAYER_H__
