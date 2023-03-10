#include "../include/User.hpp"
using namespace std;

User::User(string username, string pass, string isAdminS, string datalimitS) : username(username), pass(pass) {
    for_each(isAdminS.begin(), isAdminS.end(), [](char & c){c = ::tolower(c);});
    admin = (isAdminS == "true" || isAdminS == "yes");
    datalimit = stoi(datalimitS)*1000;
    id = -1;
    loginStatus = false;
    getcwd(currDir, BUFFER_SIZE); 
    strcpy(originDir, currDir);
}

void User::printUser() {
    cout << "User data: [username] " << username << " [password] " << pass << " [admin] " << admin << " [size] " << datalimit << endl;
}

bool User::isValid(string username_) {
    return (username_ == username);
}

bool User::fdMatches(int fd){
    return (fd == id);
}

bool User::login(string pass_){
    loginStatus = (pass_ == pass);
    resetDir();
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
    resetDir();
}

char* User::getCurrDir() {
    return currDir;
}

string User::getRelativeDir(string path){
    return string(currDir) + '/' + path;
}

bool User::updateDir(string path){
    bool success = chdir(path.c_str());
    getcwd(currDir, BUFFER_SIZE); 
    return !success;
}

bool User::resetDir() {
    strcpy(currDir, originDir);
    return !chdir(originDir);
}

bool User::canDownload(int fileSize) {
    return (fileSize <= datalimit);
}

void User::updateDataLimit(int fileSize) {
    datalimit -= fileSize;
}

bool User::isAdmin(){
    return admin;
}
