#ifndef USER_HEADER
#define USER_HEADER

#include "IncludeAndDefine.hpp"

class User {
    static int count;
    public:
        User(std::string username, std::string pass);
        User(std::string username, std::string pass, std::string purse, std::string phone, std::string address);
        std::string toString();
        void User::printUserAdmin();
        bool isValid(std::string username_);
        bool fdMatches(int fd);
        bool idMatches(int id);
        void updateFd(int fd);
        bool login(std::string pass_);
        bool isLoggedIn();
        void logout();    
        bool isAdmin();
        void setPurse(std::string purse_){purse = purse_;};
        void setPhone(std::string phone_){phoneNumber = phone_;};
        void setaddress(std::string add_){address = add_;};
    private:
        int id;
        int ID;
        std::string username, pass;
        bool admin, loginStatus;
        std::string purse, phoneNumber, address;
};

#endif