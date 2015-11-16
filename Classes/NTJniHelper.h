
/********************************************************************
 *    文件名  :    NTJNIHELPER.H
 *    作者    :    cy
 *    创建时间:    2013/1/30 9:07
 *    文件描述:    jni管理者
 *********************************************************************/

#ifndef _H_NTJNIHELPER_H_
#define _H_NTJNIHELPER_H_

#include "cocos2d.h"
class NTRenameDelegate {
public:
	virtual void registerMyName(std::string strName) = 0;
};
class NTJniHelper {

public:
	static NTJniHelper* sharedJniHelper();
	static void purgeSharedJniHelper();

public: // jni相关
	
	
	void registerName();

	void showTipsInAndroid(const char* pStr);

	void toRegisterName(std::string strName);

	
private:
	bool init();
	static NTJniHelper* m_pShare;
	CC_SYNTHESIZE(NTRenameDelegate*,m_pRenameDelegate,RenameDelegate);

};

#endif // _H_NTJNIHELPER_H_