
/********************************************************************
 *    文件名  :    NTGAMESAVE.CPP
 *    作者    :    cy
 *    创建时间:    2013/7/3 17:21
 *    文件描述:
 *********************************************************************/
#include "NTGameSave.h"
#include "NTUtility.h"
using namespace std;

USING_NS_CC;

NTGameSave* NTGameSave::_sharedContext = NULL;
NTGameSave* NTGameSave::sharedGameSave() {
    if(_sharedContext == NULL) {
        _sharedContext = new NTGameSave;
        _sharedContext->init();
		
    }
    return _sharedContext;
}

void NTGameSave::purgeGameSave() {
    CC_SAFE_DELETE(_sharedContext);
}

bool NTGameSave::init() {
    bool bRet = false;
    do {
		isSound=1;
    } while(0);
    return bRet;
}

void NTGameSave::setMusicSwitch(bool pMusic){
	if(pMusic){
		saveDataByKeyValue(_GS_MUSIC, 0, true);
	}else{
		saveDataByKeyValue(_GS_MUSIC, 1, true);
	}
}

bool NTGameSave::getMusicSwitch(){
	if(loadDataByKey(_GS_MUSIC)==1){
		return false;
	}else{
		return true;
	}
}

void NTGameSave::setSoundSwitch(bool pSound){
	if(pSound){
		saveDataByKeyValue(_GS_SOUND, 0, true);
	}else{
		saveDataByKeyValue(_GS_SOUND, 1, true);
	}
}

bool NTGameSave::getSoundSwitch(){
	if(loadDataByKey(_GS_SOUND)==1){
		return false;
	}else{
		return true;
	}
}


void NTGameSave::updateBuyGame( bool bVal )
{
	int nVal;
	if(bVal){
		nVal=1;
	}else{
		nVal=0;
	}
	saveDataByKeyValue(_GS_BUY_GAME, nVal, true);
}

bool NTGameSave::isBuyGame()
{
	if(loadDataByKey(_GS_BUY_GAME)==0){
		return false;
	}else{
		return true;
	}
}

void NTGameSave::updateValue( int nId, int nValue )
{
	saveDataByKeyValue(nId, nValue, true);
}

int NTGameSave::getDataById( int nId )
{
	if(nId == _GS_HEART){
		return loadDataByKey(nId,15);
	}
	return loadDataByKey(nId);
}

bool NTGameSave::IsGameOpen()
{
	if(loadDataByKey(_GS_OPEN)==0){
		return false;
	}else{
		return true;
	}
}

void NTGameSave::setIsGameOpen( bool bVal )
{
	if(bVal){
		saveDataByKeyValue(_GS_OPEN,1,true);
	}else{
		saveDataByKeyValue(_GS_OPEN,0,true);
	}
}

void NTGameSave::updateHeroSelect( int nVal )
{
	saveDataByKeyValue(_GS_HERO_SELECT,nVal,true);
}

int NTGameSave::getHeroSelect()
{
	return loadDataByKey(_GS_HERO_SELECT);
}

void NTGameSave::updateHeroPet( int nVal )
{
	saveDataByKeyValue(_GS_PET_SELECT,nVal,true);
}

int NTGameSave::getHeroPet()
{
	return loadDataByKey(_GS_PET_SELECT);
}

void NTGameSave::updateBuyHero( int nId, bool nVal )
{
	if(nId>=_GS_HERO_IS_BUY_1 && nId<=_GS_HERO_IS_BUY_3){
		if(nVal){
			saveDataByKeyValue(nId, 1, true);
		}else{
			saveDataByKeyValue(nId, 0, true);
		}
	}
}

bool NTGameSave::isBoughtTheHero( int nId )
{
	if(nId>=_GS_HERO_IS_BUY_1 && nId<=_GS_HERO_IS_BUY_3){
		if(loadDataByKey(nId)==1){
			return true;
		}else{
			return false;
		}
	}
	return false;
}
//购买爱心
void NTGameSave::updataBuyheart(int nId,bool nVal)
{
	if(nVal){
		saveDataByKeyValue(nId, 1, true);
	}else{
		saveDataByKeyValue(nId, 0, true);
	}
}

//购买加速
void NTGameSave::updateBuyjiaSu(int nId,bool nVal)
{
	if(nVal){
		saveDataByKeyValue(nId, 1, true);
	}else{
		saveDataByKeyValue(nId, 0, true);
	}
}
//够买加速道具
void NTGameSave::updateBuyPet( int nId, bool nVal )
{
	if(nId>=_GS_PET_IS_BUY_1 && nId<=_GS_PET_IS_BUY_3){
		if(nVal){
			saveDataByKeyValue(nId, 1, true);
		}else{
			saveDataByKeyValue(nId, 0, true);
		}
	}
}

bool NTGameSave::isBoughtThePet( int nId )
{
	if(nId>=_GS_PET_IS_BUY_1 && nId<=_GS_PET_IS_BUY_3){
		if(loadDataByKey(nId)==1){
			return true;
		}else{
			return false;
		}
	}
	return false;
}

int NTGameSave::getCurSysDay()
{
	unsigned long long timestamp = time(NULL);
	struct tm *ptm = localtime((time_t*)&timestamp);
	return ptm->tm_yday;
}

int NTGameSave::getSignDay()
{
	 int curSysDay = getCurSysDay();
	 int nDay = getDataById(_GS_SIGN_DAY);
	 if(curSysDay - getDataById(_GS_SIGN_LASTTIME) == 1){
		 nDay += 1; 
	 }else if(curSysDay - getDataById(_GS_SIGN_LASTTIME) == 0){
		 nDay = -1;
	 }else{
		 nDay = 0;
	 }
	 int nVal = nDay;
	 if(nDay < 0){
		 nDay = 0;
	 }else if(nDay >7){
		 nDay = 0;
		 nVal = nDay;
	 }
	 NTGameSave::sharedGameSave()->updateValue(_GS_SIGN_DAY,nDay);
	 NTGameSave::sharedGameSave()->updateValue(_GS_SIGN_LASTTIME,curSysDay);

	 return nVal;
}
bool NTGameSave::isTaskRefresh()
{
    int curSysDay= getCurSysDay();
    if (curSysDay - getDataById(_GS_SIGN_LASTTIME) == 0) {
        CCLog("false");
        return false;
    }else{
        CCLog("true");
   return true; }
}


bool NTGameSave::IsRegister()
{
	
	if(loadDataByKey(_GS_REGISTER) == 0){
		return false;
	}else{
		return true;
	}
}

void NTGameSave::setRegister( bool val )
{
	if(val)
		saveDataByKeyValue(_GS_REGISTER,1,true);
	else{
		saveDataByKeyValue(_GS_REGISTER,0,true);
	}
}
