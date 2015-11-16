#include "NTSharedJsonData.h"
NTSharedJsonData * NTSharedJsonData::m_pShare = NULL;
NTSharedJsonData::~NTSharedJsonData()
{

}

NTSharedJsonData* NTSharedJsonData::sharedJsonData()
{
	if (m_pShare == NULL) {
		m_pShare = new NTSharedJsonData();
		m_pShare->init();
		if (!m_pShare ) {
			CC_SAFE_DELETE(m_pShare);
		}
	}
	return m_pShare;
}


void NTSharedJsonData::purgeSharedJsonData()
{
	  CC_SAFE_DELETE(m_pShare);
}

bool NTSharedJsonData::init()
{
	 m_nSignDay = -1;
	 loadJsonFile();
	 return true;
}

void NTSharedJsonData::loadJsonFile()
{
	CCString* str = CCString::createWithContentsOfFile("goldShader.json");
	JsonReader(str->m_sString, m_jsonContent);
	for(int i=0;i<COIN_TYPE_MAX;i++){
		for(int j=0;j<COIN_HEIGHT_COUNT;j++){
			for(int k=0;k<COIN_WIDTH_COUNT;k++){
				coinPosData[i][j][k] = m_jsonContent["words"][i][j][k].asInt();
			}
		}
	}


	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	path+="rank.json";
	if(!CCFileUtils::sharedFileUtils()->isFileExist(path)){
		createRankJsonFile(path);
	}

	CCString *strRank = CCString::createWithContentsOfFile(path.c_str());
	JsonReader(strRank->m_sString,m_jsonRank);
	

	CCString *strCn = CCString::createWithContentsOfFile("cn.json");
	JsonReader(strCn->m_sString,m_jsonCn);
}

void NTSharedJsonData::saveJsonFile( std::string fileName,CSJson::Value pJson )
{
	WriteJsonFile(fileName,pJson);
}


//
//void NTSharedJsonData::createJsonFile( std::string fileName )
//{
//	do
//	{
//		// read the file from hardware
//		std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName.c_str());
//		FILE *fp = fopen(fullPath.c_str(),"wb+");
//		CC_BREAK_IF(!fp);
//		fclose(fp);
//	} while (0);
//	
//	
//}

void NTSharedJsonData::createRankJsonFile(std::string fileName)
{
	
	CCString *strRank = CCString::createWithContentsOfFile("rank_source.json");
	CSJson::Value pJson;
	JsonReader(strRank->m_sString,pJson);
	fileName = fileName.substr(0,fileName.length()-5);
	saveJsonFile(fileName,pJson);
}

void NTSharedJsonData::updateData( int nDataId )
{
	if(nDataId == eRank){
		std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
		path+="rank.json";
		CCString *strRank = CCString::createWithContentsOfFile(path.c_str());
		JsonReader(strRank->m_sString,m_jsonRank);
	}
}

int NTSharedJsonData::getPosValue( int coinType,int column,int row )
{
	return coinPosData[coinType][column][row];
}

void NTSharedJsonData::saveName( std::string strName )
{
	
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	path+="rank.json";
	if(CCFileUtils::sharedFileUtils()->isFileExist(path)){
		CCString *strRank = CCString::createWithContentsOfFile(path.c_str());
		CSJson::Value jsonRank1;
		JsonReader(strRank->m_sString,jsonRank1);
		//CCLog(strRank->m_sString.c_str());
		jsonRank1["hero"] = strName;
		path =path.substr(0,path.length()-5);
		NTSharedJsonData::sharedJsonData()->saveJsonFile(path,jsonRank1);
		NTSharedJsonData::sharedJsonData()->updateData(eRank);
	}

	CCString *strRank = CCString::createWithContentsOfFile("rank_source.json");
	CSJson::Value jsonRank1;
	JsonReader(strRank->m_sString,jsonRank1);
	jsonRank1["hero"] = strName;
	NTSharedJsonData::sharedJsonData()->saveJsonFile("rank_source",jsonRank1);
	NTSharedJsonData::sharedJsonData()->updateData(eRank);
}





