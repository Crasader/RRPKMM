
#ifndef __NTEFFECTLAYER__
#define __NTEFFECTLAYER__

#include "cocos2d.h"
#include "NTConstants.h"
#include "NTMapLayer.h"

USING_NS_CC;

enum{
	EFFECT_EAT_GOLD,
	EFFECT_WOOD_BOMB,
	EFFECT_STONE_BOMB,
	EFFECT_DIAMOND_BOMB,
	EFFECT_GLASS_BOMB,
	EFFECT_SMOKE,
	EFFECT_BUFF_BOMB
};

enum{
	PARTICLE_BATCH_WOOD1,
	PARTICLE_BATCH_WOOD2,
	PARTICLE_BATCH_STONE1,
	PARTICLE_BATCH_STONE2,
	PARTICLE_BATCH_EAT_SMALL_GOLD1,
	PARTICLE_BATCH_EAT_SMALL_GOLD2,
	PARTICLE_BATCH_EAT_SMALL_GOLD3,
	PARTICLE_BATCH_EAT_SMALL_GOLD4,
	PARTICLE_BATCH_GLASS_BREAK,
	PARTICLE_BATCH_SMOKE,
	PARTICLE_BATCH_BUFF1,
	PARTICLE_BATCH_BUFF2,
	PARTICLE_BATCH_MAX
};

class NTMapLayer;

class NTEffectLayer : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(NTEffectLayer);
	bool init();
    void onEnter();
	void onExit();
	void onEnterTransitionDidFinish();
private:
	CCParticleBatchNode* m_pParticleBatchs[PARTICLE_BATCH_MAX];
protected:
	CC_SYNTHESIZE(NTMapLayer*, m_pMapLayer, MapLayer);
private:
	void initData();
	void callBackToRemoveAnySender(CCNode* pSender);
public:
	void playAnimateForBomb(CCPoint pPos, int iType);
	CCParticleSystemQuad* getParticleFromBatch(CCParticleBatchNode* pBatchNode, const char* pListName=NULL);
	void update(float dt);
};
#endif /* defined(__NTEFFECTLAYER__) */
