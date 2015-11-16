#ifndef JSON_JSON_H_INCLUDED
#define JSON_JSON_H_INCLUDED

#include "CocoStudio/Json/lib_json/autolink.h"
#include "CocoStudio/Json/lib_json/value.h"
#include "CocoStudio/Json/lib_json/reader.h"
#include "CocoStudio/Json/lib_json/writer.h"
#include "CocoStudio/Json/lib_json/features.h"
#include <string>
#include "cocos2d.h"



    std::string JsonWriter(const CSJson::Value& v);

    bool JsonReader(std::string& strData, CSJson::Value& v);
 
    CSJson::Value ReadJsonFile(const std::string& name);

    void WriteJsonFile(const std::string& name, CSJson::Value& v);

#endif // JSON_JSON_H_INCLUDED
