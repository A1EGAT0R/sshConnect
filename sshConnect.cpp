#include "User.h"

#include<stdlib.h>
#include <iostream>

std::unique_ptr<User> adder()
{
    std::string serializedName;

    std::string keyPath;
    std::string username;
    std::string serverIp;
    unsigned short port;

    std::cout<<"Enter name for new user: ";
    std::cin >> serializedName;

    std::cout<<"\nEnter the path to the key-file: ";
    std::cin >> keyPath;

    std::cout<<"\nEnter connect username: ";
    std::cin >> username;

    std::cout<<"\nEnter the server ip: ";
    std::cin >> serverIp;

    std::cout<<"\nEnter the host port: ";
    std::cin >> port;


    auto ret = std::make_unique<User>(User(serializedName,
                                           keyPath,
                                           username,
                                           serverIp,
                                           port
    ));

    conf::serializeUser(ret.get());
    return ret;
}

int main()
{
    std::string input;
    std::string us;
    std::unique_ptr<User> user;
    bool isCorrectUser = false;

    while(!isCorrectUser) {
        do {
            std::cout << "Select.\n"
                         "Create a new user(#add) \n"
                         "or connect using an existing one(#continue): ";

            std::cin >> input;
            if (input == "#add")
                adder();
            else if(input!="#continue")
                std::cout << "\nWrong input!\n\n";

        } while (input != "#continue");

        std::cout << "Enter username: ";
        std::cin >> us;
        user = conf::readUser(us);

        isCorrectUser = conf::isCorrectUser(user.get());
    }

    std::string command = "ssh -i " + (*user).getKeyPath() + ' ' + (*user).getUserName() + '@' + (*user).getServerIp();
    system(command.c_str());

    return 0;
}
