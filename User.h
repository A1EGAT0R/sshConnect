#pragma once
#include <string>
#include <memory>
#include "json_operation.h"

class User {
private:
    std::string serializedName;

    std::string keyPath;
    std::string username;
    std::string serverIp;
    unsigned short port;

public:
    User() :serializedName(""),
            keyPath(""),
            username(""),
            serverIp(""),
            port(22)
            {}
    User(const std::string&, const std::string&, const std::string&, const std::string&, unsigned short port = 22);
    User(User&);
    User(User&&);

    std::string getSerializedName() {return serializedName;}
    std::string getKeyPath() { return keyPath; }
    std::string getUserName() { return username; }
    std::string getServerIp() { return serverIp; }
    unsigned short getPort() { return port; }
};


namespace conf {

    bool isCorrectUser(User*);

    std::unique_ptr<User> readUser(const std::string&);
    void serializeUser(User*);

}
