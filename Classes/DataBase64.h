
/********************************************************************
 *    �ļ���  :    DATABASE64.H
 *    ����    :    
 *    ����ʱ��:    2013/1/2 15:58
 *    �ļ�����:    ���database64�㷨�����ܴ浵����
 *********************************************************************/

#ifndef _H_DATABASE64_H_
#define _H_DATABASE64_H_

#include <string>

std::string saveData(unsigned char const* , unsigned int len);
std::string parseData(std::string const& s);

#endif // _H_DATABASE64_H_
