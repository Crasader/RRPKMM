#include "NTSign.h"

#include "NTConstants.h"
#include "NTStart.h"
#include "NTSharedJsonData.h"
#include "NTGameSave.h"
void NTSign::onEnter()
{
	
	NTCoverLayer::onEnter();
    initValue();
	initUI();
}
void NTSign::initValue()
{
    int task1[4]={4,5,6,10};
    int task2[4]={2,3,9,12};
    int task3[4]={1,7,8,11};
    if ( NTGameSave::sharedGameSave()->getDataById(_GS_SIGN)==1||NTGameSave::sharedGameSave()->getDataById(_GS_FIRST_TASK)==0) {
        CCLog("taskrefresh");
      //  NTGameSave::sharedGameSave()->updateValue(_GS_GOLD,999999);
        NTGameSave::sharedGameSave()->updateValue(_GS_FIRST_TASK, 1);
        m_taskId[0]=task1[rand()%4];
        //cclog("taskone%d",m_taskId[0]);
        m_taskId[1]=task2[rand()%4];
        //cclog("tasktwo%d",m_taskId[1]);
        m_taskId[2]=task3[rand()%4];
        //cclog("taskthree%d",m_taskId[2]);
        for (int i=0; i<3; i++) {
            NTGameSave::sharedGameSave()->updateValue(_GS_TASKONE+i, m_taskId[i]);
            NTGameSave::sharedGameSave()->updateValue(_GS_TASKONE_FINISH+i,0);
        }
         NTGameSave::sharedGameSave()->updateValue(_GS_TASK_COMPLISH,0);
       NTGameSave::sharedGameSave()->updateValue(_GS_SCORE, 0);
        NTGameSave::sharedGameSave()->updateValue(_GS_BOX_HIT, 0);
        NTGameSave::sharedGameSave()->updateValue(_GS_GOLDMODE_TIMES, 0);
        NTGameSave::sharedGameSave()->updateValue(_GS_HEART_USE, 0);
    }
      taskcomplish=0;
    for (int i=0; i<3; i++) {
        m_taskFinish[i]=( NTGameSave::sharedGameSave()->getDataById(_GS_TASKONE_FINISH+i)==0?false:true);
        taskcomplish+= NTGameSave::sharedGameSave()->getDataById(_GS_TASKONE_FINISH+i);
    }
    //cclog("taskcomplish%d",taskcomplish);
   }
void NTSign::initUI()
{
    
    
	//-------  ≤Àµ•
	CCMenu *pMenu = CCMenu::create();
	this->addChild(pMenu,2);
	pMenu->setPosition(CCPointZero);
	pMenu->setAnchorPoint(CCPointZero);
	setMenu(pMenu);

	//-------  ±≥æ∞
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	 pSignBg = CCSprite::create("sign/meiri_db.png");
	this->addChild(pSignBg);
	pSignBg->setPosition(ccp(winSize.width/2,winSize.height/2-42));
    pTaskBg = CCSprite::create("sign/meiri_db.png");
    this->addChild(pTaskBg);
    pTaskBg->setPosition(ccp(winSize.width/2,winSize.height/2-42));
   if( NTGameSave::sharedGameSave()->getDataById(_GS_SIGN)==1)
    { pTaskBg->setScale(0);
        pSignBg->setScale(1);
    }
    else{
        pTaskBg->setScale(1);
        pSignBg->setScale(0);
    }
	//-------  «©µΩœÓ
    int posX=120;
    int posY=10;
	CCPoint posSignItem[7] ={ccp(101-posX,233-posY),ccp(234-posX,234-posY),ccp(366-posX,233-posY),ccp(498-posX,232-posY),ccp(164-posX,93-posY),ccp(296-posX,95-posY),ccp(431-posX,94-posY)};
	for(int i=0;i<7;i++){
		//-------  ª“…´µƒ
		CCSprite *pSign1 = CCSprite::create("sign/meiri_andb.png");
		pSignBg->addChild(pSign1);
		pSign1->setPosition(ccp(posSignItem[i].x+100,posSignItem[i].y+60));
		m_pUnSelect[i] = pSign1;
		m_pUnSelect[i]->setVisible(false);
		//-------  ¡¡…´µƒ
		CCSprite *pSign2 = CCSprite::create("sign/meiri_ldb.png");
		pSignBg->addChild(pSign2);
		pSign2->setPosition(ccp(posSignItem[i].x+100,posSignItem[i].y+60));
		m_pSelect[i] = pSign2;
		m_pSelect[i]->setVisible(false);
		//-------Ω±“
        CCSprite *pGold;
        if (i==2) {
            pGold=CCSprite::create("sign/meiri_tsjl.png");
            
        }else if(i==6){
            pGold=CCSprite::create("sign/meiri_luol.png");
        
        }else
        {
		pGold = CCSprite::create("sign/meiri_jb.png");
            pGold->setScale(0.8f);
        }
		pSignBg->addChild(pGold);
		pGold->setPosition(ccp(posSignItem[i].x+100,posSignItem[i].y+60));
		CCSprite *pDay = CCSprite::create(CCString::createWithFormat("sign/meiri_shz%d.png",i+1)->getCString());
		pSignBg->addChild(pDay);
		pDay->setPosition(ccp(posSignItem[i].x+100,posSignItem[i].y+104));
        if (i==2) {
            CCSprite *pText=CCSprite::create("hero/stage_js5ts.png");
            pSignBg->addChild(pText);
            pText->setPosition(ccp(posSignItem[i].x+100,posSignItem[i].y+20));
            pText->setAnchorPoint(ccp(0.5,0.5));
        }else if(i==6){
            CCSprite *pText=CCSprite::create("hero/stage_ll.png");
            pSignBg->addChild(pText);
            pText->setPosition(ccp(posSignItem[i].x+100,posSignItem[i].y+20));
            pText->setAnchorPoint(ccp(0.5,0.5));
        }else
        {
		CCLabelAtlas *pNum = CCLabelAtlas::create(CCString::createWithFormat("%d",(i+1)*1000)->getCString(),"sign/meiri_jbnb.png",13,25,'0');
		pSignBg->addChild(pNum);
		pNum->setPosition(ccp(posSignItem[i].x+100,posSignItem[i].y+20));
		pNum->setAnchorPoint(ccp(0.5,0.5));
        }
		//logo
		CCSprite *pSelectLogo = CCSprite::create("sign/meiri_yzh.png");
        pSelectLogo->setScale(0.7f);
		pSignBg->addChild(pSelectLogo);
		pSelectLogo->setPosition(ccp(posSignItem[i].x+150,posSignItem[i].y+20));
		m_pSelectLogo[i] = pSelectLogo;
		m_pSelectLogo[i]->setVisible(false);
        
		

	}
    CCPoint posTaskReward[3]={ccp(170,250),ccp(340,250),ccp(510,250)};
     CCPoint posTaskItem[3]={ccp(winSize.width/2-110,170),ccp(winSize.width/2-110,130),ccp(winSize.width/2-110,90)};
    CCSprite *RewardBoard =CCSprite::create("sign/meiri_lq1.png");
    RewardBoard->setPosition(ccp(winSize.width/2-115,280));
    pTaskBg->addChild(RewardBoard);
    for (int i=0; i<3; i++) {
        m_taskId[i]=NTGameSave::sharedGameSave()->getDataById(_GS_TASKONE+i);
        //Reward Got or Not
        m_pRewardGot[i]=CCSprite::create("sign/meiri_lq.png");
         m_pRewardGot[i]->setPosition(posTaskReward[i]);
        pTaskBg->addChild(m_pRewardGot[i]);
        //Taskboard 1 2 3
        m_pTaskNo[i]=CCSprite::create("sign/meiri_rw1.png");
        m_pTaskNo[i]->setPosition(posTaskItem[i]);
        pTaskBg->addChild(m_pTaskNo[i]);
        //TaskDescription 123
        m_pTaskDec[i]=CCSprite::create(CCString::createWithFormat("sign/meiri_rwz%d.png",m_taskId[i]*2)->getCString());
        m_pTaskNo[i]->addChild(m_pTaskDec[i]);
        m_pTaskDec[i]->setPosition(ccp(150,20));
        m_pTaskLabel[i] =CCLabelAtlas::create("01","sign/meiri_rwsz1.png",15,21,'0');
        m_pTaskLabel[i]->setAnchorPoint(ccp(0.5f,0));
         m_pTaskLabel[i]->setPosition(ccp(400, 10));
         m_pTaskNo[i]->addChild(m_pTaskLabel[i]);
        
        //Taskboard 1 2 3
        m_pTaskYes[i]=CCSprite::create("sign/meiri_rw2.png");
        m_pTaskYes[i]->setPosition(posTaskItem[i]);
        pTaskBg->addChild(m_pTaskYes[i]);
        //TaskDescription 123
        m_pTaskDec0[i]=CCSprite::create(CCString::createWithFormat("sign/meiri_rwz%d.png",m_taskId[i]*2-1)->getCString());
        m_pTaskYes[i]->addChild(m_pTaskDec0[i]);
        m_pTaskDec0[i]->setPosition(ccp(150,20));
        m_pTaskLabel0[i] =CCLabelAtlas::create("01","sign/meiri_rwsz2.png",15,21,'0');
        m_pTaskLabel0[i]->setAnchorPoint(ccp(0.5f,0));
        m_pTaskLabel0[i]->setPosition(ccp(400, 10));
        if (i<NTGameSave::sharedGameSave()->getDataById(_GS_TASK_COMPLISH)) {
        }
        else m_pRewardGot[i]->setVisible(false);
        m_pTaskYes[i]->addChild(m_pTaskLabel0[i]);
        m_pTaskNo[i]->setVisible(m_taskFinish[i]?false:true);
        m_pTaskYes[i]->setVisible(m_taskFinish[i]?true:false);
            int target;
        int complish[3]={0,0,0};
            switch (m_taskId[i]) {
                case TASK_HIT_BOX:
                    target=10;
                    complish[1]=NTGameSave::sharedGameSave()->getDataById(_GS_BOX_HIT);
                    break;
                case TASK_GOLD_MODE:
                    target=3;
                    complish[1]=NTGameSave::sharedGameSave()->getDataById(_GS_GOLDMODE_TIMES);
                    break;
                case TASK_SCORE_10000:
                    target=10000;
                    complish[0]=NTGameSave::sharedGameSave()->getDataById(_GS_SCORE);
                    break;
                case TASK_SCORE_30000:
                    target=30000;
                    complish[0]=NTGameSave::sharedGameSave()->getDataById(_GS_SCORE);
                    break;
                case TASK_SCORE_50000:
                    target=50000;
                    complish[0]=NTGameSave::sharedGameSave()->getDataById(_GS_SCORE);
                    break;
                case TASK_SCORE_80000:
                    target=80000;
                    complish[0]=NTGameSave::sharedGameSave()->getDataById(_GS_SCORE);
                    break;
                case TASK_HEART_USEUP:
                    target=5;
                    break;
                default:
                    target=1;
                    break;
            }
            m_pTaskLabel[i]->setString(CCString::createWithFormat("%d:%d",complish[i],target)->getCString());
         m_pTaskLabel0[i]->setString(CCString::createWithFormat("%d:%d",target,target)->getCString());
    }
    
 pSignButton=NTMenuItemSprite::create(
                                                     CCSprite::create("sign/meiri_bq4.png"),
                                                     CCSprite::create("sign/meiri_bq4.png"),
                                                     CCSprite::create("sign/meiri_bq1.png"),this,menu_selector(NTSign::menu_signBg));
    pMenu->addChild(pSignButton);
    pSignButton->setPosition(ccp(winSize.width/4+110,400));
    
    
     pTaskButton=NTMenuItemSprite::create(
                                                           CCSprite::create("sign/meiri_bq3.png"),
                                                           CCSprite::create("sign/meiri_bq3.png"),
                                                           CCSprite::create("sign/meiri_bq2.png"),this,menu_selector(NTSign::menu_taskBg));
    pMenu->addChild(pTaskButton);
    pTaskButton->setPosition(ccp(winSize.width/4+290,400));
    pTaskButton->setEnabled(pTaskBg->getScale()==0?true:false);
   pSignButton->setEnabled(pTaskBg->getScale()==0?false:true);
	//-------  ¡Ï»°∞¥≈•
	NTMenuItemSprite *pItem=NTMenuItemSprite::create(
								CCSprite::create("sign/renwu_an.png"),
								CCSprite::create("sign/renwu_an.png"),
								NULL,this,menu_selector(NTSign::menu_complete));
	pMenu->addChild(pItem);
	pItem->setPosition(ccp(winSize.width/2,50));
    //Jerry--edit
//	if(getSelectDay() == -1)
		//pItem->setVisible(false);

	//-------  πÿ±’∞¥≈•
    if(NTGameSave::sharedGameSave()->getDataById(_GS_SIGN)!=1)
	addBackMenu("share_button/nn.png",ccp(693,371));

	setSignDay(NTGameSave::sharedGameSave()->getDataById(_GS_SIGN_TIMES));
}


void NTSign::setSignDay( int nday )
{
	for(int i =0;i<7;i++){
		if(i<nday){
			//m_pSelectLogo[i]->setVisible(false);
            m_pUnSelect[i]->setColor(ccc3(211,211,211));
		}else{
            //m_pSelectLogo[i]->setVisible(false);
		}
		if(i == nday){
            m_pSelectLogo[i]->setVisible(true);
			m_pSelect[i]->setVisible(true);
			m_pUnSelect[i]->setVisible(false);
		}else{
			m_pSelect[i]->setVisible(false);
			m_pUnSelect[i]->setVisible(true);
		}
	}
}

void NTSign::menu_complete( CCObject *pSender )
{
     NTGameSave::sharedGameSave()->updateValue(_GS_SIGN, 0);
    if (pSignBg->getScale()) {
        CCMenuItem *pItem = (CCMenuItem*)pSender;
        pItem->setVisible(false);
        this->closeSelf();
        //	this->closeSelfCallBack();
        int curGold =NTGameSave::sharedGameSave()->getDataById(_GS_GOLD);
        
        int nCurDay = getSelectDay();
        if(nCurDay < 0)
            return;
        if(nCurDay==2)
            NTGameSave::sharedGameSave()->updateBuyPet(_GS_PET_IS_BUY_1,true);
        else if(nCurDay==6)
            NTGameSave::sharedGameSave()->updateBuyHero(_GS_HERO_IS_BUY_2,true);
        else
        {
            curGold+=(nCurDay+1)*1000;
            NTGameSave::sharedGameSave()->updateValue(_GS_GOLD,curGold);
        }
    }else{
        int rewardtogot= NTGameSave::sharedGameSave()->getDataById(_GS_TASK_COMPLISH);
        //////cclog("rewardtogot%d",rewardtogot);
         int reward[3]={3000,5000,12000};
        for (int i=rewardtogot; i<taskcomplish; i++) {
            NTGameSave::sharedGameSave()->updateValue(_GS_GOLD,NTGameSave::sharedGameSave()->getDataById(_GS_GOLD)+reward[i]);
            m_pRewardGot[i]->setVisible(true);
        }
        NTGameSave::sharedGameSave()->updateValue(_GS_TASK_COMPLISH,taskcomplish);
        
            }
	
//	NTStart *pLayer =(NTStart*)this->getParent();
//	pLayer->updateGoldView();

}
void NTSign::menu_signBg(CCObject *pSender)
{
    pSignButton->setEnabled(false);
    pTaskButton->setEnabled(true);
        pSignBg->setScale(1);
        pTaskBg->setScale(0);
    //Jerry-test
   // NTGameSave::sharedGameSave()->updateValue(_GS_FIRST_TASK, 0);
    
    
}
void NTSign::menu_taskBg(CCObject *pSender)
{
    pSignButton->setEnabled(true);
    pTaskButton->setEnabled(false);
        pSignBg->setScale(0);
        pTaskBg->setScale(1);
    
}

NTSign::NTSign()
{
	m_nSelectDay = -1;
}
