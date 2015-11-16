#ifndef __ASSISTANT_H__
#define __ASSISTANT_H__

#include "cocos2d.h"
#include "NTGameSave.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

using namespace cocos2d;

#define QH_RANDOM(min, max) min+rand()%(max-min)

/*#define CG_SDK_UNKNOWN      0
#define CG_SDK_CM           1
#define CG_SDK_MM           2
#define CG_SDK_DX           3
#define CG_SDK_CMMUSIC		4
#define CG_SDK_CMANDMUSIC	5

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// ��ʱ���ݰ�׿�ı�����Ķ���
#define CG_SDK_MODE         CG_SDK_CMANDMUSIC // ֻ��android ��Ч ��������Ϊ0
#else
#define CG_SDK_MODE         CG_SDK_UNKNOWN // ֻ��android ��Ч ��������Ϊ0
#endif*/

typedef void (CCObject::*Activate_CallFunc)();
typedef void (CCObject::*SYSDLG_CallFunc)(int);
typedef void (CCObject::*SYSDLG_CallFuncIS)(int, std::string billing);
const int SYS_DLG_NEGATIVE_BTN = 1;
const int SYS_DLG_POSITIVE_BTN = 2;

struct SDialogContent
{
    CCObject* target;
    SYSDLG_CallFunc func;
};

struct SActivateContent
{
    CCObject* target;
    Activate_CallFunc func;
};

extern void ShowSysDialog(const char *title, const char *msg, const char* negative, const char* positive, CCObject* target, SYSDLG_CallFunc pFunc);
//������Ʒ
extern void buyShopItem(CCObject* target, SYSDLG_CallFunc pFunc, int index);
//������Ʒ�ɹ�
extern void buyShopItemSucess(int index);

extern "C"
{     
    void android_ShowSysDialog(const char *title, const char *msg, const char* negative, const char* positive, CCObject* target, SYSDLG_CallFunc pFunc);
	void android_ShortText(const char* text);
    void buyItem_Android(int index);
}



#endif // __ASSISTANT_H__
