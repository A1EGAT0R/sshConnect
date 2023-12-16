#include "json_operation.h"
using namespace nlohmann;


json
json_op::getJsonFromFile()
{
    json read;

    std::ifstream ist(serializedPath);
    if(ist)
        ist>>read;
    ist.close();

    return read;
}


void
json_op::serializedJson(const nlohmann::json& saved)
{
    std::ofstream ost(json_op::serializedPath);
    if(ost)
        ost<<saved;
    ost.close();
}

void
json_op::erase(const std::string &target)
{
    json erase_from = GET_MAIN_JSON;

    erase_from.erase(target);
    serializedJson(erase_from);

}