#ifndef _ANIMATE_PACKER_H_
#define _ANIMATE_PACKER_H_

#include <string>
#include <map>
#include <vector>
#include <set>
#include "cocos2d.h"
#include "Singleton.h"

struct Animate {
    std::string name;
    float delay;
    bool flipX;
    bool flipY;
    std::vector<std::string> spriteFrames;
};

class AnimatePacker: public Singleton<AnimatePacker> {
public:
    void loadAnimations(const char *path);

    cocos2d::CCAnimate* getAnimate(const char *name);
};

#endif//_ANIMATE_PACKER_H_

