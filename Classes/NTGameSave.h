
/********************************************************************
 *    Œƒº˛√˚  :    NTGAMESAVE.H
 *    ◊˜’ﬂ    :    cy
 *    ¥¥Ω® ±º‰:    2013/7/3 17:20
 *    Œƒº˛√Ë ˆ:    ”Œœ∑¥Êµµ ˝æ›
 *********************************************************************/

#ifndef _H_NTGAMESAVE_H_
#define _H_NTGAMESAVE_H_

#include "cocos2d.h"


enum {

	_GS_MUSIC,
	_GS_SOUND,

	_GS_FIRST_IN_GAME,	//µ⁄“ª¥ŒΩ¯»Î”Œœ∑

	_GS_BUY_GAME,	//º§ªÓ”Œœ∑

	_GS_MAX_SCORE,	//◊Ó∏ﬂ∑÷

	_GS_OPEN,	//√ø¥Œø™∆Ù”Œœ∑µƒ±Íº«£¨◊ˆ≈≈––∞Ò±‰∂Ø”√

	_GS_HEART,	//∞Æ–ƒ

	_GS_GOLD,	//Ω±“
	_GS_JIASU = 8, //º”ÀŸ
	//”¢–€ «∑Ò±ªπ∫¬Ú
	_GS_HERO_IS_BUY_1,
	_GS_HERO_IS_BUY_2,
	_GS_HERO_IS_BUY_3,
	//≥ËŒÔ «∑Ò±ªπ∫¬Ú
	_GS_PET_IS_BUY_1,
	_GS_PET_IS_BUY_2,
	_GS_PET_IS_BUY_3,
	//µ±«∞—°‘Ò”¢–€
	_GS_HERO_SELECT,
	//µ±«∞—°‘Òµƒ≥ËŒÔ
	_GS_PET_SELECT,
	//”¢–€ ˝æ›
	_GS_HERO1_LEVEL,
	_GS_HERO2_LEVEL,
	_GS_HERO3_LEVEL,
	//≥ËŒÔ ˝æ›
	_GS_PET1_LEVEL,
	_GS_PET2_LEVEL,
	_GS_PET3_LEVEL,

	//“˝µº
	_GS_GUIDE_JUMP,		//“˝µºÃ¯‘æ
	_GS_GUIDE_SLIDE,	//“˝µºœ¬ª¨

	//«©µΩ ±º‰
	_GS_SIGN_LASTTIME,
	_GS_SIGN_DAY,
	_GS_SIGN_TIMES,
	_GS_REGISTER,
    
    _GS_HEART_COUNTLESS,
    //Jerry--Task
    _GS_FIRST_TASK,
    _GS_TASKONE,
    _GS_TASKTWO,
    _GS_TASKTHREE,
    _GS_TASKONE_FINISH,
    _GS_TASKTWO_FINISH,
    _GS_TASKTHREE_FINISH,
    _GS_SCORE,
    _GS_GOLDMODE_TIMES,
    _GS_HEART_USE,
    _GS_BOX_HIT,
    _GS_TASK_COMPLISH,
    _GS_SIGN,
	_GS_MAX,

};

class NTGameSave {

public:
	static NTGameSave* sharedGameSave();
	static void purgeGameSave();

private:
	bool init();
private:
	static NTGameSave* _sharedContext;
public :
	// …˘“Ùøÿ÷∆
	void setMusicSwitch(bool pMusic);
	bool getMusicSwitch();
	void setSoundSwitch(bool pSound);
	bool getSoundSwitch();
public:
	void updateBuyGame(bool bVal);
	bool isBuyGame();
public:
	void updateValue(int nId, int nValue);
	int getDataById(int nId);

	bool IsGameOpen();
	void setIsGameOpen(bool bVal);

	//—°‘Òµƒ”¢–€
public:
	void updateHeroSelect(int nVal);
	int getHeroSelect();

	//—°‘Òµƒ≥ËŒÔ
public:
	void updateHeroPet(int nVal);
	int getHeroPet();

	//”¢–€ «∑Ò±ªπ∫¬Ú
public:
	void updateBuyHero(int nId, bool nVal);
	bool isBoughtTheHero(int nId);
public:
	//–ﬁ∏ƒ---  ∞Æ–ƒ
	void updataBuyheart(int nId,bool nVal);
	//–ﬁ∏ƒ--- º”ÀŸµ¿æﬂ
	void updateBuyjiaSu(int n,bool isBuy);

	//≥ËŒÔ «∑Ò±ªπ∫¬Ú
public:
	void updateBuyPet(int nId, bool nVal);
	bool isBoughtThePet(int nId);

	//-------  ªÒ»°œµÕ≥ÃÏ ˝£¨«©µΩ”√
	int getCurSysDay();
	int getSignDay();
    
    //Jerry--Task
    bool isTaskRefresh();

	//-------   «∑Ò◊¢≤·¡À√˚◊÷
	bool IsRegister();
	void setRegister(bool val);

	 int isSound;
};

#endif // _H_NTGAMESAVE_H_