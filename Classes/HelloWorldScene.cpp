
#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "NTMapLayer.h"
#include "CocoStudio/Armature/CCArmature.h"
#include "CocoStudio/Armature/animation/CCArmatureAnimation.h"
#include "CocoStudio/Armature/utils/CCArmatureDataManager.h"
#include "NTControlLayer.h"
#include "json.h"
#include "NTSharedJsonData.h"
#include "AnimatePacker.h"
#include "NTStart.h"
#include "NTGameSave.h"
#include "NTGameSound.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

USING_NS_CC;

USING_NS_CC_EXT;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    //Jerry--init
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    //getStaticMethodInfo
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/ibirdgame/archirun/PayWrapper","Cocos_initPay", "()V");
    
    if (!isHave) {
        CCLog("jni:NoHave");
    }else{
        CCLog("jni:Have");
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
    CCLog("jni-java");
#endif

    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	/*CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	m_pMuXinWangLuo = CCSprite::create("aiyouxi.png");
	m_pMuXinWangLuo->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	m_pMuXinWangLuo->setScale(1.35);
	this->addChild(m_pMuXinWangLuo, 2);
	CCFiniteTimeAction *actionF = CCCallFunc::create(this,
		callfunc_selector(HelloWorld::MuXinWangLuoCallback));
	CCFiniteTimeAction*  action = CCSequence::create(CCDelayTime::create(2.f), actionF, NULL);
	m_pMuXinWangLuo->runAction(action);*/

    
	m_pWorsText = CCLabelTTF::create("", "arial", 25);
	this->addChild(m_pWorsText);
	m_pWorsText->setPosition(ccp(400, 50));
	//º”‘ÿ «∑ÒΩ· ¯
	m_bIsLoadOver = false;


	AnimatePacker::getInstance()->loadAnimations("effect/effect_anima.xml");
	AnimatePacker::getInstance()->loadAnimations("box_anima.xml");

	// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/hero.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/horse.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/bear.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/boy.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/baby.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/girl.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/pet1.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/pet2.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/pet3.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	//Jerry--Aizou
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/aizou.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	/*setScale(0.5f);*/

    
    return true;
}

void HelloWorld::dataLoaded(float percent)
{
    if(m_bIsLoadOver){
        return;
    }
    
    if (percent >= 1)
    {
        m_bIsLoadOver = true;
        
        //µ⁄“ª¥ŒΩ¯»Î”Œœ∑
        if(NTGameSave::sharedGameSave()->getDataById(_GS_FIRST_IN_GAME)==0){
            NTGameSave::sharedGameSave()->updateValue(_GS_FIRST_IN_GAME, 1);
            
            //≥ı ºªØ”¢–€µ»º∂
            NTGameSave::sharedGameSave()->updateValue(_GS_HERO1_LEVEL, 1);
            NTGameSave::sharedGameSave()->updateValue(_GS_HERO2_LEVEL, 1);
            NTGameSave::sharedGameSave()->updateValue(_GS_HERO3_LEVEL, 1);
            //≥ı ºªØ≥ËŒÔµ»º∂
            NTGameSave::sharedGameSave()->updateValue(_GS_PET1_LEVEL, 1);
            NTGameSave::sharedGameSave()->updateValue(_GS_PET2_LEVEL, 1);
            NTGameSave::sharedGameSave()->updateValue(_GS_PET3_LEVEL, 1);
            //‘˘ÀÕµ⁄“ª∏ˆ”¢–€f
            NTGameSave::sharedGameSave()->updateBuyHero(_GS_HERO_IS_BUY_1, true);
            //—°‘Ò≥ËŒÔµƒ÷µ…Ë÷√Œ™-1
            NTGameSave::sharedGameSave()->updateHeroPet(-1);
            
            NTGameSave::sharedGameSave()->updateValue(_GS_HEART,5);
            //‘˘ÀÕ99999999Ω±“£¨≤‚ ‘”√
            NTGameSave::sharedGameSave()->updateValue(_GS_GOLD, 0);
            NTGameSave::sharedGameSave()->updateValue(_GS_FIRST_TASK, 0);
        }

		

		CCScene* pScene = NTStart::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
       
        
    }else{
        showWords();
    }
}

void HelloWorld::MuXinWangLuoCallback() // 木心网络界面回调函数
{
	if (m_pMuXinWangLuo)
	{
		m_pMuXinWangLuo->removeFromParent();

	}

	m_pWorsText = CCLabelTTF::create("", "arial", 25);
	this->addChild(m_pWorsText);
	m_pWorsText->setPosition(ccp(400, 50));
	//º”‘ÿ «∑ÒΩ· ¯
	m_bIsLoadOver = false;


	AnimatePacker::getInstance()->loadAnimations("effect/effect_anima.xml");
	AnimatePacker::getInstance()->loadAnimations("box_anima.xml");
	//º”‘ÿ◊ ‘¥
	// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/hero.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/horse.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	// 	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/bear.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/boy.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/baby.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/girl.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/pet1.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/pet2.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/pet3.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	//Jerry--Aizou
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("armature/aizou.ExportJson", this, schedule_selector(HelloWorld::dataLoaded));
	/*setScale(0.5f);*/


}
void HelloWorld::showWords()
{
    CSJson::Value pJsonLoad = NTSharedJsonData::sharedJsonData()->getJsonCn();
    int index = rand()%(pJsonLoad["loading"].size());
    std::string str ="Tips:"+pJsonLoad["loading"][index].asString();
    m_pWorsText->setString(str.c_str());
    m_pWorsText->setColor(ccYELLOW);
}
