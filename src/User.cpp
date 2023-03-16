#include "../include/User.hpp"
using namespace std;

int User::count{0};

User::User(string username, string pass) : username(username), pass(pass){
    admin = true;
    id = -1;
    loginStatus = false;
    purse = 0;
    phoneNumber = "";
    address = "";
    count += 1;
    ID = count;
}

User::User(string username, string pass, string _purse, string phone, string address)
    : username(username), pass(pass), phoneNumber(phone), address(address){
    admin = false;
    id = -1;
    loginStatus = false;
    count += 1;
    ID = count;
    purse = stoi(_purse);
}

string User::toString() {
    stringstream strm;
    if(!admin)
        strm << "User data: "<< " [id] "  << ID << " [username] " << username <<  " [admin] " << admin << " [purse] " << purse << " [phone] " << phoneNumber << " [address] " << address << endl;
    else 
        strm << "User data: "<< " [id] "  << ID << " [username] " << username << " [admin] " << admin << endl;

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

bool User::canAfford(int _price){
    if(purse >= _price) return true;
    else return false;
}

