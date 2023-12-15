#pragma once
#include <string>


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
    User(std::string, std::string, std::string, std::string, unsigned short port = 22);
    User(User&);
    User(User&&);

    std::string getSerializedName() {return serializedName;}
    std::string getKeyPath() { return keyPath; }
    std::string getUserName() { return username; }
    std::string getServerIp() { return serverIp; }
    unsigned short getPort() { return port; }
};


namespace conf {
    const inline std::string serializedPath = "Srl.json";

    bool isCorrectUser(User*);

    std::unique_ptr<User> readUser(std::string);
    void serializeUser(User*);
}
