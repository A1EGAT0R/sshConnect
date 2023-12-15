#include "User.h"
#include <nlohmann/json.hpp>
#include<fstream>


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

User::User(std::string serName, std::string keyPath, std::string usName, std::string servIp, unsigned short port):
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
    json inFileJson;

    std::ifstream ist(conf::serializedPath);
    if(ist)
        ist>>inFileJson;
    ist.close();

    std::ofstream ost(conf::serializedPath);

    runtimeJson["KeyPath"] = user->getKeyPath();
    runtimeJson["UserName"] = user->getUserName();
    runtimeJson["ServerIp"] = user->getServerIp();
    runtimeJson["Port"] = user->getPort();

    inFileJson[user->getSerializedName()] = runtimeJson;
    ost << inFileJson;
    ost.close();
}

std::unique_ptr<User>
conf::readUser(std::string serializedName)
{
    json read;

    std::ifstream ist(conf::serializedPath);
    ist >> read;
    ist.close();

    json retValues = read[serializedName];

    auto ret = std::make_unique<User>(User(serializedName,
                                           retValues["KeyPath"].get<std::string>(),
                                           retValues["UserName"].get<std::string>(),
                                           retValues["ServerIp"].get<std::string>(),
                                           retValues["Port"].get<unsigned short>()
    ));
    return ret;
}



