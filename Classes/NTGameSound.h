#ifndef _H_NTGAMESOUND_H_
#define _H_NTGAMESOUND_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

enum
{
	SOUND_START=-1,
	SOUND_BUTTON,//0
	SOUND_HERO_SELECTED,//1
	SOUND_HERO_UPGRADE,//2
	SOUND_TOWER_UPGRADE,//3
	SOUND_SKILL_CLEANUP,//4
	SOUND_SKILL_DOUBLEATT,//5
	SOUND_SKILL_BOMB,//6
	SOUND_MONSTER_DIE,//7
	SOUND_TOMATO_ATTACK,//8
	SOUND_MUSHROOM_ATTACK,//9
//	SOUND_BANANA_ATTACK,
//	SOUND_HERO_ATTACK,
	SOUND_GAME_WIN,//10
	SOUND_GAME_LOSE,//11
	SOUND_MAP_STEP,//12
	SOUND_MAP_FLOWER,//13
//	SOUND_SPLASH,

// 	SOUND_GIFT_1,
// 	SOUND_GIFT_2,
// 	SOUND_GIFT_3,
	
//	SOUND_BIG_SKILL,
	
	SOUND_MAX
};

class NTSoundPlayer;

class NTGameSound :public CocosDenshion::SimpleAudioEngine
{
public:
	NTGameSound(void);
	~NTGameSound(void);
	bool init();

	static NTGameSound* sharedEngine();

	void purge();
	void playEffectById(int sId, bool pReal,int issss);
	void playBackgroundMusic(const char *name, bool isLoop,int isss);
	bool soundEnd;
	void closeAll();
	void openAll();
	void switchAudio();
	bool isAudioOpen();
	
	float m_fTimesCount[SOUND_MAX];
	void initTimesCount();
	void updateTimesCount(float dt);

	int m_iSoundArray[SOUND_MAX][3];//0当前数量，1最大数量，2播放时间
	NTSoundPlayer* pPlayer;
	void initSoundArray();
	void initPlayer(CCNode* pParent);
	void playSoundInArray(float dt);
	void addSoundToArray(int nId);

private:
	static NTGameSound* _sharedSound;
};

class NTSoundPlayer : public CCNode
{
public:
	CREATE_FUNC(NTSoundPlayer);
	void updateSound(float dt);
	void start();
};
#endif
