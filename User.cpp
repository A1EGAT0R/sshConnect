#include "User.h"
#include<vector>

using namespace nlohmann;

User::User(User&& us)
{
    serializedName = us.getSerializedName();
    keyPath = us.getKeyPath();
    username = us.getUserName();
    serverIp = us.getServerIp();
    port = us.getPort();
}
User::User(User& us)
{
    serializedName = us.getSerializedName();
    keyPath = us.getKeyPath();
    username = us.getUserName();
    serverIp = us.getServerIp();
    port = us.getPort();
}

User::User(const std::string& serName, const std::string& keyPath, const std::string& usName, const std::string& servIp, unsigned short port):
serializedName(serName),
keyPath(keyPath),
username(usName),
serverIp(servIp),
port(port)
{}


bool
conf::isCorrectUser(User* user)
{
    std::ifstream ist(user->getKeyPath());
    if(!ist)
        return false;
    ist.close();

    if((user->getSerializedName()).size() == 0)
        return false;

    return true;
}

void
conf::serializeUser(User* user)
{
    json runtimeJson;
    json inFileJson = GET_MAIN_JSON;

    runtimeJson["SerializedName"] = user->getSerializedName();
    runtimeJson["KeyPath"] = user->getKeyPath();
    runtimeJson["UserName"] = user->getUserName();
    runtimeJson["ServerIp"] = user->getServerIp();
    runtimeJson["Port"] = user->getPort();

    inFileJson[user->getSerializedName()] = runtimeJson;
    json_op::serializedJson(inFileJson);
}

std::unique_ptr<User>
conf::readUser(const std::string& serializedName)
{
    json read = GET_MAIN_JSON;

    json retValues = read[serializedName];

    auto ret = std::make_unique<User>(User(serializedName,
                                           retValues["KeyPath"].get<std::string>(),
                                           retValues["UserName"].get<std::string>(),
                                           retValues["ServerIp"].get<std::string>(),
                                           retValues["Port"].get<unsigned short>()
    ));
    return ret;
}



