/********************************************************************
 *    文件名  :    NTSharedJsonData.h
 *    作者    :    yobo
 *    创建时间:    2014/01/04 17:48 
 *    文件描述:    
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

	//金币摆放
	CC_SYNTHESIZE(CSJson::Value,m_jsonContent,JsonContent);

	//排行榜存储
	CC_SYNTHESIZE(CSJson::Value,m_jsonRank,JsonRank);
	

	//中文
	CC_SYNTHESIZE(CSJson::Value,m_jsonCn,JsonCn);

	//排行榜特殊处理
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
