/********************************************************************
 *    文件名  :    NTXMLLOADER.H
 *    作者    :    cy
 *    创建时间:    2013/5/8 13:08
 *    文件描述:    加载xml配置
 *********************************************************************/

#ifndef _H_NTXMLLODER_H_
#define _H_NTXMLLODER_H_

#include "cocos2d.h"

class NTXmlLoader {

public:
	
	static cocos2d::CCDictionary* getDictFromXml(char* pXmlFile);
};

#endif // _H_NTXMLLOADER_H_
