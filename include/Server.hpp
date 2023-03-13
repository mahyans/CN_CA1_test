#ifndef SERVER_HEADER
#define SERVER_HEADER

#include "IncludeAndDefine.hpp"
#include "User.hpp"
#include "Room.hpp"
#include "Parser.hpp"

class Server {
public:
    Server(std::map<std::string, std::vector<std::string>> inputs);
    void printServer();
    int acceptClient(int port);
    std::string handleCommand(std::string command, std::string argument, int userFd, int userDataFd);
    void run();

private:
    std::string curr_log, log_path;
    std::string hostName;
    int cmdChannelPort, dataChannelPort, serverDataFd, serverCmdFd;
    std::vector<User> users; 
    std::vector<Room> rooms;
    std::vector <std::string> adminFiles;
    std::map<int, std::string> fdLastRequest, fdLoggedInUser; 

    std::string handleSignIn(string username , string password , int fd);


    User* findUserByFd(int userFd); 
    User* findUserByName(std::string username_);
    bool loginUser(std::string curr_user, int fd, std::string lastUser);
    bool hasFileAccess(User* currUser, std::string file);
    bool hasDirectoryAccess(User* currUser, std::string file);
    std::string handleUser(int userFd, std::string argument1);
    std::string handlePass(int userFd, std::string argument1);
    std::string handlePwd(User* currUser);
    std::string handleMkd(User* currUser, std::string argument);
    std::string handleDele(User* currUser, std::string argument1, std::string argument2);
    std::string handleFileDel(User* currUser, std::string argument2);
    std::string handleDirDel(User* currUser, std::string argument2);
    std::string handleLs(User* currUser, int dataFd);
    std::string handleCwd(User* currUser, std::string argument1);
    std::string handleRetr(User* currUser, std::string argument1, int dataFd);
    std::string makeRes(int code, std::string msg);
    std::string handleRename(User* currUser, std::string argument1, std::string argument2);
    std::string handleHelp();
    std::string handleQuit(User* currUser, int userFd);
    int setupServer(int port);
    int getFileSize(std::string fileName);
    void sendData(std::string file, int dataFd);
    void convertConfig(std::map<std::string, std::vector<std::string>> inputs);
    void writeLog();
};

void exitLog(std::string log);

void signal_callback_handler(int signum);

#endif