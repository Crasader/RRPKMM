
/********************************************************************
 *    文件名  :    NTUTILITY.H
 *    作者    :    cy
 *    创建时间:    2013/3/9 11:21
 *    文件描述:    常用方法集
 *********************************************************************/

#ifndef _H_NTUTILITY_H_
#define _H_NTUTILITY_H_

#include "cocos2d.h"
#include "DataBase64.h"
#include <string>
#include "NTGameSave.h"


using namespace std;

USING_NS_CC;

#define encrypt_data 1

inline void cclogCurTime(){
	struct cc_timeval now; 
	CCTime::gettimeofdayCocos2d(&now, NULL); 
	CCLog("%d",now.tv_sec * 1000 + now.tv_usec / 1000);
}

inline void saveDataByKeyValue(int iKey, string sValue, bool bSaveAtOnce=false){ 
	char buffer[32];
	sprintf(buffer, "ntparkour%d", iKey);
#if encrypt_data
	string sKey = saveData(reinterpret_cast<const unsigned char*>(sValue.c_str()), sValue.length());
#else
	string sKey = sValue;
#endif
	CCUserDefault::sharedUserDefault()->setStringForKey(buffer, sKey);

	if(bSaveAtOnce) {
		CCUserDefault::sharedUserDefault()->flush();
	}
}

inline void saveDataByKeyLongValue(int iKey, long nVal, bool bSaveAtOnce=false){
	char buffer[32];
	sprintf(buffer, "%ld", nVal);
	saveDataByKeyValue(iKey, buffer, bSaveAtOnce);
}

inline void saveDataByKeyValue(int iKey, int nVal, bool bSaveAtOnce=false){
	char buffer[32];
	sprintf(buffer, "%d", nVal);
	saveDataByKeyValue(iKey, buffer, bSaveAtOnce);
}

inline int loadDataByKey(int iKey, int defaultValue=0){
	char buffer[32];
	sprintf(buffer, "ntparkour%d", iKey);

	string s = CCUserDefault::sharedUserDefault()->getStringForKey(buffer);
	if(s == "") {
		return defaultValue;
	}
#if encrypt_data
	string parseKey = parseData(s);
	return atoi(parseKey.c_str());	
#else
	return atoi(s.c_str());
#endif
}
#endif // _H_NTUTILITY_H_
