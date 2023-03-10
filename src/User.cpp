#include "../include/User.hpp"
using namespace std;

int User::count{0};

User::User(string username, string pass, string isAdmin) : username(username), pass(pass){
    admin = (isAdmin == "true");
    id = -1;
    loginStatus = false;
    purse = "";
    phoneNumber = "";
    address = "";
    count += 1;
    ID = rand();
}

string User::toString() {
    stringstream strm;
    strm << " User data: " << " [id] "  << ID << " [username] " << username << " [password] " << pass << " [admin] " << admin << " [purse] " << purse << " [phone] " << phoneNumber << " [address] " << address << endl;
    return strm.str();
}

bool User::isValid(string username_) {
    return (username_ == username);
}

bool User::fdMatches(int fd){
    return (fd == id);
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
