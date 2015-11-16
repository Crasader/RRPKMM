#include "NTRank.h"
#include "GUI/CCScrollView/CCScrollView.h"
#include "json.h"
#include "NTSharedJsonData.h"
#include "NTGameSave.h"

using namespace extension;
void NTRank::onEnter()
{
	m_pMyName = NULL;
	CCLayer::onEnter();
	initUI();
	
}

void NTRank::initUI()
{
	
	//-------  ’⁄∏«
	CCScrollView *pScrollView = CCScrollView ::create();
	pScrollView->setViewSize(CCSprite::create("rank/phb_db.png")->getContentSize());
	this->addChild(pScrollView);
    pScrollView->setScale(0.8f);
	pScrollView->setPosition(ccp(500,120));

	//------- ±≥æ∞
	CCSprite *pBg = CCSprite::create("rank/phb_db.png");
	pScrollView->addChild(pBg);
	

	//-------  ≈≈––∞Ò◊”œÓ
	CCSize pSize = pBg->getContentSize();
	const char* strPath[]={"rank/phb_k.png","rank/phb_k1.png"};
	CSJson::Value pJson = NTSharedJsonData::sharedJsonData()->getJsonRank();
	//int iIndex = rand()%(pJson["rank"].size()-ITEM_MAX);
	for(int i=0;i<ITEM_MAX;i++){
		//-------  ◊”œÓ±≥æ∞
		CCSprite *pSprite = CCSprite::create(strPath[i%2]);
		pBg->addChild(pSprite);
		pSprite->setPosition(ccp(pSize.width/2,pSize.height-(i+1.25)*pSprite->getContentSize().height));
		m_pItemPos[i] = pSprite->getPosition();
		m_pItem[i] = pSprite;
		m_pItem[i]->setVisible(false);
		m_pItem[i]->setPosition(m_pItemPos[i].x+(i%2 ==0?1:-1)*300,m_pItemPos[i].y);

		//-------  Õ∑œÒ
		CCSprite *pHeadIcon = CCSprite::create(CCString::createWithFormat("rank/phb_tx%d.png",i+1)->getCString());
		m_pItem[i]->addChild(pHeadIcon);
		pHeadIcon->setPosition(ccp(55,m_pItem[i]->getContentSize().height/2));
		//-------  √˚◊÷
		
		//int iIndex = pJson["rank"].size();

		CCLabelTTF *pName;
		if(i != 4){
			pName = CCLabelTTF::create(pJson["rank"][i].asCString(),"arial",15);
			pName->setColor(ccBLACK);
		}else{
			pName =CCLabelTTF::create(pJson["hero"].asCString(),"arial",15);
			pName->setColor(ccBLUE);
			m_pMyName = pName;
		}
		
		m_pItem[i]->addChild(pName);
		pName->setAnchorPoint(ccp(0,0.5));
		pName->setPosition(ccp(80,m_pItem[i]->getContentSize().height/2+10));
		
		m_pName[i] = pName;
		
	}
	//-------  Ω±“≈≈–Ú
	int nGold[ITEM_MAX];
	
		for(int i=0;i<ITEM_MAX-1;i++){
			if(!NTGameSave::sharedGameSave()->IsGameOpen()){
				nGold[i] = pJson["savegold"][i].asInt();
			}else{
                nGold[i] = rand()%100000+100000*(rand()%5+1);
			}
		}
		nGold[ITEM_MAX-1]= NTGameSave::sharedGameSave()->getDataById(_GS_MAX_SCORE);
	
	
	selectSort(nGold,ITEM_MAX);

	
	for(int i=0;i<ITEM_MAX;i++){

		//-------  ≈≈√˚–Ú∫≈
		CCNode *pRankIndex;
		const char* strIndex[] ={"rank/phb_jp.png","rank/phb_yp.png","rank/phb_tp.png"};
		if(i <= 2){
			CCSprite *pIndexSprite  = CCSprite::create(strIndex[i]);
			pRankIndex = pIndexSprite;
		}else{
			CCLabelAtlas *pIndexLabel = CCLabelAtlas::create(CCString::createWithFormat("%d",i+1)->getCString(),"rank/phb_pmnb.png",7,13,'0');
			pRankIndex = pIndexLabel;
		}
		m_pItem[i]->addChild(pRankIndex);
		pRankIndex->setAnchorPoint(ccp(0.5,0.5));
		pRankIndex->setPosition(ccp(15,m_pItem[i]->getContentSize().height/2));


		//-------  Ω±“
		CCLabelAtlas *pGolds = CCLabelAtlas::create("0","rank/phb_pmnb.png",7,13,'0');
		m_pItem[i]->addChild(pGolds);	
		m_pGold[i] = pGolds;
		//pGolds->setScale(0.5);
		pGolds->setPosition(ccp(110,m_pItem[i]->getContentSize().height/2-15));
		m_pGold[i]->setString(CCString::createWithFormat("%d",nGold[i])->getCString());
	}

	if(NTGameSave::sharedGameSave()->IsGameOpen()){
		NTGameSave::sharedGameSave()->setIsGameOpen(false);
		for(int j=0;j<ITEM_MAX;j++){
			pJson["savegold"][j] = nGold[j];
			
		
		}

		std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
		path+="rank";
		NTSharedJsonData::sharedJsonData()->saveJsonFile(path,pJson);
		NTSharedJsonData::sharedJsonData()->updateData(eRank);
	}

	//-------  ø™ º∂Øª≠
	show();
}

void NTRank::show()
{
	for(int i=0;i<ITEM_MAX;i++){
		m_pItem[i]->setVisible(true);

		m_pItem[i]->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.8f,m_pItemPos[i])));
	}

}
//-------  ¥”¥ÛµΩ–°µƒ—°‘Ò≈≈–Ú
void NTRank::selectSort( int a[],int n )
{
//	int k;
//	for(int i=0;i<n;i++){
//		k =i;
//		for(int j=i+1;j<n;j++){
//			if(a[k] < a[j]){
//				k = j;
//			}
//		}
//		if(i != k){
//			int temp = a[i];
//			a[i] = a[k];
//			a[k] = temp;
//
//
//		
//			CCNode* tempItem = m_pItem[i];
//			m_pItem[i] = m_pItem[k];
//			m_pItem[k] = tempItem;
//
//		}
//	}
    int temp=0;
    for (int i=n-1; i>0; --i) {
        for (int j=0; j<i; ++j) {
            if (a[j+1]>a[j]) {
                 temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
                
                			CCNode* tempItem = m_pItem[j];
                			m_pItem[j] = m_pItem[j+1];
                			m_pItem[j+1] = tempItem;
            }
        }
    }
   
}

void NTRank::updateMyNameView( std::string strName )
{
	if(m_pMyName){
		m_pMyName->setString(strName.c_str());
	}
}

