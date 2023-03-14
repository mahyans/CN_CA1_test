#ifndef USER_HEADER
#define USER_HEADER

#include "IncludeAndDefine.hpp"


class User {
    static int count;
    public:
        User(std::string username, std::string pass);
        User(std::string username, std::string pass, std::string purse, std::string phone, std::string address);
        std::string toString();
        bool isValid(std::string username_);
        bool fdMatches(int fd);
        bool idMatches(int id);
        void updateFd(int fd);
        bool login(std::string pass_);
        bool isLoggedIn();
        void logout();    
        bool isAdmin();
        void reduceMoney(int howMuch){purse -= howMuch;};
        bool canAfford(int _price);
        int getId(){return ID;};
        std::vector<std::string>reservs;
        void edit(std::string pas, std::string phone, std::string ad){pass = pas; phoneNumber = phone; address = ad ;};
    private:
        int id;
        int ID, purse;
        std::string username, pass;
        bool admin, loginStatus;
        std::string phoneNumber, address;
};

#endif