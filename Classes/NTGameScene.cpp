
#include "NTGameScene.h"
#include "NTMapLayer.h"
#include "NTControlLayer.h"
#include "NTMessageBox.h"
#include "NTGameSound.h"
//”Œœ∑÷˜ΩÁ√Ê
CCScene* NTGameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *pScene = CCScene::create();
    
    // 'layer' is an autorelease object
    NTGameScene *layer = NTGameScene::create();

    // add layer as a child to scene
    pScene->addChild(layer);

// 	CCLabelTTF *label = CCLabelTTF::create("TRAIL-GAME", "Arial", 48);		
// 	label->setOpacity(100);
// 	label->setPosition(ccp(400, 150));
// 	label->setColor(ccc3(255, 0, 0));
// 	pScene->addChild(label, 99999);
	/*CCLabelTTF *label1 = CCLabelTTF::create("QQ:3773590", "Arial", 48);		
	label1->setOpacity(100);
	label1->setColor(ccc3(255, 0, 0));
	label1->setPosition(ccp(400, 100));
	pScene->addChild(label1, 99999);*/


    // return the scene
    return pScene;
}

// on "init" you need to initialize your instance
bool NTGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    if(NTGameSave::sharedGameSave()->getDataById(_GS_TASKTHREE)==11){
        int heartuse;
        heartuse=NTGameSave::sharedGameSave()->getDataById(_GS_HEART_USE)+1;
        CCLog("updateheartuse%d",NTGameSave::sharedGameSave()->getDataById(_GS_HEART_USE));
        NTGameSave::sharedGameSave()->updateValue(_GS_HEART_USE,heartuse);
        if(heartuse>4)
          NTGameSave::sharedGameSave()->updateValue(_GS_TASKTHREE_FINISH,1);
    }
   
//Jerry--0.5
	//this->setScale(0.5f);
//	m_pControlLayer = NULL;		
	NTControlLayer* pControlLayer = NTControlLayer::create();
	this->addChild(pControlLayer);
	NTGameSound::sharedEngine()->openAll();
	NTGameHud* pGameHud = NTGameHud::create();
    //Jerry--KickBoss
    
	pGameHud->setControlLayer(pControlLayer);
	this->addChild(pGameHud);
	pControlLayer->setGameHud(pGameHud);
//	NTGameSound::sharedEngine()->playEffectById(SOUND_TOWER_UPGRADE,true,NTGameSave::sharedGameSave()->isSound);
    return true;
}

//º”‘ÿÕÍ≥…÷Æ∫Ûœ‘ æ”≈ª›¿Ò∞¸
void NTGameScene::onEnter()
{
	CCLayer::onEnter();

}

