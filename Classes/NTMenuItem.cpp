#include "NTMenuItem.h"
const unsigned int    kNormalTag = 0x1;
const unsigned int    kSelectedTag = 0x2;
const unsigned int    kDisableTag = 0x3;
NTMenuItemSprite::NTMenuItemSprite()
{

}
NTMenuItemSprite::~NTMenuItemSprite()
{

};
//
//NTMenuItemSprite
//


void NTMenuItemSprite::setNormalImage(CCNode* pImage)
{
	if (pImage != m_pNormalImage)
	{
		if (pImage)
		{
			addChild(pImage, 0, kNormalTag);
			pImage->setAnchorPoint(ccp(0.5, 0.5));
			pImage->setPosition(pImage->getAnchorPoint().x*pImage->getContentSize().width,pImage->getAnchorPoint().y*pImage->getContentSize().height);
		}

		if (m_pNormalImage)
		{
			removeChild(m_pNormalImage, true);
		}

		m_pNormalImage = pImage;
		this->setContentSize(m_pNormalImage->getContentSize());
		this->updateImagesVisibility();
	}
}



void NTMenuItemSprite::setSelectedImage(CCNode* pImage)
{
	if (pImage != m_pNormalImage)
	{
		if (pImage)
		{
			addChild(pImage, 0, kSelectedTag);
			pImage->setAnchorPoint(ccp(0.5, 0.5));
			pImage->setPosition(pImage->getAnchorPoint().x*pImage->getContentSize().width,pImage->getAnchorPoint().y*pImage->getContentSize().height);
			pImage->setScale(1.1);

		}

		if (m_pSelectedImage)
		{
			removeChild(m_pSelectedImage, true);
		}

		m_pSelectedImage = pImage;
		this->updateImagesVisibility();
	}
}



void NTMenuItemSprite::setDisabledImage(CCNode* pImage)
{
	if (pImage != m_pNormalImage)
	{
		if (pImage)
		{
			addChild(pImage, 0, kDisableTag);
			pImage->setAnchorPoint(ccp(0.5, 0.5));
			pImage->setPosition(pImage->getAnchorPoint().x*pImage->getContentSize().width,pImage->getAnchorPoint().y*pImage->getContentSize().height);
		}

		if (m_pDisabledImage)
		{
			removeChild(m_pDisabledImage, true);
		}

		m_pDisabledImage = pImage;
		this->updateImagesVisibility();
	}
}

//
//NTMenuItemSprite
//

NTMenuItemSprite * NTMenuItemSprite::create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite)
{
	return NTMenuItemSprite::create(normalSprite, selectedSprite, disabledSprite, NULL, NULL);
}

NTMenuItemSprite * NTMenuItemSprite::create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector)
{
	return NTMenuItemSprite::create(normalSprite, selectedSprite, NULL, target, selector);
}

NTMenuItemSprite * NTMenuItemSprite::create(CCNode *normalSprite, CCNode *selectedSprite, CCNode *disabledSprite, CCObject *target, SEL_MenuHandler selector)
{
	NTMenuItemSprite *pRet = new NTMenuItemSprite();
	pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector); 
	pRet->autorelease();
	return pRet;
}
bool NTMenuItemSprite::initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItem::initWithTarget(target, selector); 
	setNormalImage(normalSprite);
	setSelectedImage(selectedSprite);
	setDisabledImage(disabledSprite);

	if(m_pNormalImage)
	{
		this->setContentSize(m_pNormalImage->getContentSize());
	}

	setCascadeColorEnabled(true);
	setCascadeOpacityEnabled(true);

	return true;
}
/*--------------¿ª¹Ø°´Å¥--------------------*/  
NTMenuItemToggle::NTMenuItemToggle()
{
	m_nSelectIndex = 0;
}

NTMenuItemToggle * NTMenuItemToggle::create( CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite /*= NULL*/ )
{
	return NTMenuItemToggle::create(normalSprite, selectedSprite, disabledSprite, NULL, NULL);
}

NTMenuItemToggle * NTMenuItemToggle::create( CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector )
{
	 return NTMenuItemToggle::create(normalSprite, selectedSprite, NULL, target, selector);
}

NTMenuItemToggle * NTMenuItemToggle::create( CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector )
{
	NTMenuItemToggle *pRet = new NTMenuItemToggle();
	pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector); 
	pRet->autorelease();
	return pRet;
}

void NTMenuItemToggle::activate()
{
	 if(m_bEnabled){
		CCMenuItemSprite::activate();
	 }
	 if(m_nSelectIndex == 0){
		 setSelectIndex(1);
	 }else{
		 setSelectIndex(0);
	 }
}

void NTMenuItemToggle::setSelectIndex( int nVal )
{
	if(m_nSelectIndex != nVal){
		if(nVal == 0){
			if (m_pNormalImage)
			{
				m_pNormalImage->setVisible(true);

				if (m_pSelectedImage)
				{
					m_pSelectedImage->setVisible(false);
				}

				if (m_pDisabledImage)
				{
					m_pDisabledImage->setVisible(false);
				}
			}
		}else{
			if (m_pNormalImage)
			{
				m_pNormalImage->setVisible(false);

				if (m_pSelectedImage)
				{
					m_pSelectedImage->setVisible(true);
				}

				if (m_pDisabledImage)
				{
					m_pDisabledImage->setVisible(false);
				}
			}
		}
		
	}
	m_nSelectIndex = nVal;

}
int NTMenuItemToggle::getSelectIndex()
{
	return m_nSelectIndex;
}

void NTMenuItemToggle::selected()
{
	CCMenuItem::selected();
}

void NTMenuItemToggle::unselected()
{
	CCMenuItem::unselected();
}
