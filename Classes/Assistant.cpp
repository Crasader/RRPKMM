#include "Assistant.h"
#include <list>

std::list<SDialogContent> g_lstContents;

SDialogContent* GetContent()
{
    if (g_lstContents.empty())
        return NULL;

    return &(g_lstContents.back());
}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    WCHAR* Utf8ToUincode(const char* utf8)
    {
        WCHAR* outstr = new WCHAR[2048];
	    memset(outstr, '\0', sizeof(WCHAR)*2048);

	    int i = 0;
	    int pos = 0;

	    while(utf8[i] != 0)
	    {
		    if ( (utf8[i] & 0x80) == 0 ) // 多字节继续检查0x20 0x10 0x08 0x04
		    {
			    outstr[pos] = utf8[i++];
		    }
		    else if ((utf8[i] & 0xE0) == 0xC0)
		    {
			    WORD temp = (BYTE)utf8[i++];
			    outstr[pos] = (temp & 0x1f) << 6; 
			    temp = (BYTE)utf8[i++];
			    outstr[pos] |= (temp & 0x3f); 

		    }
		    else if ((utf8[i] & 0xF0) == 0xE0)
		    {
			    WORD temp = (BYTE)utf8[i++];
			    outstr[pos] = (temp & 0x0f) << 12; 
			    temp = (BYTE)utf8[i++];
			    outstr[pos] |= (temp & 0x3f) << 6; 
			    temp = (BYTE)utf8[i++];
			    outstr[pos] |= (temp & 0x3f);
		    }

		    ++pos;
	    }

	    return outstr;
    }
#endif

void ShowSysDialog(const char *title, const char *msg, const char* negative, const char* positive, CCObject* target, SYSDLG_CallFunc pFunc)
{

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    android_ShowSysDialog(title, msg, negative, positive, target, pFunc);
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    
    WCHAR* _msg = Utf8ToUincode(msg);
    WCHAR* _title = Utf8ToUincode(title);

    int ret = MessageBoxW(NULL, _msg, _title, MB_OKCANCEL);

    if (ret == IDOK)
    {
        (target->*pFunc)(SYS_DLG_POSITIVE_BTN);
    }
    else if (ret == IDCANCEL)
    {
        (target->*pFunc)(SYS_DLG_NEGATIVE_BTN);
    }

    delete[] _msg;
    delete[] _title;

#endif
}

void ShortText(const char* text)
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    android_ShortText(text);
#endif
}

static SDialogContent buyItemContent;
void buyShopItem(CCObject* target, SYSDLG_CallFunc pFunc, int index)
{
    buyItemContent.target = target;
    buyItemContent.func = pFunc;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    buyItem_Android(index);
#else
    buyShopItemSucess(index);
#endif
}

void buyShopItemSucess(int index)
{
    CCObject* target = buyItemContent.target;
    SYSDLG_CallFunc pFunc = buyItemContent.func;
    (target->*pFunc)(index);
}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

extern "C"
{
	void android_ShortText(const char* text)
	{
		JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "com/qhshow/dumptys/DumptyJni", "ShortText", "(Ljava/lang/String;)V"))
		{
			jstring jText = t.env->NewStringUTF(text);
			t.env->CallStaticVoidMethod(t.classID, t.methodID, jText);
			t.env->DeleteLocalRef(jText);
		}
	}

    void android_ShowSysDialog(const char *title, const char *msg, const char* negative, const char* positive, CCObject* target, SYSDLG_CallFunc pFunc)
    {
        target->retain();

        SDialogContent con;
        con.target = target;
        con.func = pFunc;

        g_lstContents.push_back(con);

        JniMethodInfo t;
		if(JniHelper::getStaticMethodInfo(t, "com/qhshow/dumptys/DumptyJni", "ShowSysDialog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
		{
			jstring jTitle = t.env->NewStringUTF(title);
			jstring jMsg = t.env->NewStringUTF(msg);
			jstring jNegative = t.env->NewStringUTF(negative);
			jstring jPositive = t.env->NewStringUTF(positive);
			t.env->CallStaticVoidMethod(t.classID, t.methodID, jTitle, jMsg, jNegative, jPositive);
			t.env->DeleteLocalRef(jTitle);
			t.env->DeleteLocalRef(jMsg);
			t.env->DeleteLocalRef(jNegative);
			t.env->DeleteLocalRef(jPositive);
		}
    }

    void Java_com_qhshow_dumptys_DumptyJni_OnNegative(JNIEnv *env, jobject thiz)
    {

        SDialogContent* pCon = GetContent();
        if (!pCon) return;

        CCObject* target = pCon->target;
        unsigned int rc = target->retainCount();
        CC_SAFE_RELEASE_NULL(pCon->target);
        SYSDLG_CallFunc pFunc = pCon->func;
        if (rc > 1)
        {
            (target->*pFunc)(SYS_DLG_NEGATIVE_BTN);
        }

        g_lstContents.pop_back();
    }

    void Java_com_qhshow_dumptys_DumptyJni_OnPositive(JNIEnv *env, jobject thiz)
    {

        SDialogContent* pCon = GetContent();
        if (!pCon) return;

        CCObject* target = pCon->target;
        unsigned int rc = target->retainCount();
        CC_SAFE_RELEASE_NULL(pCon->target);
        SYSDLG_CallFunc pFunc = pCon->func;
        if (rc > 1)
        {
            (target->*pFunc)(SYS_DLG_POSITIVE_BTN);
        }

        g_lstContents.pop_back();
    }

    void buyItem_Android(int idx)
    {
        JniMethodInfo t;
        if(JniHelper::getStaticMethodInfo(t, "com/ibirdgame/archirun/PayWrapper", "Cocos_order", "(I)V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID, idx);
        }
    }

    void Java_com_qhshow_huawei_Dispel_buyShopItemBack(JNIEnv *env, jobject thiz, jint idx, jboolean bPayOk)
    {
        if(bPayOk)
        {
            buyShopItemSucess(idx);
        }
    }
}

#endif