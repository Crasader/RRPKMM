/********************************************************************
 *    文件名  :    NTTask.h
 *    作者    :    yobo
 *    创建时间:    2014/01/16 10:12 
 *    文件描述:    
 *********************************************************************/
#ifndef _H_NTTASK_H_
#define _H_NTTASK_H_
#include "cocos2d.h"
#include "NTCoverLayer.h"
USING_NS_CC;

enum{
    TASK_RUN_2000=1,
    TASK_RUN_4000,
    TASK_RUN_5000,
    TASK_RUN_8000,
    TASK_GOLDMODE_5,
    TASK_GOLDMODE_10,
    TASK_GOLDMODE_15,
    TASK_BOY_LEVELUP,
    TASK_BABY_LEVELUP,
    TASK_GIRL_LEVELUP,
    TASK_HEART_PURCHASE,
    TASK_PET1_LEVELUP,
    TASK_PET2_LEVELUP,
    TASK_PET3_LEVELUP,
    TASK_HERO_LEVELTO10,
    TASK_HERO_LEVELTO15,
    TASK_PET_LEVELTO10,
    TASK_PET_LEVELTO15
};
class NTTask:public NTCoverLayer{

public:
	CREATE_FUNC(NTTask);

	void onEnter();
	void initValue();
	void initUI();


	//-------  按钮回调事件
	void menu_finish(CCObject *pSender);
    bool isTaskFinished(int type);
    void setTaskFinished(int type);
//    int getTaskOne();
//    int getTaskTwo();
//    int getTaskThree();
//    void setTaskOne();
//    void setTaskTwo();
//    void setTaskThree();
//    int taskOne;
//    int taskTwo;
//    int taskThree;
    CC_SYNTHESIZE(int,m_pTaskOne,TaskOne);
    CC_SYNTHESIZE(int,m_pTaskTwo,TaskTwo);
    CC_SYNTHESIZE(int,m_pTaskThree,TaskThree);

private:
	
};

#endif //_H_NTTASK_H_