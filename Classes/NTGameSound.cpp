#include "NTGameSound.h"
#include "NTGameSave.h"

using namespace CocosDenshion;
USING_NS_CC;



NTGameSound* NTGameSound::_sharedSound = NULL;

NTGameSound::NTGameSound(void)
{
	soundEnd=true;

}


NTGameSound::~NTGameSound(void)
{
	CC_SAFE_RELEASE(pPlayer);
}

NTGameSound* NTGameSound::sharedEngine() {
	if(_sharedSound  == NULL) {
		_sharedSound  = new NTGameSound;
		_sharedSound->init();
	}
	return _sharedSound;
}
bool NTGameSound::init()
{
	initTimesCount();
	initSoundArray();
	this->preloadBackgroundMusic("sound/backgroud.ogg");
    this->preloadBackgroundMusic("sound/bgm_lobby.ogg");
    this->preloadBackgroundMusic("sound/bgm_super.ogg");

//	this->preloadBackgroundMusic("sound/country_shop.ogg");
//	this->preloadEffect("sound/button.ogg");
//	this->preloadEffect("sound/gameWin.ogg");
// 	this->preloadEffect("sound/hero_selected.ogg");
// 	this->preloadEffect("sound/hero_attack.ogg");
// 	this->preloadEffect("sound/hero_upgrade.ogg");
// 	this->preloadEffect("sound/skill_bomb.ogg");
// 	this->preloadEffect("sound/skill_cleanup.ogg");
// 	this->preloadEffect("sound/skill_doubleattack.ogg");
// 	this->preloadEffect("sound/tower_upgrade.ogg");
// 	this->preloadEffect("sound/banana_attack.ogg");
// 	this->preloadEffect("sound/tomato_attack.ogg");
// 	this->preloadEffect("sound/mushroom_attack.ogg");
// 	this->preloadEffect("sound/gameLose.mp3");
// 	this->preloadEffect("sound/map_flower.mp3");
// 	this->preloadEffect("sound/map_step.mp3");

	//加入哆啦咪声音2013.07.29
// 	this->preloadEffect("sound/01.mp3");
// 	this->preloadEffect("sound/02.mp3");
// 	this->preloadEffect("sound/03.mp3");
// 
// 	//大招声音
// 	this->preloadEffect("sound/big_skill.mp3");

	this->preloadEffect("sound/break.ogg");
	this->preloadEffect("sound/count.ogg");//过关
	this->preloadEffect("sound/eat_gold.ogg");//吃金币的
	this->preloadEffect("sound/eat_prop.ogg");//吃收益
	this->preloadEffect("sound/fly_begin.ogg");//开始飞
	this->preloadEffect("sound/fly_end.ogg");//飞完了
	this->preloadEffect("sound/heart.ogg");//心
	this->preloadEffect("sound/hero_show.ogg");//出场
	this->preloadEffect("sound/jump_boy.ogg");//男男跳
	this->preloadEffect("sound/jump_girl.ogg");//女女跳
	this->preloadEffect("sound/plane.ogg");//飞机来了
	this->preloadEffect("sound/press.ogg");//按键
	this->preloadEffect("sound/sfx_hit.ogg");//撞上了
	this->preloadEffect("sound/sfx_wing.ogg");
	this->preloadEffect("sound/slide.ogg");//
	return true;
}

void NTGameSound::playBackgroundMusic(const char *name, bool isLoop,int isss )
{	if (isss==1)
	{
		SimpleAudioEngine::playBackgroundMusic(name,isLoop);
		if(!isAudioOpen()){
			SimpleAudioEngine::setBackgroundMusicVolume(0);
			CCLog("bbbbbbbbbbbbbbbbbbbbbbbbb");
		}
	}
	
}


void NTGameSound::playEffectById(int sId, bool pReal,int isss)
{
	if (isss==1)
	{
		//CCLog("ssssssssssssssssssssssssssssssssssssss");
		if(!soundEnd)
			return;

		if(!isAudioOpen()){
			return;
		}

		if(!pReal){
			addSoundToArray(sId);
			return;
		}
        if (sId!=11) {
             CCLog("playEffectById:%d",sId);
        }
       
		switch(sId)
		{
		case SOUND_MAP_FLOWER:
			this->playEffect("sound/break.ogg");
			break;
		case SOUND_MAP_STEP:
			this->playEffect("sound/count.ogg");
			break;
		case SOUND_GAME_LOSE:
			this->playEffect("sound/eat_gold.ogg");
			break;
		case SOUND_BUTTON:
			this->playEffect("sound/eat_prop.ogg");//
			break;
		case SOUND_GAME_WIN:
			this->playEffect("sound/fly_begin.ogg");
			break;
		case SOUND_HERO_SELECTED:
			this->playEffect("sound/fly_end.ogg");
			break;
		case SOUND_HERO_UPGRADE:
			this->playEffect("sound/heart.ogg");
			break;
		case SOUND_TOWER_UPGRADE:
			this->playEffect("sound/hero_show.ogg");
			break;
		case SOUND_SKILL_CLEANUP:
			this->playEffect("sound/jump_boy.ogg");
			break;
		case SOUND_SKILL_DOUBLEATT:
			this->playEffect("sound/jump_girl.ogg");
			break;
		case SOUND_SKILL_BOMB:
			this->playEffect("sound/plane.ogg");
			break;
		case SOUND_MONSTER_DIE:
			this->playEffect("sound/press.mp3");
			break;
		case SOUND_MUSHROOM_ATTACK:
			this->playEffect("sound/sfx_hit.ogg");
			break;
		case SOUND_TOMATO_ATTACK:
			this->playEffect("sound/sfx_wing.ogg");
			break;
			// 		case SOUND_BANANA_ATTACK:
			// 			this->playEffect("sound/slide.ogg");
			// 		break;
			// 		case SOUND_HERO_ATTACK:
			// 			this->playEffect("sound/hero_attack.ogg");
			// 		break;
			// 		case SOUND_SPLASH:
			// 			this->playEffect("sound/country_shop.ogg");
			// 		break;
			//加入哆啦咪
			// 		case SOUND_GIFT_1:
			// 			this->playEffect("sound/01.mp3");
			// 			break;
			// 		case SOUND_GIFT_2:
			// 			this->playEffect("sound/02.mp3");
			// 			break;
			// 		case SOUND_GIFT_3:
			// 			this->playEffect("sound/03.mp3");
			// 			break;
			// 		case SOUND_BIG_SKILL:
			// 			this->playEffect("sound/big_skill.mp3");
			// 			break;
		default:
			break;
		}
	}
}

void NTGameSound::closeAll()
{
	/*pauseBackgroundMusic();*/
	SimpleAudioEngine::setBackgroundMusicVolume(0.0f);
	stopAllEffects();
	NTGameSave::sharedGameSave()->setMusicSwitch(false);
	NTGameSave::sharedGameSave()->setSoundSwitch(false);
	CCLog("guanbiyinyue+++++++++");
}

void NTGameSound::openAll()
{
	if(NTGameSave::sharedGameSave()->isSound==1){
		/*resumeBackgroundMusic();*/
		SimpleAudioEngine::setBackgroundMusicVolume(0.5f);
		NTGameSave::sharedGameSave()->setMusicSwitch(true);
		NTGameSave::sharedGameSave()->setSoundSwitch(true);
		CCLog("kaiqiyinyue-------");
	}

	
}

void NTGameSound::switchAudio()
{
	if(isAudioOpen()){
		closeAll();
	}else{
		openAll();
	}
}
//得到声音的是否开启
bool NTGameSound::isAudioOpen()
{
	return NTGameSave::sharedGameSave()->getMusicSwitch();
}

void NTGameSound::addSoundToArray( int nId )
{
	if(m_iSoundArray[nId][0]+1<=m_iSoundArray[nId][1]){
		m_iSoundArray[nId][0]++;
	}
}
//根据id播放音乐文件
void NTGameSound::playSoundInArray(float dt)
{
	updateTimesCount(dt);
	for (unsigned int i=0; i<SOUND_MAX; i++)
	{
		for(unsigned int j=0; j<m_iSoundArray[i][0]; j++){
			
			if(m_fTimesCount[i]<m_iSoundArray[i][2]){
				break;
			}else{
				m_fTimesCount[i]=0;
			}
			playEffectById(i,true,NTGameSave::sharedGameSave()->isSound);
		}
	}

	initSoundArray();
}

void NTGameSound::initSoundArray()
{
	for (unsigned int i=0; i<SOUND_MAX; i++)
	{
		m_iSoundArray[i][0] = 0;	//当前数量
		m_iSoundArray[i][1] = 2;	//最大数量
		m_iSoundArray[i][2] = 100;  //播放时间
	}
	m_iSoundArray[SOUND_TOMATO_ATTACK][2] = 200;
	m_iSoundArray[SOUND_HERO_SELECTED][2] = 1000;
	m_iSoundArray[SOUND_MONSTER_DIE][2] = 400;
//	m_iSoundArray[SOUND_BIG_SKILL][2] = 400;
}


void NTGameSound::initPlayer(CCNode* pParent)
{
	pPlayer = NTSoundPlayer::create();
	pPlayer->start();
	pParent->addChild(pPlayer ,-1000);
}

void NTGameSound::initTimesCount()
{
	for(unsigned int i=0; i<SOUND_MAX; i++){
		m_fTimesCount[i]=0;
	}
}

void NTGameSound::updateTimesCount( float dt )
{
	for(unsigned int i=0; i<SOUND_MAX; i++){
		m_fTimesCount[i]+=dt*1000;
	}
}

//
void NTSoundPlayer::updateSound( float dt )
{
	NTGameSound::sharedEngine()->playSoundInArray(dt);
}
//给播放者添加个计时器
void NTSoundPlayer::start()
{
	schedule(schedule_selector(NTSoundPlayer::updateSound));
}
