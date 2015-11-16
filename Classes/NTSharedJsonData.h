/********************************************************************
 *    �ļ���  :    NTSharedJsonData.h
 *    ����    :    yobo
 *    ����ʱ��:    2014/01/04 17:48 
 *    �ļ�����:    
 *********************************************************************/
#ifndef _H_NTSHAREDJSONDATA_H_
#define _H_NTSHAREDJSONDATA_H_
#include "cocos2d.h"
#include "json.h"
#include "NTCoinPosData.h"
using namespace cocos2d;
enum {
	eRank,
};
class NTSharedJsonData{

	
public:
	
	

	~NTSharedJsonData();
	static NTSharedJsonData* sharedJsonData();
	static void purgeSharedJsonData();

	static NTSharedJsonData * m_pShare;

	bool init();

	void loadJsonFile();

	//��Ұڷ�
	CC_SYNTHESIZE(CSJson::Value,m_jsonContent,JsonContent);

	//���а�洢
	CC_SYNTHESIZE(CSJson::Value,m_jsonRank,JsonRank);
	

	//����
	CC_SYNTHESIZE(CSJson::Value,m_jsonCn,JsonCn);

	//���а����⴦��
	void createRankJsonFile(std::string fileName);

	void saveJsonFile(std::string fileName,CSJson::Value pJson);

	void createJsonFile(std::string fileName);

	void updateData(int nDataId);


	int coinPosData[COIN_TYPE_MAX][COIN_HEIGHT_COUNT][COIN_WIDTH_COUNT];
	int getPosValue(int coinType,int column,int row);
	

	CC_SYNTHESIZE(int,m_nSignDay,SignDay);

	void saveName(std::string strName);
};


#endif //_H_NTSHAREDJSONDATA_H_
