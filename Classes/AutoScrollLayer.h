//
//  AutoScrollLayer.h
//  BombExpert_box2d
//
//  Created by soul on 13-3-28.
//
//

#ifndef _AutoScrollLayer_
#define _AutoScrollLayer_

#include "cocos2d.h"

USING_NS_CC;

enum{
	DIR_LEFT = -1,
	DIR_RIGHT = 1
};

class AutoScrollLayer:public CCLayer{
public:
    
    AutoScrollLayer();
    ~AutoScrollLayer();
    
    bool init();
    void startScroll(int speed, int dir);
    static AutoScrollLayer *create(const char *fileName);
    virtual void onEnter();
    virtual void onExit();
    
    void update(float dt);
    void stop();
    void start();
    
public:
    std::string fileName;
    CC_SYNTHESIZE(float, m_fSpeed, Speed);
    CC_SYNTHESIZE(int, m_iDirection, Direction);
};

#endif /* _AutoScrollLayer_ */
