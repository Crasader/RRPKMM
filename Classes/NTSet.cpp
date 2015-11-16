#include "NTSet.h"
#include "NTMenuItem.h"
#include "NTConstants.h"
#include "NTGameSound.h"
#include "NTGameSave.h"


void NTSet::onEnter()
{
	NTCoverLayer::onEnter();
	initValues();
	initUI();
}



void NTSet::initValues()
{

}

void NTSet::initUI()
{
	tinyxml2::XMLDocument pdocx;
	tinyxml2::XMLElement* pSurface;
	unsigned char* mybuf = NULL;
	unsigned long bufsize = 0;
	mybuf = CCFileUtils::sharedFileUtils()->getFileData(SET_XML_FILE,"r",&bufsize);
	if (!mybuf){
		return;
	}
	pdocx.Parse((const char*)mybuf,bufsize);
	if (pdocx.NoChildren()){
		return;
	}
	pSurface = pdocx.FirstChildElement();

	/*tinyxml2::XMLElement* pSurface = initUiDataFromXmlFile();*/
	if(pSurface==NULL){
		return;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	while(pSurface)
	{
		int posx = 0;	//X位置
		int posy = 0;	//Y位置
		int pid = 0;	//编号
		pSurface->QueryIntAttribute("posx",&posx);
		pSurface->QueryIntAttribute("posy",&posy);
		pSurface->QueryIntAttribute("pid",&pid);

		char filestr[80] = {0};
		sprintf(filestr,"%s%s", SET_PICTURE_PATH, pSurface->Name());

		//初始化背景
		if(strcmp(pSurface->Name(),"shzh_dk.png") == 0)
		{
			m_pBg = CCSprite::create(filestr);
			m_pBg->setPosition(ccp(winSize.width/2, winSize.height/2));
			this->addChild(m_pBg);

			//初始化MENU
			m_pMenu = CCMenu::create();
			m_pMenu->setPosition(CCPointZero);
			m_pMenu->setAnchorPoint(CCPointZero);
			m_pMenu->setTouchEnabled(false);
			this->addChild(m_pMenu,100);

			//关闭按钮
			addBackMenu("share_button/nn.png",ccp(580,380));

		}
		//-------  音乐调节按钮

// 		else if(strcmp(pSurface->Name(),"shzh_ant.png") == 0){
// 			slider = CCControlSlider::create("set/shzh_ank.png","set/shzh_ant.png" ,"set/shzh_an.png");
// 			slider->setAnchorPoint(ccp(0.5f, 1.0f));
// 			slider->setMinimumValue(0.0f); // Sets the min value of range(设置滑块的最小值)
// 			slider->setMaximumValue(5.0f); // Sets the max value of range（设置滑块的最大值）
// 			slider->setPosition(ccp(posx+40,posy+20));
// 			slider->setValue(1.0f);
// 		//	slider->setTouchMode(ccTouchesMode::kCCTouchesOneByOne);
// 			this->addChild(slider);
//  			if(pid == 1){
//  				//调节音量大小
//  				slider->addTargetWithActionForControlEvents(this, cccontrol_selector(NTSet::backgroudMusicChanged), CCControlEventValueChanged);
// 			}
// 			else{
// 				slider->addTargetWithActionForControlEvents(this, cccontrol_selector(NTSet::effectChanged), CCControlEventValueChanged);
// 			}
// 		}
		//-------  关于按钮
		else if(strcmp(pSurface->Name(),"shzh_gy.png") == 0)
		{
			pItem=NTMenuItemSprite::create(
										CCSprite::create("set/shzh_gy.png"),
										CCSprite::create("set/shzh_gy.png"),
										NULL,this,menu_selector(NTSet::menu_about));
			
			pItem->setPosition(ccp(posx+20,posy-20));
			m_pMenu->addChild(pItem);
		}
		pSurface = pSurface->NextSiblingElement();
	}
	pItem2=NTMenuItemSprite::create(
		CCSprite::create("set/close.png"),
		CCSprite::create("set/close.png"),
		NULL,this,menu_selector(NTSet::menu_about2));
	pItem2->setPosition(ccp(440,260));
	
	
	m_pMenu->addChild(pItem2,10);
	pItem3=NTMenuItemSprite::create(
		CCSprite::create("set/open.png"),
		CCSprite::create("set/open.png"),
		NULL,this,menu_selector(NTSet::menu_about3));
	pItem3->setPosition(ccp(480,260));
	m_pMenu->addChild(pItem3,10);
	if(NTGameSave::sharedGameSave()->isSound==1){
		pItem3->setVisible(false);
	}else{
		pItem2->setVisible(false);
	}
}

void NTSet::menu_show( CCObject *pSender )
{

}

void NTSet::backgroudMusicChanged( CCObject *sender, CCControlEvent controlEvent )
{
	  
	CCControlSlider* pSlider = (CCControlSlider*)sender;
	NTGameSound::sharedEngine()->setBackgroundMusicVolume(pSlider->getValue());
	 CCLOG("%f",pSlider->getValue()*5);
}

void NTSet::effectChanged( CCObject *sender, CCControlEvent controlEvent )
{
	CCControlSlider* pSlider = (CCControlSlider*)sender;
	NTGameSound::sharedEngine()->setEffectsVolume(pSlider->getValue());
}

void NTSet::menu_about( CCObject *pSender )
{
	pItem->setVisible(false);
	if(pItem2->isVisible()){
		pItem2->setVisible(false);
		ssss=1;
	}else{pItem3->setVisible(false);
		ssss=2;
	}

	ccsp1 = CCSprite::create("set/shzh_gy1.png");
	this->addChild(ccsp1);
	
	pItem1=CCMenuItemSprite::create(
		CCSprite::create("share_button/nn.png"),
		CCSprite::create("share_button/nn.png"),
		NULL,this,menu_selector(NTSet::menu_back_about));
	m_pMenu->addChild(pItem1);
	ccsp1->setPosition(ccp(400,200));
	pItem1->setPosition(ccp(600,320));
}

void NTSet::menu_back_about(CCObject* p){
	pItem->setVisible(true);
	if(ssss==1){
		pItem2->setVisible(true);
	}else{
		pItem3->setVisible(true);
	}
	pItem1->runAction(CCMoveTo::create(0.8f,ccp(400,1500)));
	ccsp1->runAction(CCMoveTo::create(0.8f,ccp(400,1500)));
	pItem1->removeAllChildrenWithCleanup(true);
	ccsp1->removeAllChildrenWithCleanup(true);

}

// bool NTSet::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){slider->ccTouchBegan(pTouch,pEvent);}
// void NTSet::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){slider->ccTouchBegan(pTouch,pEvent);}
// void NTSet::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){slider->ccTouchBegan(pTouch,pEvent);}
// void NTSet::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){slider->ccTouchBegan(pTouch,pEvent);}

void NTSet::menu_about3( CCObject *pSender ){

		pItem3->setVisible(false);
		pItem2->setVisible(true);
    NTGameSound::sharedEngine()->switchAudio();
}

void NTSet::menu_about2( CCObject *pSender ){

		pItem2->setVisible(false);
		pItem3->setVisible(true);
	//	if(){}
		//NTGameSave::sharedGameSave()->isSound=0;
    NTGameSound::sharedEngine()->switchAudio();
}


