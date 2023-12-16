#pragma once
#include<nlohmann/json.hpp>
#include<string>
#include<fstream>

#define GET_MAIN_JSON json_op::getJsonFromFile()

namespace json_op
{
    const inline std::string serializedPath = "Srl.json";

    void serializedJson(const nlohmann::json&);
    nlohmann::json getJsonFromFile();
    void erase(const std::string&);
}