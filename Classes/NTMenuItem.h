#ifndef _H_NTMENUITEM_H_
#define _H_NTMENUITEM_H_

#include "menu_nodes/CCMenuItem.h"
#include "cocos2d.h"
using namespace cocos2d;
class NTMenuItemSprite : public CCMenuItemSprite
{
public:
    NTMenuItemSprite();
    ~NTMenuItemSprite();
   void setNormalImage(CCNode* pImage);
   void setSelectedImage(CCNode* pImage);
	  void setDisabledImage(CCNode* pImage);
    

    /** creates a menu item with a normal, selected and disabled image*/
    static NTMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite = NULL);
    /** creates a menu item with a normal and selected image with target/selector */
    static NTMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    static NTMenuItemSprite * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);

    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    bool initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);
    


};
/*--------------¿ª¹Ø°´Å¥--------------------*/  
class NTMenuItemToggle : public CCMenuItemSprite{
public:
	NTMenuItemToggle();
	/** creates a menu item with a normal, selected and disabled image*/
	static NTMenuItemToggle * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite = NULL);
	/** creates a menu item with a normal and selected image with target/selector */
	static NTMenuItemToggle * create(CCNode* normalSprite, CCNode* selectedSprite, CCObject* target, SEL_MenuHandler selector);
	/** creates a menu item with a normal,selected  and disabled image with target/selector */
	static NTMenuItemToggle * create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);

	void activate();

	void unselected();

	void selected();
	

	void setSelectIndex(int nVal);
	int getSelectIndex();
private:
	int m_nSelectIndex;
};

#endif //_H_NTMENUITEM_H_