/****************************************************************************
 Copyright (c) 2010-2013 cocos2d-x.org
 Copyright (c) Microsoft Open Technologies, Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "AppDelegate.h"

#include <vector>
#include <string>

#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "CocoStudio/Reader/SceneReader.h"
#include "NTGameSave.h"
#include "SimpleAudioEngine.h"
#include "NTGameSound.h"
USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    
    
    
    pDirector->setOpenGLView(pEGLView);
    CCSize frameSize = pEGLView->getFrameSize();
    CCSize designResolutionSize = cocos2d::CCSizeMake(800, 480);
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionExactFit);
    // turn on display FPS
    pDirector->setDisplayStats(false);
    
    srand((unsigned)time( NULL ));
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bg.plist");
    // 	CCScene * newscene  = CCScene::create();
    // 	CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("FishJoy2.json");
    // 	newscene->addChild(pNode);
    
    
    NTGameSave::sharedGameSave()->setIsGameOpen(true);
    // create a scene. it's an autorelease object
    // run
    CCScene* pScene = HelloWorld::scene();
    pDirector->runWithScene(pScene);
    
    // 	CCLabelTTF *label = CCLabelTTF::create("TRAIL-GAME", "Arial", 48);
    // 	label->setOpacity(100);
    // 	label->setPosition(ccp(400, 150));
    // 	label->setColor(ccc3(255, 0, 0));
    // 	pScene->addChild(label, 99999);
    // 	CCLabelTTF *label1 = CCLabelTTF::create("QQ:3773590", "Arial", 48);
    // 	label1->setOpacity(100);
    // 	label1->setColor(ccc3(255, 0, 0));
    // 	label1->setPosition(ccp(400, 100));
    // 	pScene->addChild(label1, 99999);
    
    // 	CocosGUIExamplesWeaponScene *pScene = new CocosGUIExamplesWeaponScene();
    // 	pScene->autorelease();
    //
    // 	// run
    // 	pDirector->runWithScene(pScene
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    NTGameSound::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    NTGameSound::sharedEngine()->resumeBackgroundMusic();
}
