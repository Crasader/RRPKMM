
/********************************************************************
 *    �ļ���  :    NTSTATICDATA.H
 *    ����    :    cy
 *    ����ʱ��:    2013/7/24 15:01
 *    �ļ�����:    ��̬����
 *********************************************************************/

#ifndef _H_NTSTATICDATA_H_
#define _H_NTSTATICDATA_H_

#include "cocos2d.h"
USING_NS_CC;
#define STATIC_DATA_STRING1(key) NTStaticData::sharedStaticData()->getString1(key)

class NTStaticData {

public:
	~NTStaticData();
	static NTStaticData* sharedStaticData();
	static void purgeSharedStaticData();
	
	const char* getString1(const char* pKey);
	cocos2d::CCString* getString0(const char* pKey);
;

	void test();
private:
	bool init();
	static NTStaticData* m_pShare;

	cocos2d::CCDictionary* m_pXmlDict;




	
};

#endif // _H_NTSTATICDATA_H_