
/********************************************************************
 *    文件名  :    NTJNIHELPER.CPP
 *    作者    :    cy
 *    创建时间:    2013/1/30 9:09
 *    文件描述:    jni 管理者
 *********************************************************************/
#include "NTJniHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "../proj.android/jni/hellocpp/NTJni.h"
#include "platform/android/jni/JniHelper.h"
#endif

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>




extern "C" {
	void Java_com_nt_common_NTJniHelper_toRegisterName(JNIEnv *env, jobject thiz, jstring strName) {
		const char *pkgName = env->GetStringUTFChars(strName, NULL);

		NTJniHelper::sharedJniHelper()->toRegisterName(pkgName);

		env->ReleaseStringUTFChars(strName,pkgName);
		
		
	}
}
#endif

NTJniHelper* NTJniHelper::m_pShare = NULL;
NTJniHelper* NTJniHelper::sharedJniHelper() {
    if (m_pShare == NULL) {
        m_pShare = new NTJniHelper();
        if (!m_pShare || !m_pShare->init()) {
            CC_SAFE_DELETE(m_pShare);
        }
    }
    return m_pShare;
}

void NTJniHelper::purgeSharedJniHelper() {
    CC_SAFE_DELETE(m_pShare);
}

bool NTJniHelper::init() {
    bool bRet = false;
    do {
        m_pRenameDelegate = NULL;
        bRet = true;
    } while (0);

    return bRet;
}


void NTJniHelper::registerName() {
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    aRegister();
// #endif
}

void NTJniHelper::showTipsInAndroid( const char* pStr ) {
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//     if(pStr != NULL) {
//         showTips(pStr);
//     }
// #endif
}



void NTJniHelper::toRegisterName( std::string strName )
{
	//CCLog(strName.c_str());
	if(m_pRenameDelegate){
		m_pRenameDelegate->registerMyName(strName);
	}
}