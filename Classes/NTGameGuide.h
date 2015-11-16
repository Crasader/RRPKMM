
#ifndef _H_NTGAMEGUIDE_H_
#define _H_NTGAMEGUIDE_H_

#include "cocos2d.h"
#include "NTControlLayer.h"
#include "NTMessageBox.h"

class NTTileData;
class NTGameHUD;
class NTWave;
class NTTower;
class NTEnemy;

USING_NS_CC;


enum{
	GUIDE_TYPE_TAP,			//���
	GUIDE_TYPE_MOVE,		//�ƶ�
	GUIDE_TYPE_DRAW,		//����
	GUIDE_TYPE_LONG_TAP,	//����
};

#define GUIDE_ARROW_SHOW_DELAY	0.2f
#define GUIDE_ARROW_SHOW_GAP	0.15f

#define GAME_LAYER_GUIDE 1700

class NTGameGuide : public CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	CREATE_FUNC(NTGameGuide);
	~NTGameGuide();
	NTGameGuide();
	bool init();
	void onEnterTransitionDidFinish();
    void onExit();
	void onEnter();

	// default implements are used to call script callback if exist
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
public:
	CC_SYNTHESIZE(NTControlLayer*, m_pControlLayer, ControlLayer);
public:
	//��������
	CC_SYNTHESIZE(bool, m_bTouchLock, TouchLock)
private:
	//��������
	CC_SYNTHESIZE(bool, m_bGuideLock, GuideLock);
	//������ʼ��
	CC_SYNTHESIZE(CCPoint, m_pStart, TouchStart);
	//�����յ�
	CC_SYNTHESIZE(CCPoint, m_pEnd, TouchEnd);
	//������
	CC_SYNTHESIZE(CCArray*, m_pPointArray, PointArray);
	CC_SYNTHESIZE(int, m_iPointIndex, PointIndex);
	//���������Ļص�
	CC_SYNTHESIZE(CCAction*, m_pGuideOverCallBack, GuideOverCallBack);
	//����ִ�е�Layer
	CC_SYNTHESIZE(CCTouchDelegate*, m_pTouchLayer, TouchLayer);
	//ִ��ʱ��
	CC_SYNTHESIZE(float, m_pDelayTime, DelayTime);
	//��ʼ����յ��gap
	CC_SYNTHESIZE(CCPoint, m_pGap, Gap);
	//��������
	CC_SYNTHESIZE(int, m_pGuideType, GuideType);
	//gap���������point
	CC_SYNTHESIZE(CCPoint, m_pStartToAdd, StartToAdd);

	CC_SYNTHESIZE(int, m_iGuideMode, GuideMode);

	void initLightLayer();
	void initValue();

	//�ֺͼ�ͷ
	CCSprite* m_pArrow;
	CCSprite* m_pHand;
	CCSprite* m_pBlinkLight;
	void showHandAndArrow(CCPoint pPos);
	void hideHandAndArrow();


	void showMsgBox(int pType=-1);
	void messageOkCallBack( CCObject * pSender);

	//ִ������ 
	//pHud:ִ�д�����ʵ��
	//pStart:������ʼ��	
	//pEnd:�����յ�	
	//pDelayTime:����ʱ��
	//pActionCallBack:���������Ļص�
	//iGuideMode:������ģʽ
	//pPointArray:һ��������
	bool runGuide(int pType, 
		CCTouchDelegate* pTouchLayer, 
		CCPoint pStart, CCPoint pEnd, 
		float pDelayTime, 
		CCAction* pActionCallBack,
		int iGuideMode, 
		CCArray* pPointArray=NULL);

	void showGuide();
	void showTapGuide();
	void showLongTapGuide();
	void showMoveGuide();
	void showDrawGuide();
	void showGuideCallBack();
	void showTapTouch();
	void showLongTapTouch();
	void showLongTapTouchCallBack();
	void showDragTouch();
	bool changePoint(CCPoint pStart=CCPointZero);
	void updateForTouchMove(float dt);
	
	CCSpriteBatchNode* m_pArrowBatchNode;
	void initArrayBatchNode();
	void showArrowWithArrayPoint(CCArray* pArray);
	void showArrowWithArrayPointCallBack();
	void moveHandWithArrayPoint(CCArray* pArray);
	void moveHandWithArrayPointCallBack();

private:
	// chenying 2013-12-24 ����ģ��
	CCTouch* m_pVirtualTouch;
};
#endif // _H_NTGAMEGUIDE_H_
