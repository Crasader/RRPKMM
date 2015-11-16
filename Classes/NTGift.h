                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        #ifndef _NTGIFT_H_
#define _NTGIFT_H_

#include "cocos2d.h"
#include "NTCoverLayer.h"

#define GIFT_PICTURE_PATH "gift/"

USING_NS_CC;

class NTGift:public NTCoverLayer
{
public:
	CREATE_FUNC(NTGift);

private:

private:

	void onEnter();
	void initValues();
	void initUI();
	void setupdataLibaoState(int i);
	void update_heart(float f);
	void menu_buy(CCObject* pRender);
	void menu_close(CCObject* p);
	void callback_close();
    void pGetCallback(CCObject* pSender);
    void pExitCallback(CCObject* pSender);
};

#endif