#ifndef _H_NTLOADING_H_
#define _H_NTLOADING_H_

#include "cocos2d.h"

USING_NS_CC;

class NTLoadingLayer : public cocos2d::CCLayerColor {

public:

	CREATE_FUNC(NTLoadingLayer);

private:
	bool init();
	void onEnterTransitionDidFinish();
	void showLight(CCNode* pSender);
	void initForLoading();
	void updateForLoading(float dt);
	float m_iLoadSpeed;
public:
	void setSpeed(float pSpeed);
	float getSpeed();

private:
	CCProgressTimer* m_pProgress;
	void showToEndCallBack();
public:
	void showToEnd(CCFiniteTimeAction* pCallBack);
};

#endif // _H_NTLOADING_H_