#include "NTTask.h"
#include "NTMenuItem.h"
#include "NTGameSave.h"

void NTTask::onEnter()
{
	NTCoverLayer::onEnter();
	initValue();
	initUI();
}
#define TASK_NUM 18
void NTTask::initValue()
{
    if (true){//(NTGameSave::sharedGameSave()->isTaskRefresh()||NTGameSave::sharedGameSave()->getDataById(_GS_FIRST_TASK)==0) {
        NTGameSave::sharedGameSave()->updateValue(_GS_GOLD,999999);
         NTGameSave::sharedGameSave()->updateValue(_GS_FIRST_TASK, 1);
        m_pTaskOne=rand()%(TASK_NUM-1)+1;
        CCLog("taskone%d",m_pTaskOne);
        m_pTaskTwo=rand()%(TASK_NUM-2)+1;
        CCLog("tasktwo%d",m_pTaskTwo);
        if(m_pTaskTwo==getTaskOne()) {
            m_pTaskTwo++;
        }
        
        m_pTaskThree=rand()%(TASK_NUM-3)+1;
        CCLog("taskthree%d",m_pTaskThree);
        if (m_pTaskThree==getTaskOne()) {
            if (m_pTaskThree==(getTaskTwo()-1)) {
                ((m_pTaskThree+2)>TASK_NUM)?(m_pTaskThree=m_pTaskThree+2-TASK_NUM):(m_pTaskThree=m_pTaskThree+2);
            }else  ((m_pTaskThree+1)>TASK_NUM)?(m_pTaskThree=m_pTaskThree+1-TASK_NUM ):(m_pTaskThree=m_pTaskThree+1);
        }else if(m_pTaskThree==getTaskTwo()){
            if (m_pTaskThree==(getTaskOne()-1)) {
                ((m_pTaskThree+2)>TASK_NUM)?(m_pTaskThree=m_pTaskThree+2-TASK_NUM):(m_pTaskThree=m_pTaskThree+2);
            }else  ((m_pTaskThree+1)>TASK_NUM)?(m_pTaskThree=m_pTaskThree+1-TASK_NUM ):(m_pTaskThree=m_pTaskThree+1);
        }
        NTGameSave::sharedGameSave()->updateValue(_GS_TASKONE, m_pTaskOne);
        NTGameSave::sharedGameSave()->updateValue(_GS_TASKTWO, m_pTaskTwo);
        NTGameSave::sharedGameSave()->updateValue(_GS_TASKTHREE, m_pTaskThree);
    }
    
}

void NTTask::initUI()
{
	//-------  ≤Àµ•
	CCMenu *pMenu = CCMenu::create();
	this->addChild(pMenu,2);
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	setMenu(pMenu);

	//-------  ±≥æ∞
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *pBg = CCSprite::create("task/renwu_db.png");
	this->addChild(pBg);
	pBg->setPosition(ccp(winSize.width/2,winSize.height/2));

	//-------  »ŒŒÒ√Ë ˆ
	CCSprite *pDesc = CCSprite::create("task/renwu_wz.png");
	pBg->addChild(pDesc);
	pDesc->setPosition(ccp(pBg->getContentSize().width/2,pBg->getContentSize().height-100));

	//-------  »ŒŒÒΩ¯∂»
	CCSprite *pProgressBg = CCSprite::create("task/renwu_jdtk.png");
	pBg->addChild(pProgressBg);
	pProgressBg->setPosition(ccp(163,170));
	//pProgressBg->setVisible(false);
	CCProgressTimer *pProgress = CCProgressTimer::create(CCSprite::create("task/renwu_jdt.png"));
	pBg->addChild(pProgress);
	pProgress->setType(kCCProgressTimerTypeBar);
	pProgress->setMidpoint(ccp(0, 0.5));
	pProgress->setBarChangeRate(ccp(1, 0));
	pProgress->setPercentage(50);
	pProgress->setPosition(pProgressBg->getPosition());

	int nSumDistance = 5000;
	int nFinshedDistance = 2500;
	CCLabelAtlas *pProgressText =  CCLabelAtlas::create(CCString::createWithFormat("%d/%d",nFinshedDistance,nSumDistance)->getCString(),"task/renwu_jdtnb.png",6,12,'0'-1);
	pBg->addChild(pProgressText);
	pProgressText->setPosition(ccp(146,165));
	//-------  »ŒŒÒΩ±¿¯
	CCSprite *pNumLogo = CCSprite::create("heart/bank_x.png");
	pBg->addChild(pNumLogo);
	pNumLogo->setPosition(ccp(130,127));
	CCLabelAtlas *pNumText = CCLabelAtlas::create(CCString::createWithFormat("/%d",3)->getCString(),"task/renwu_jlnb.png",13,21,'0'-1);
	pBg->addChild(pNumText);
	pNumText->setPosition(ccp(150,115));
	
	//-------  ¡Ï»°∞¥≈•
	NTMenuItemSprite *pFinishItem=NTMenuItemSprite::create(
								CCSprite::create("task/renwu_an.png"),
								CCSprite::create("task/renwu_an.png"),
								NULL,this,menu_selector(NTTask::menu_finish));
	pMenu->addChild(pFinishItem);
	pFinishItem->setPosition(ccp(404,135));
    //Jerry-Task
                CCLabelAtlas *task1 =CCLabelAtlas::create("01","start/start_jbsz.png",14,21,'0');
                task1->setPosition(ccp(200, 300));
                addChild(task1);
                 task1->setString(CCString::createWithFormat("%d",NTGameSave::sharedGameSave()->getDataById(_GS_TASKONE))->getCString());
    
                CCLabelAtlas *task2 =CCLabelAtlas::create("01","start/start_jbsz.png",14,21,'0');
                task2->setPosition(ccp(250, 300));
                addChild(task2);
                task2->setString(CCString::createWithFormat("%d",NTGameSave::sharedGameSave()->getDataById(_GS_TASKTWO))->getCString());
    
                CCLabelAtlas *task3 =CCLabelAtlas::create("01","start/start_jbsz.png",14,21,'0');
                task3->setPosition(ccp(300, 300));
                addChild(task3);
                task3->setString(CCString::createWithFormat("%d",NTGameSave::sharedGameSave()->getDataById(_GS_TASKTHREE))->getCString());
    
    CCLabelAtlas *task1_fisish =CCLabelAtlas::create("01","start/start_jbsz.png",14,21,'0');
    task1_fisish->setPosition(ccp(200, 250));
    addChild(task1_fisish);
    task1_fisish->setString(CCString::createWithFormat("%d",isTaskFinished(NTGameSave::sharedGameSave()->getDataById(_GS_TASKONE))?1:0)->getCString());

    CCLabelAtlas *task2_fisish =CCLabelAtlas::create("01","start/start_jbsz.png",14,21,'0');
    task2_fisish->setPosition(ccp(250, 250));
    addChild(task2_fisish);
    task2_fisish->setString(CCString::createWithFormat("%d",isTaskFinished(NTGameSave::sharedGameSave()->getDataById(_GS_TASKTWO))?1:0)->getCString());
    
    CCLabelAtlas *task3_fisish =CCLabelAtlas::create("01","start/start_jbsz.png",14,21,'0');
    task3_fisish->setPosition(ccp(300, 250));
    addChild(task3_fisish);
    task3_fisish->setString(CCString::createWithFormat("%d",isTaskFinished(NTGameSave::sharedGameSave()->getDataById(_GS_TASKTHREE))?1:0)->getCString());

	//-------  πÿ±’∞¥≈•
	addBackMenu("share_button/nn.png",ccp(510,381));


}

void NTTask::menu_finish( CCObject *pSender )
{

}
bool NTTask::isTaskFinished(int type)
{
//    if (type!=m_pTaskOne&&type!=m_pTaskTwo&&type!=m_pTaskThree) {
//        return false;
//    }
//    switch (type) {
//        case TASK_RUN_2000:
//            if (NTGameSave::sharedGameSave()->getDataById(_GS_DISTANCE)>1999) {
//                return true;
//            }else return false;
//            break;
//        case TASK_RUN_4000:
//            if (NTGameSave::sharedGameSave()->getDataById(_GS_DISTANCE)>3999) {
//                return true;
//            }else return false;
//            break;
//        case TASK_RUN_5000:
//            if (NTGameSave::sharedGameSave()->getDataById(_GS_DISTANCE)>4999) {
//                return true;
//            }else return false;
//            break;
//        case TASK_RUN_8000:
//            if (NTGameSave::sharedGameSave()->getDataById(_GS_DISTANCE)>7999) {
//                return true;
//            }else return false;
//            break;
//        case TASK_GOLDMODE_5:
//            return NTGameSave::sharedGameSave()->getDataById(_GS_GOLDMODE_TIMES)>4;
//            break;
//        case TASK_GOLDMODE_10:
//            return NTGameSave::sharedGameSave()->getDataById(_GS_GOLDMODE_TIMES)>9;
//            break;
//            
//        case TASK_GOLDMODE_15:
//            return NTGameSave::sharedGameSave()->getDataById(_GS_GOLDMODE_TIMES)>14;
//            break;
//        case TASK_BOY_LEVELUP:
//            return NTGameSave::sharedGameSave()->getDataById(_GS_HERO1_LEVEL)>2;
//            break;
//        case TASK_GIRL_LEVELUP:
//            return NTGameSave::sharedGameSave()->getDataById(_GS_HERO2_LEVEL)>2;
//            break;
//        case TASK_BABY_LEVELUP:
//            return NTGameSave::sharedGameSave()->getDataById(_GS_HERO3_LEVEL)>2;
//
//            break;
//        case TASK_HEART_PURCHASE:
//            if (NTGameSave::sharedGameSave()->getDataById(_GS_HEART_PURCHASE)==1) {
//                return true;
//            }else return false;
//            break;
//        case TASK_PET1_LEVELUP:
//            return NTGameSave::sharedGameSave()->getDataById(_GS_PET1_LEVEL)>2;
//            break;
//            
//        case TASK_PET2_LEVELUP:
//            return NTGameSave::sharedGameSave()->getDataById(_GS_PET2_LEVEL)>2;
//
//            break;
//        case TASK_PET3_LEVELUP:
//            return NTGameSave::sharedGameSave()->getDataById(_GS_PET3_LEVEL)>2;
//
//            break;
//        case TASK_HERO_LEVELTO10:
//            return (NTGameSave::sharedGameSave()->getDataById(_GS_HERO1_LEVEL)>9||NTGameSave::sharedGameSave()->getDataById(_GS_HERO2_LEVEL)>9||NTGameSave::sharedGameSave()->getDataById(_GS_HERO3_LEVEL)>9);
//
//            break;
//            
//        case TASK_HERO_LEVELTO15:
//            return (NTGameSave::sharedGameSave()->getDataById(_GS_HERO1_LEVEL)>14||NTGameSave::sharedGameSave()->getDataById(_GS_HERO2_LEVEL)>14||NTGameSave::sharedGameSave()->getDataById(_GS_HERO3_LEVEL)>14);
//            break;
//            
//        case TASK_PET_LEVELTO10:
//            return (NTGameSave::sharedGameSave()->getDataById(_GS_PET1_LEVEL)>9||NTGameSave::sharedGameSave()->getDataById(_GS_PET2_LEVEL)>9||NTGameSave::sharedGameSave()->getDataById(_GS_PET3_LEVEL)>9);
//            break;
//        case TASK_PET_LEVELTO15:
//            return (NTGameSave::sharedGameSave()->getDataById(_GS_PET1_LEVEL)>14||NTGameSave::sharedGameSave()->getDataById(_GS_PET2_LEVEL)>14||NTGameSave::sharedGameSave()->getDataById(_GS_PET3_LEVEL)>14);
//            break;
//            
//        default:
//            return false;
//            break;
//    }
	return true;
}


