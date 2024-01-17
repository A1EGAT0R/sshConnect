#include "User.h"

#include <stdlib.h>
#include <iostream>
#include <array>

namespace commands
{
    const std::string ADD = "#add";
    const std::string CONTINUE = "#go";
    const std::string REMOVE = "#del";
    const std::string LIST = "#list";
}

void
clear_win()
{
    std::cout << "\033[0d\033[2J";
}

void adder()
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
}

void jsonFormatedPrint(const std::string& fromJsonString)
{
    for (auto ch : fromJsonString) {
        std::cout << ch;
        if(ch == '}')
            std::cout << "\n\n";
    }
}

void eraser()
{
    std::string target;

    std::cout<<"\n\n";
    std::cout << "Enter the username: ";
    std::cin >> target;
    std::cout<<"\n\n";

    json_op::erase(target);
}

int main()
{
    std::string input;
    std::string us;
    std::unique_ptr<User> user;
    bool isCorrectUser = false;

    while(!isCorrectUser) {
        do {
            std::cout << "Select.\n" <<
                         "See user list(" << commands::LIST << ")\n" <<
                         "Create a new user(" << commands::ADD << ")\n" <<
                         "Delete user(" << commands::REMOVE <<")\n" <<
                         "or connect using an existing one("<<commands::CONTINUE<<"): ";

            std::cin >> input;
            clear_win();
            if (input == commands::ADD)
                adder();
            else if (input == commands::LIST)
            {
                std::cout<<"\n\n";
                jsonFormatedPrint(to_string((GET_MAIN_JSON)));
                std::cout<<"\n";
            }
            else if(input == commands::REMOVE)
                eraser();
            else if(input!=commands::CONTINUE)
                std::cout << "\n\nWrong input!\n\n";

        } while (input != commands::CONTINUE);

        std::cout << "Enter username: ";
        std::cin >> us;
        user = conf::readUser(us);

        isCorrectUser = conf::isCorrectUser(user.get());
    }

    std::string command = "ssh -i " + (*user).getKeyPath() + ' ' + (*user).getUserName() + '@' + (*user).getServerIp();
    system(command.c_str());

    return 0;
}
