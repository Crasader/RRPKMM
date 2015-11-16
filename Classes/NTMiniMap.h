#ifndef _NTMINIMAP_H_
#define _NTMINIMAP_H_

#include "cocos2d.h"

USING_NS_CC;

class NTMiniMap:public CCLayer
{
public:
	CREATE_FUNC(NTMiniMap);
	void updatePlayerPos(CCPoint pPos);
	void updateNpcPos(CCPoint pPos);
	void updatePowerBar(float fPercentAdd);
	float getPercentOfPowerBar();

private:
	CCMenu* m_pMenu;
	bool m_bIsTouchMu;

private:
	bool init();
	void onEnter();
	void onExit();
	void onEnterTransitionDidFinish();

	//触摸事件
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	//初始化数据
	void initValues();
	//初始化UI
	void initUI();
	//道路滚动效果
	void roadScrollEffect();
	void updateForRoadLine(float dt);

private:
	//主角头像
	CC_SYNTHESIZE(CCSprite*, m_pPlayerHead, PlayerHead);
	//NPC头像
	CC_SYNTHESIZE(CCSprite*, m_pNPCHead, NPCHead);
private:
	//屏幕视野框
	CCSprite* m_pScreenRect;
	//mini道路条
	CCSprite* m_pMiniRoad;
	CCSprite* m_pRoadLine[6];
	//屏幕起点
	CCPoint m_pScreenStartPos;
	//缩放倍数
	float m_fScreenScale;

	//能量条
	CCProgressTimer* m_pPowerBar;
	CCLabelAtlas* m_pPowerAtlas;
	float m_fPowerPercent;
};

#endif /*_NTMINIMAP_H_*/