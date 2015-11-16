
#ifndef _H_NTBOX_H_
#define _H_NTBOX_H_

#include "cocos2d.h"
/*#include "NTMapLayer.h"*/

USING_NS_CC;

class NTMapLayer;

class NTBox : public CCSprite{

public:
	NTBox();
	//�������ӣ���������
	static NTBox* createBox(int iType);
public:
	//���Ե��pos
	CCPoint getLeftPos();
	//���Ե��pos
	CCPoint getRightPos();
	//�ϱ�Ե��pos
	CCPoint getUpPos();
	//�±�Ե��pos
	CCPoint geBottomPos();
public:
	//����Ч��
	void showSelfEffect(float dt);
	void showSelfEffectCallBack();

	//��ײЧ��
	void showCollideEffect();
	//��̤Ч��
	void showLandEffect(CCPoint pPos=CCPointZero);
	//��ըЧ��
	void showBombEffect(CCPoint pPos=CCPointZero);

	//����������͵�box
	void changeToOthers(int iType);
	//����Լ�Ϊȥ��״̬
	void remove();
	//�����ڲ�״̬
	void reset();
	//�Ƿ�Ӧ�ñ�����
	bool shouldBeRecycle();
	//�Ƿ�Ӧ���и����ͼ�ƶ���Ч��
	bool shouldBeMoveWithMap();
	//����Ŀ��
	void flyToAim(CCNode* pAimNode);
	//�Ƿ�ɴ�Խ
	void updatePervious();
	//�Ƿ�����ظ�����
	bool isShouldInFreeArray();
	static bool isShouldInFreeArray(int iType);
protected:
	CC_SYNTHESIZE(NTMapLayer*, m_pMapLayer, MapLayer);	//��ͼ
	CC_SYNTHESIZE(CCNode*, m_pAimNode, AimNode);		//Ŀ��
	CC_SYNTHESIZE(int, m_iType, Type);					//����
	CC_SYNTHESIZE(bool, m_bIsFlyToDie, IsFlyToDie);		//flyToDie״̬
	CC_SYNTHESIZE(bool, m_bIsRemove, IsRemove);			//ȥ��״̬
	CC_SYNTHESIZE(bool, m_bIsPervious, IsPervious);		//�Ƿ�ɴ�Խ
	CC_SYNTHESIZE(float, m_fSpeedScale, SpeedScale);	//��Ե�·���ٶȱ�����Ĭ����1
	CC_SYNTHESIZE(bool, m_bIsGiveCoin, IsGiveCoin);	//��Ե�·���ٶȱ�����Ĭ����1
//====================================================================================//
private:
	static NTBox* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame, int iType);
	static const char* getTypeName(int iType);
public:
	virtual void initData(int iType);
	void initEffect();
private:
	void updateForMoveToAim(float dt);
	void draw();
//====================================================================================//
};

#endif // _H_NTBOX_H_
