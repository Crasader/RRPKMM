#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "NTHero.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    void dataLoaded(float percent);
    
    void loadjsonFile();
	void MuXinWangLuoCallback();
    CC_SYNTHESIZE(NTHero*, m_pNTHero, NTHero);
    void showWords();
    cocos2d::CCLabelTTF *m_pWorsText;
private:
    bool m_bIsLoadOver;
	CCSprite* m_pMuXinWangLuo;
    
};

#endif // __HELLOWORLD_SCENE_H__
