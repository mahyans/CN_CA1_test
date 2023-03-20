#ifndef SERVER_HEADER
#define SERVER_HEADER

#include "IncludeAndDefine.hpp"
#include "User.hpp"
#include "Room.hpp"
#include "Parser.hpp"
#include <iostream>
#include <string>
#include "Date.hpp"



class Server {
public:
    Server(){};
    void setValue(std::map<std::string, std::vector<std::string>> inputs);
    static Server* getInstance(){
        if(serverPtr == NULL){
            Server* ptr = new Server();
            return ptr;
        }else throw "Just one server at time!\n";
    }
    Server(const Server& obj) = delete;
    void printServer();
    int acceptClient(int port);
    std::string handleCommand(std::string command, std::string argument, int userFd);
    void run();
    void setDate(std::string date);
    void updateJsonFiles();
    void checkExpiredReservation();

private:
    static Server* serverPtr;
    static int num;
    Date systemDate = Date("0-0-0");
    std::string curr_log, log_path;
    std::string hostName;
    int cmdChannelPort, dataChannelPort, serverDataFd, serverCmdFd;
    std::vector<User> users; 
    std::vector<Room> rooms;
    std::vector <std::string> adminFiles;
    std::map<int, std::string> fdLastRequest, fdLoggedInUser; 
    User* loginedUser;
    User* findUserByFd(int userFd); 
    User* findUserById(int userId);
    Room* findRoomByNumber(string num);
    User* findUserByName(std::string username_);
    int setupServer(int port);
    void convertConfig(std::map<std::string, std::vector<std::string>> inputs);
    void writeLog();
};

void exitLog(std::string log);

void signal_callback_handler(int signum);

#endif