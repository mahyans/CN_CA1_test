#include "../include/User.hpp"
using namespace std;

int User::count{0};

User::User(string username, string pass) : username(username), pass(pass){
    admin = true;
    id = -1;
    loginStatus = false;
    purse = "";
    phoneNumber = "";
    address = "";
    count += 1;
    ID = count;
}

User::User(string username, string pass, string purse, string phone, string address)
    : username(username), pass(pass), purse(purse), phoneNumber(phone), address(address){
    admin = false;
    id = -1;
    loginStatus = false;
    count += 1;
    ID = count;
}

string User::toString() {
    stringstream strm;
    strm << "User data: "<< " [id] "  << ID << " [username] " << username << " [password] " << pass << " [admin] " << admin << " [purse] " << purse << " [phone] " << phoneNumber << " [address] " << address << endl;
    return strm.str();
}

bool User::isValid(string username_) {
    return (username_ == username);
}

bool User::fdMatches(int fd){
    return (fd == id);
}

bool User::idMatches(int _id){
    return (ID == _id);
}

bool User::login(string pass_){
    loginStatus = (pass_ == pass);
    return loginStatus;
}

void User::updateFd(int fd){
    id = fd;
}

bool User::isLoggedIn(){
    return loginStatus;
}

void User::logout(){
    id = -1;
    loginStatus = false;
}

bool User::isAdmin(){
    return admin;
}
