
/********************************************************************
 *    �ļ���  :    NTXMLLOADER.CPP
 *    ����    :    cy
 *    ����ʱ��:    2013/5/8 13:09
 *    �ļ�����:    
 *********************************************************************/
#include "NTXmlLoader.h"

USING_NS_CC;

cocos2d::CCDictionary* NTXmlLoader::getDictFromXml( char* pXmlFile )
{
	return CCDictionary::createWithContentsOfFile(pXmlFile);
}

