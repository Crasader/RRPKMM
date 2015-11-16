
/********************************************************************
 *    文件名  :    NTXMLLOADER.CPP
 *    作者    :    cy
 *    创建时间:    2013/5/8 13:09
 *    文件描述:    
 *********************************************************************/
#include "NTXmlLoader.h"

USING_NS_CC;

cocos2d::CCDictionary* NTXmlLoader::getDictFromXml( char* pXmlFile )
{
	return CCDictionary::createWithContentsOfFile(pXmlFile);
}

