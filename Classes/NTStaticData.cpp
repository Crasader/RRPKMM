
/********************************************************************
 *    文件名  :    NTSTATICDATA.CPP
 *    作者    :    cy
 *    创建时间:    2013/7/24 15:02
 *    文件描述:
 *********************************************************************/
#include "NTStaticData.h"
#include "NTXmlLoader.h"

USING_NS_CC;

NTStaticData* NTStaticData::m_pShare = NULL;
NTStaticData* NTStaticData::sharedStaticData() {
    if (m_pShare == NULL) {
        m_pShare = new NTStaticData();
        if (!m_pShare || !m_pShare->init()) {
            CC_SAFE_DELETE(m_pShare);
        }
    }
    return m_pShare;
}

void NTStaticData::purgeSharedStaticData() {
    CC_SAFE_DELETE(m_pShare);
}


NTStaticData::~NTStaticData() {
    CC_SAFE_RELEASE_NULL(m_pXmlDict);
	
}


bool NTStaticData::init() {
    bool bRet = false;
    do {
        m_pXmlDict = NTXmlLoader::getDictFromXml("cn_string.xml");
        m_pXmlDict->retain();

		
        bRet = true;
    } while (0);

    return bRet;
}

const char* NTStaticData::getString1( const char* pKey ) {
    CCString* str = getString0(pKey);
    if(str == NULL) {
        return NULL;
    }
    return str->getCString();
}

cocos2d::CCString* NTStaticData::getString0( const char* pKey ) {
    if(m_pXmlDict == NULL) {
        return NULL;
    }
    CCObject* obj = m_pXmlDict->objectForKey(pKey);
    if(obj == NULL) {
        return NULL;
    }
    return (CCString*)obj;
}

