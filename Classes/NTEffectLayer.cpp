
#include "NTEffectLayer.h"
#include "AnimatePacker.h"

const char* name[PARTICLE_BATCH_MAX] = {
	"lz/woodpiece1.png", "lz/woodpiece2.png","lz/stone_1.png", "lz/stone_2.png",
	"lz/star2.png", "lz/stars2.png","lz/star3a.png", "lz/gq.png",
	"lz/glasspiece1.png", 
	"lz/cloud.png",
	"lz/gold.png", "lz/fire.png"
};
const char* namePlist[PARTICLE_BATCH_MAX] = {
	"lz/woodbreak.plist", "lz/woodbreak2.plist","lz/stonebreak.plist", "lz/stonebreak2.plist",
	"lz/eatgolda1.plist", "lz/eatgolda2.plist","lz/eatgolda3.plist", "lz/eatgolda4.plist",
	"lz/glassbreak.plist",
	"lz/smoke1.plist",
	"lz/gold1.plist", "lz/gold2.plist"
};
const int iParticleCount[PARTICLE_BATCH_MAX] = {
	4,	4,	4,	4,
	4,	4,	4,	4,
	2,
	20,
	4, 4
};

bool NTEffectLayer::init()
{
	bool bRet = false;
	do 
	{        
		CC_BREAK_IF(!(CCLayer::init()));
		bRet = true;
	} while(0);
	return bRet;
}

void NTEffectLayer::onEnter()
{
	CCLayer::onEnter();
}

void NTEffectLayer::onExit()
{
	CCLayer::onExit();
}

void NTEffectLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	initData();
}

void NTEffectLayer::initData()
{
	m_pMapLayer = NULL;

	for(unsigned int i=0; i<PARTICLE_BATCH_MAX; i++){
		m_pParticleBatchs[i] = CCParticleBatchNode::create(name[i]);
		this->addChild(m_pParticleBatchs[i]);
		for(unsigned int j=0; j<iParticleCount[i]; j++){
			CCParticleSystemQuad* pParticle = CCParticleSystemQuad::create(namePlist[i]);
			pParticle->stopSystem();
			m_pParticleBatchs[i]->addChild(pParticle);
		}
	}
}


void NTEffectLayer::callBackToRemoveAnySender( CCNode* pSender )
{
	pSender->removeFromParentAndCleanup(true);
}

void NTEffectLayer::playAnimateForBomb( CCPoint pPos, int iType )
{
	switch(iType)
	{
		case EFFECT_WOOD_BOMB:
			{
				CCParticleSystemQuad* pParticle1 = getParticleFromBatch(
					m_pParticleBatchs[PARTICLE_BATCH_WOOD1], namePlist[PARTICLE_BATCH_WOOD1]);
				pParticle1->setPosition(pPos);
				pParticle1->setEmissionRate(50);
				pParticle1->resetSystem();

				CCParticleSystemQuad* pParticle2 = getParticleFromBatch(
					m_pParticleBatchs[PARTICLE_BATCH_WOOD2], namePlist[PARTICLE_BATCH_WOOD2]);
				pParticle2->setPosition(pPos);
				pParticle2->setEmissionRate(50);
				pParticle2->resetSystem();

			};break;
		case EFFECT_STONE_BOMB:
			{
				CCParticleSystemQuad* pParticle1 = getParticleFromBatch(
					m_pParticleBatchs[PARTICLE_BATCH_STONE1], namePlist[PARTICLE_BATCH_STONE1]);
				pParticle1->setPosition(pPos);
				pParticle1->setEmissionRate(50);
				pParticle1->resetSystem();

				CCParticleSystemQuad* pParticle2 = getParticleFromBatch(
					m_pParticleBatchs[PARTICLE_BATCH_STONE2], namePlist[PARTICLE_BATCH_STONE2]);
				pParticle2->setPosition(pPos);
				pParticle1->setEmissionRate(50);
				pParticle2->resetSystem();

			};break;
		case EFFECT_BUFF_BOMB:
			{
				for(unsigned int i=PARTICLE_BATCH_EAT_SMALL_GOLD1; i<=PARTICLE_BATCH_EAT_SMALL_GOLD4; i++){
					CCParticleSystemQuad* pParticle = getParticleFromBatch(
						m_pParticleBatchs[i], NULL);
					if(pParticle!=NULL){
						pParticle->setPosition(pPos);
						pParticle->resetSystem();
					}
				}

			};break;
		case EFFECT_GLASS_BOMB:
			{
				CCParticleSystemQuad* pParticle = getParticleFromBatch(
					m_pParticleBatchs[PARTICLE_BATCH_GLASS_BREAK], namePlist[PARTICLE_BATCH_GLASS_BREAK]);
				if(pParticle!=NULL){
					pParticle->setPosition(pPos);
					pParticle->setEmissionRate(50);
					pParticle->resetSystem();
				}
			};break;
		case EFFECT_SMOKE:
			{
				CCParticleSystemQuad* pParticle = getParticleFromBatch(
					m_pParticleBatchs[PARTICLE_BATCH_SMOKE], NULL);
				if(pParticle!=NULL){
					pParticle->setPosition(pPos);
					pParticle->resetSystem();
				}
			};break;
		case EFFECT_EAT_GOLD:
			{
				for(unsigned int i=PARTICLE_BATCH_BUFF1; i<=PARTICLE_BATCH_BUFF2; i++){
					CCParticleSystemQuad* pParticle = getParticleFromBatch(
						m_pParticleBatchs[i], NULL);
					if(pParticle!=NULL){
						pParticle->setPosition(pPos);
						pParticle->resetSystem();
					}
				}
			};break;
	}
}


CCParticleSystemQuad* NTEffectLayer::getParticleFromBatch( CCParticleBatchNode* pBatchNode, const char* pListName)
{
	CCArray* pArray = pBatchNode->getChildren();
	CCObject* pObj;
	CCParticleSystemQuad* pParticle=NULL;
	CCARRAY_FOREACH(pArray, pObj){
		pParticle = (CCParticleSystemQuad*)pObj;
		if(!pParticle->isActive()){
			return pParticle;
		}
	}

	if(pListName==NULL){
		return NULL;
	}

	if(pParticle==NULL){
		pParticle = CCParticleSystemQuad::create(pListName);
		pBatchNode->addChild(pParticle);
		return pParticle;
	}
}


void NTEffectLayer::update( float dt )
{

}

















