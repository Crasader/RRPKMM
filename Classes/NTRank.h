/********************************************************************
 *    文件名  :    NTRank.h
 *    作者    :    yobo
 *    创建时间:    2014/01/06 14:20 
 *    文件描述:    排行榜
 *********************************************************************/
#ifndef _H_NTRANK_H_
#define _H_NTRANK_H_

#include "cocos2d.h"
using namespace cocos2d;
# define ITEM_MAX 5
class NTRank : public CCLayer{

public:
	CREATE_FUNC(NTRank);
	void onEnter();
	//-------  初始化
	void initUI();
	//-------  小动画
	void show();


	CCNode *m_pItem[ITEM_MAX];
	CCPoint m_pItemPos[ITEM_MAX];
	CCLabelAtlas *m_pGold[ITEM_MAX];
	CCLabelTTF *m_pName[ITEM_MAX];

	void selectSort(int a[],int length);

	CCLabelTTF *m_pMyName;
	void updateMyNameView(std::string strName);

	
	

};

#endif //_H_NTRANK_H_