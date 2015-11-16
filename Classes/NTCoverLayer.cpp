#include "NTCoverLayer.h"
#include "NTMenuItem.h"
bool NTCoverLayer::init()
{
	
		bool bRet = false;
		do
		{
			CC_BREAK_IF( !CCLayerColor::init() );
	
			m_pMenu = NULL;
			m_bTouchEnd = true;
			m_bTouchedMenu = false;
			this->setColor(ccc3(0, 0, 0));
			this->setOpacity(160);
			setTouchEnabled(true);
			
			bRet = true;
		}while(0);
	
		return bRet;
}

void NTCoverLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 20, true);
}

bool NTCoverLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if(m_bTouchEnd && m_pMenu)
	{
		m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent); 
		if(m_bTouchedMenu)
			m_bTouchEnd=false;
	}
	return true;  
}

void NTCoverLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bTouchedMenu) {  
		m_pMenu->ccTouchMoved(pTouch, pEvent);  
	}  
}

void NTCoverLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bTouchedMenu) {

		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
		m_bTouchEnd=true;
	}
}

void NTCoverLayer::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bTouchedMenu) {
		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
		m_bTouchEnd=true;
	}
}

void NTCoverLayer::bornOnLayer( CCLayer *layer )
{
	this->setPosition(ccp(0,600));	
	layer->addChild(this, 100);
	this->runAction(CCEaseBounceOut::create(CCMoveTo::create(1.0,ccp(0,0))));
}

void NTCoverLayer::closeSelf()
{
	CCMoveTo * moveOut=CCMoveTo::create(0.2,ccp(0,600));
	CCCallFunc *callback=CCCallFunc::create(this,callfunc_selector(NTCoverLayer::closeSelfCallBack));
	this->runAction(CCSequence::createWithTwoActions(moveOut,callback));
}

void NTCoverLayer::closeSelfCallBack()
{
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
}

void NTCoverLayer::addBackMenu(const char* fileName,CCPoint pt )
{
	if(m_pMenu){
		CCPoint ipos = m_pMenu->convertToNodeSpace(pt);
		NTMenuItemSprite *backItem=NTMenuItemSprite::create(
							CCSprite::create(fileName),
							CCSprite::create(fileName),
							NULL,this,menu_selector(NTCoverLayer::backItemClick));
		m_pMenu->addChild(backItem);
		backItem->setPosition(pt);
	}
}

void NTCoverLayer::backItemClick( CCObject *pSender )
{
	closeSelf();
}

