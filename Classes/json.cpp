
#include "json.h"
std::string JsonWriter(const CSJson::Value& v)
{
	CSJson::FastWriter w;

	std::string result;

	try
	{
		result = w.write(v);
	}
	catch (...)
	{
		//TRACE0("JsonWriter ...error..");
	}


	return result;
}

//
bool JsonReader(std::string& strData,CSJson::Value& v)
{
	CSJson::Reader r;
	
	bool result = false;
	try
	{

		result = r.parse(strData, v);
	}
	catch (...)
	{
		//TRACE0("JsonWriter ...error..");
	}

	return result;
}


CSJson::Value ReadJsonFile(const std::string& name)
{
	std::string file = name + ".json";
	CSJson::Value v;

	FILE* fp = fopen(file.c_str(), "rt");

	if(fp != NULL) 
	{
		fseek(fp, 0, SEEK_END);
		int len = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		char tmp[1024*10] = {0};

		fread(tmp, 1, len, fp);
		fclose(fp);

		std::string data = tmp;
		JsonReader(data, v);
	}

	return v;
}

void WriteJsonFile(const std::string& name, CSJson::Value& v)
{
	std::string file = name + ".json";

	FILE* fp = fopen(file.c_str(), "wt");
	if(fp != NULL)
	{	
		std::string data = JsonWriter(v);
		fwrite(data.c_str(), 1, data.size(), fp);
		fclose(fp);
	}
}