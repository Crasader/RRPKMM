#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include "cocos2d.h"
#include "NTControlLayer.h"
#include "menu_nodes/CCMenuItem.h"
USING_NS_CC;

class NTGameScene : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(NTGameScene);
	void onEnter();


};

#endif // __GAME_SCENE__
