/********************************************************************
 *    �ļ���  :    NTXMLLOADER.H
 *    ����    :    cy
 *    ����ʱ��:    2013/5/8 13:08
 *    �ļ�����:    ����xml����
 *********************************************************************/

#ifndef _H_NTXMLLODER_H_
#define _H_NTXMLLODER_H_

#include "cocos2d.h"

class NTXmlLoader {

public:
	
	static cocos2d::CCDictionary* getDictFromXml(char* pXmlFile);
};

#endif // _H_NTXMLLOADER_H_
