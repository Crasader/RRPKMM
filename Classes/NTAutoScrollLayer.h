
#ifndef _NTAutoScrollLayer_
#define _NTAutoScrollLayer_

#include "cocos2d.h"

USING_NS_CC;

enum{
	NT_DIR_LEFT = -1,
	NT_DIR_RIGHT = 1
};


class NTAutoScrollLayer:public CCLayer{

public:
	static NTAutoScrollLayer *create(const char *fileName, CCPoint pPos);
	void stop();
	void start();

	void showFadeIn();

private: 
	NTAutoScrollLayer();
    bool init();
    void startScroll(int speed, int dir);
   
    virtual void onEnter();
    virtual void onExit();
    
    void update(float dt);

	CCSprite* m_pShadow;
    
public:
	CC_SYNTHESIZE(std::string, m_pFileName, FileName);
    CC_SYNTHESIZE(float, m_fSpeed, Speed);
    CC_SYNTHESIZE(int, m_iDirection, MoveDirection);
	CC_SYNTHESIZE(CCPoint, m_pPicturePos, PicturePos);
	CC_SYNTHESIZE(CCPoint, m_pAimPos, AimPos);
	CC_SYNTHESIZE(CCPoint, m_pBackPos, BackPos);
};

#endif /* _NTAutoScrollLayer_ */
