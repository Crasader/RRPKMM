#ifndef _NTMINIMAP_H_
#define _NTMINIMAP_H_

#include "cocos2d.h"

USING_NS_CC;

class NTMiniMap:public CCLayer
{
public:
	CREATE_FUNC(NTMiniMap);
	void updatePlayerPos(CCPoint pPos);
	void updateNpcPos(CCPoint pPos);
	void updatePowerBar(float fPercentAdd);
	float getPercentOfPowerBar();

private:
	CCMenu* m_pMenu;
	bool m_bIsTouchMu;

private:
	bool init();
	void onEnter();
	void onExit();
	void onEnterTransitionDidFinish();

	//�����¼�
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	//��ʼ������
	void initValues();
	//��ʼ��UI
	void initUI();
	//��·����Ч��
	void roadScrollEffect();
	void updateForRoadLine(float dt);

private:
	//����ͷ��
	CC_SYNTHESIZE(CCSprite*, m_pPlayerHead, PlayerHead);
	//NPCͷ��
	CC_SYNTHESIZE(CCSprite*, m_pNPCHead, NPCHead);
private:
	//��Ļ��Ұ��
	CCSprite* m_pScreenRect;
	//mini��·��
	CCSprite* m_pMiniRoad;
	CCSprite* m_pRoadLine[6];
	//��Ļ���
	CCPoint m_pScreenStartPos;
	//���ű���
	float m_fScreenScale;

	//������
	CCProgressTimer* m_pPowerBar;
	CCLabelAtlas* m_pPowerAtlas;
	float m_fPowerPercent;
};

#endif /*_NTMINIMAP_H_*/