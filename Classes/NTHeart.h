#ifndef _NTHEART_H_
#define _NTHEART_H_

#include "cocos2d.h"
#include "NTCoverLayer.h"


#define HEART_PICTURE_PATH "heart/"


USING_NS_CC;

class NTHeart:public NTCoverLayer
{
public:
	CREATE_FUNC(NTHeart);
private:

private:

	void onEnter();

	//��ʼ������
	void initValues();
	//��ʼ��UI
	void initUI();
	void setupdataLibaoState(int i);
	void update_heart(float f);
	int	index;
	int count1;
	//��ť�ص��¼�
	void menu_buy(CCObject* pRender);
	void menu_close(CCObject* p);
	void callback_close();



};

#endif /*_NTHEART_H_*/