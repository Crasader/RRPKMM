
#ifndef _H_NTGAMEGUIDE_H_
#define _H_NTGAMEGUIDE_H_

#include "cocos2d.h"
#include "NTControlLayer.h"
#include "NTMessageBox.h"

class NTTileData;
class NTGameHUD;
class NTWave;
class NTTower;
class NTEnemy;

USING_NS_CC;


enum{
	GUIDE_TYPE_TAP,			//点击
	GUIDE_TYPE_MOVE,		//移动
	GUIDE_TYPE_DRAW,		//划线
	GUIDE_TYPE_LONG_TAP,	//长按
};

#define GUIDE_ARROW_SHOW_DELAY	0.2f
#define GUIDE_ARROW_SHOW_GAP	0.15f

#define GAME_LAYER_GUIDE 1700

class NTGameGuide : public CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	CREATE_FUNC(NTGameGuide);
	~NTGameGuide();
	NTGameGuide();
	bool init();
	void onEnterTransitionDidFinish();
    void onExit();
	void onEnter();

	// default implements are used to call script callback if exist
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
public:
	CC_SYNTHESIZE(NTControlLayer*, m_pControlLayer, ControlLayer);
public:
	//触摸加锁
	CC_SYNTHESIZE(bool, m_bTouchLock, TouchLock)
private:
	//引导加锁
	CC_SYNTHESIZE(bool, m_bGuideLock, GuideLock);
	//触摸起始点
	CC_SYNTHESIZE(CCPoint, m_pStart, TouchStart);
	//触摸终点
	CC_SYNTHESIZE(CCPoint, m_pEnd, TouchEnd);
	//引导点
	CC_SYNTHESIZE(CCArray*, m_pPointArray, PointArray);
	CC_SYNTHESIZE(int, m_iPointIndex, PointIndex);
	//引导结束的回调
	CC_SYNTHESIZE(CCAction*, m_pGuideOverCallBack, GuideOverCallBack);
	//触摸执行的Layer
	CC_SYNTHESIZE(CCTouchDelegate*, m_pTouchLayer, TouchLayer);
	//执行时间
	CC_SYNTHESIZE(float, m_pDelayTime, DelayTime);
	//起始点和终点的gap
	CC_SYNTHESIZE(CCPoint, m_pGap, Gap);
	//引导类型
	CC_SYNTHESIZE(int, m_pGuideType, GuideType);
	//gap方向的增量point
	CC_SYNTHESIZE(CCPoint, m_pStartToAdd, StartToAdd);

	CC_SYNTHESIZE(int, m_iGuideMode, GuideMode);

	void initLightLayer();
	void initValue();

	//手和箭头
	CCSprite* m_pArrow;
	CCSprite* m_pHand;
	CCSprite* m_pBlinkLight;
	void showHandAndArrow(CCPoint pPos);
	void hideHandAndArrow();


	void showMsgBox(int pType=-1);
	void messageOkCallBack( CCObject * pSender);

	//执行引导 
	//pHud:执行触摸的实例
	//pStart:触摸起始点	
	//pEnd:触摸终点	
	//pDelayTime:持续时间
	//pActionCallBack:引导结束的回调
	//iGuideMode:引导的模式
	//pPointArray:一组点的数组
	bool runGuide(int pType, 
		CCTouchDelegate* pTouchLayer, 
		CCPoint pStart, CCPoint pEnd, 
		float pDelayTime, 
		CCAction* pActionCallBack,
		int iGuideMode, 
		CCArray* pPointArray=NULL);

	void showGuide();
	void showTapGuide();
	void showLongTapGuide();
	void showMoveGuide();
	void showDrawGuide();
	void showGuideCallBack();
	void showTapTouch();
	void showLongTapTouch();
	void showLongTapTouchCallBack();
	void showDragTouch();
	bool changePoint(CCPoint pStart=CCPointZero);
	void updateForTouchMove(float dt);
	
	CCSpriteBatchNode* m_pArrowBatchNode;
	void initArrayBatchNode();
	void showArrowWithArrayPoint(CCArray* pArray);
	void showArrowWithArrayPointCallBack();
	void moveHandWithArrayPoint(CCArray* pArray);
	void moveHandWithArrayPointCallBack();

private:
	// chenying 2013-12-24 触点模拟
	CCTouch* m_pVirtualTouch;
};
#endif // _H_NTGAMEGUIDE_H_
