#include "../include/Server.hpp"
using namespace std;

char SERVER_ABSOLUTE_PATH[BUFFER_SIZE];

Server::Server(map<string, vector<string>> inputs)
{
    convertConfig(inputs);
    serverCmdFd = setupServer(cmdChannelPort);

    curr_log = "";
    getcwd(SERVER_ABSOLUTE_PATH, BUFFER_SIZE);
    log_path = string(SERVER_ABSOLUTE_PATH) + LOG_FILE_NAME;
};

void Server::setDate(string date)
{
    Date newDate = Date(date);
    systemDate = newDate;
    
}

int Server::getFileSize(string fileName)
{
    ifstream in_file(fileName, ios::binary);
    in_file.seekg(0, ios::end);
    int file_size = in_file.tellg();
    return file_size;
}

string Server::handleQuit(User *currUser, int userFd)
{
    fdLoggedInUser.erase(userFd);
    currUser->logout();
    return SUCCESSFUL_QUIT;
}

string Server::handleHelp()
{
    string help;
    help += "214\n";
    help += "user [username]: This command is used to submit a username for authentication.\n\n";
    help += "pass [password]: This command is used to submit a password for the previously submitted username for authentication.";
    help += "This command must be executed directly after the \"user\" command.\n\n";
    help += "pwd: Show the path of the current working directoty.\n\n";
    help += "mkd [path]: Make a new directory in the specified path.\n\n";
    help += "dele [-f|-d] [file name| directory path]: Delete the file with the name or the directory in the path specified in its argument\n\n";
    help += "ls: Show all the files and folders in the current directory.\n\n";
    help += "cwd [path]: Change the current working directory and move to the specified path.\n\n";
    help += "rename [from] [to]: Change the name of the file given in the first argument to the name specified in the second argument.\n\n";
    help += "retr [file name]: Download the file with the specified name.\n\n";
    help += "help: Show the system commands and their descriptions.\n\n";
    help += "quit: Logout from the server.\n\n";
    return help;
}

void Server::sendData(string file, int dataFd)
{
    send(dataFd, file.c_str(), strlen(file.c_str()), 0);
}

User *Server::findUserByFd(int userFd)
{
    for (auto &user : users)
        if (user.fdMatches(userFd))
            return &user;
    return NULL;
}

User *Server::findUserById(int userId)
{
    for (auto &user : users)
        if (user.idMatches(userId))
            return &user;
    return NULL;
}

string Server::handleUser(int userFd, string argument1)
{
    if (fdLoggedInUser.find(userFd) != fdLoggedInUser.end())
        return NEED_TO_LOGOUT;
    User *curr_user = findUserByName(argument1);
    if (curr_user)
    {
        if (!curr_user->isLoggedIn())
        {
            curr_user->updateFd(userFd);
            fdLastRequest[userFd] = argument1;
            return USERNAME_OK;
        }
        else
            return ALREADY_LOGGED_IN;
    }
    else
        return INVALID_LOGIN;
}

string Server::handlePass(int userFd, string argument1)
{
    if (fdLastRequest.find(userFd) != fdLastRequest.end())
    {
        if (loginUser(argument1, userFd, fdLastRequest[userFd]))
            return SUCCESSFUL_LOGIN;
        else
            return INVALID_LOGIN;
    }
    else
        return BAD_SEQUENCE;
}

void Server::printServer()
{
    cout << "Server info:\n";
    cout << "Command Channel Port: " << cmdChannelPort << endl;
    cout << "Data Channel Port: " << dataChannelPort << endl;
    cout << "files: " << endl;
    for (auto file : adminFiles)
    {
        cout << file << " ";
    }
    cout << endl;
    cout << "User List: \n";
    for (auto user : users)
        cout << user.toString();
}

User *Server::findUserByName(string username_)
{
    for (auto &user : users)
        if (user.isValid(username_))
            return &user;
    return NULL;
}

bool Server::loginUser(string password, int fd, string lastUser)
{
    for (auto &user : users)
    {
        if (user.fdMatches(fd) && user.isValid(lastUser))
        {
            if (user.login(password))
            {
                fdLoggedInUser[fd] = lastUser;
                return true;
            }
            else
                return false;
        }
    }
    return false;
}

string Server::handleCommand(string command, string argument, int userFd)
{

    curr_log += "Client (fd = " + to_string(userFd) + ") requested: " + command;
    writeLog();

    string  argument1, argument2, argument3 , argument4;
    User *currUser = findUserByFd(userFd);

    
    if (command == SIGN_IN_COMMAND | command == CANCLE_COMMAND) 
    {
        stringstream ss(argument);
        getline(ss, argument1 , ' ');
        getline(ss, argument2 , '\n');
    }
    else if(command == BOOK_COMMAND | command == USER_DATA)
    {
        stringstream ss(argument);
        getline(ss, argument1 , ' ');
        getline(ss, argument2 , ' ');
        getline(ss, argument3 , ' ');
        getline(ss, argument4 , '\n');   
    }
    else if(command == ADD_COMMAND | command == MODIFY_COMMAND)
    {
        stringstream ss(argument);
        getline(ss, argument1 , ' ');
        getline(ss, argument2 , ' ');
        getline(ss, argument3 , '\n');
    }
    else if (command == DELE_COMMAND || command == RENAME_COMMAND)
    {
        stringstream ss(argument);
        getline(ss, argument1, ' ');
        getline(ss, argument2, '\n');
    }
    else
        argument1 = argument;
    

    if (command == SET_TIME_COMMAND)
    {
        try{
        setDate(argument);
        return SUCCESSFUL;
        }catch(...){
            return BAD_ARGUMENT;
        } 
    }

    if (command == PASS_DAY_COMMAND)
    {
        try{
            if (currUser->isAdmin()){
                systemDate.addDay(stoi(argument));
                cout << systemDate.toSting() << endl;
                return SUCCESSFUL;
            }
            return ACCESS_DENIED;
        }catch(...){
            return BAD_ARGUMENT;
        }    
    }

    if (command == SIGN_UP_COMMAND)
    {
        if (findUserByName(argument1) == NULL)
        {
            fdLastRequest[userFd] = argument1;
            return ENTER_USER_DATA;
        }
        else return USER_ALREADY_EXIST;
    }

    if (command == USER_DATA)
    {
        if (fdLastRequest.find(userFd) != fdLastRequest.end())
        {
            string username =  fdLastRequest[userFd];
            User newUser(username, argument1, argument2, argument3, argument4);
            users.push_back(newUser);
            return SUCCESSFUL_SIGNUP;
        }
        else
            return BAD_SEQUENCE;        
    }

    if (command == SIGN_IN_COMMAND)
    {
        if (fdLoggedInUser.find(userFd) != fdLoggedInUser.end())
            return NEED_TO_LOGOUT;
        for(auto us : users)cout << us.toString() << endl;

        User * currUser = findUserByName(argument1);
        if (currUser)
        {
            if (currUser->login(argument2))
            {
                fdLoggedInUser[userFd] = argument1;
                return SUCCESSFUL_LOGIN;
            }
        }
        else return INVALID_USERNAME_PASS;
    }

    else if(command == VIEW_USER_INFO){

    }else if(command == VIEW_USER_INFO){

    }else if(command == VIEW_USER_INFO){

    }else if(command == VIEW_USER_INFO){

    }else if(command == VIEW_USER_INFO){

    }else if(command == VIEW_USER_INFO){

    }else if(command == VIEW_USER_INFO){

    }else if(command == VIEW_USER_INFO){

    }else if(command == VIEW_USER_INFO){

    }else if(command == VIEW_USER_INFO){

    }



    

    return SYNTAX_ERROR;
}

void Server::convertConfig(map<string, vector<string>> inputs)
{

    cmdChannelPort = stoi(inputs[COMMAND_PORT][0]);
    hostName = inputs[HOST][0];
    auto usersInfo = parseJson(USERS_INFO_FILE);
    auto roomsInfo = parseJson(ROOMS_INFO_FILE);
    int index = 0;

    for (int i = 0; i < usersInfo["id"].size(); i++)
    {
        if (usersInfo["admin"][i] == "true")
        {
            User newUser(usersInfo["user"][i], usersInfo["password"][i]);
            users.push_back(newUser);
        }
        else
        {
            User newUser(usersInfo["user"][i], usersInfo["password"][i], usersInfo["purse"][index], usersInfo["phoneNumber"][index], usersInfo["address"][index]);
            index += 1;
            users.push_back(newUser);
        }
    }
    index = 0;
    for (int i = 0; i < roomsInfo["number"].size(); i++)
    {
        string number = roomsInfo["number"][i];
        int price = stoi(roomsInfo["price"][i]);
        int cap = stoi(roomsInfo["capacity"][i]);
        int maxCap = stoi(roomsInfo["maxCapacity"][i]);
        int numOfReservation = maxCap - cap;
        Room newRoom(number, price, maxCap, cap);

        for (int x = 0; x < numOfReservation; x++)
        {
            int id = stoi(roomsInfo["id"][index]);
            int numOfBeds = stoi(roomsInfo["numOfBeds"][index]);
            string reserveDate = roomsInfo["reserveDate"][index];
            string checkoutDate = roomsInfo["checkoutDate"][index];
            Reservation newRes(findUserById(id), numOfBeds, reserveDate, checkoutDate);
            newRoom.addReservation(&newRes);
            index += 1;
        }
        rooms.push_back(newRoom);
    }
}

void Server::writeLog()
{
    if (curr_log == "")
        return;

    time_t now = time(0);
    char *dt = strtok(ctime(&now), "\n");
    string newLog = "[";
    newLog += dt;
    newLog += "] ";
    newLog += curr_log;
    newLog += "\n";

    ofstream logFile;
    logFile.open(log_path, ios_base::app);
    logFile << newLog;
    logFile.close();
    curr_log = "";
}

int Server::setupServer(int port)
{
    struct sockaddr_in address;
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    // only for command
    listen(server_fd, 4);

    return server_fd;
}

int Server::acceptClient(int port)
{
    int client_fd;
    struct sockaddr_in client_address;
    int address_len = sizeof(client_address);
    client_fd = accept(port, (struct sockaddr *)&client_address, (socklen_t *)&address_len);
    return client_fd;
}

void Server::run()
{
    int new_data_socket, new_cmd_socket, data_max_sd, cmd_max_sd;
    char buffer[BUFFER_SIZE] = {0};
    fd_set cmd_master_set, cmd_working_set;
    map<int, int> cmdDataFd;
    FD_ZERO(&cmd_master_set);
    cmd_max_sd = serverCmdFd;
    FD_SET(serverCmdFd, &cmd_master_set);

    printf("Server is up!\n");
    curr_log += "Server is now online.";
    writeLog();

    while (1)
    {
        cmd_working_set = cmd_master_set;
        select(cmd_max_sd + 1, &cmd_working_set, NULL, NULL, NULL);
        for (int i = 0; i <= cmd_max_sd; i++)
        {
            memset(buffer, 0, BUFFER_SIZE);
            if (FD_ISSET(i, &cmd_working_set))
            {
                if (i == serverCmdFd)
                { // new clinet
                    new_cmd_socket = acceptClient(serverCmdFd);
                    FD_SET(new_cmd_socket, &cmd_master_set);
                    if (new_cmd_socket > cmd_max_sd)
                        cmd_max_sd = new_cmd_socket;

                    curr_log += "new client connected with fd " + to_string(new_cmd_socket);
                    writeLog();
                }
                else
                { // client sending msg
                    int bytes_received;
                    bytes_received = recv(i, buffer, BUFFER_SIZE, 0);
                    if (bytes_received == 0)
                    { // EOF
                        if (fdLoggedInUser.find(i) != fdLoggedInUser.end())
                        {
                            findUserByName(fdLoggedInUser[i])->logout();
                            fdLoggedInUser.erase(i);
                        }
                        fdLastRequest.erase(i);

                        curr_log += "Client on fd " + to_string(i) + " disconnected";
                        writeLog();

                        write(1, "Client disconnected!\n", 22);
                        close(i);
                        close(cmdDataFd[i]);
                        FD_CLR(i, &cmd_master_set);
                        auto it = cmdDataFd.find(i);
                        cmdDataFd.erase(it);
                        continue;
                    }
                    stringstream ss(buffer);
                    string command, argument;
                    getline(ss, command, ' ');
                    getline(ss, argument, '\n');
                    if (command.back() == '\n')
                        command.pop_back();
                    string response = handleCommand(command, argument, i);
                    strcpy(buffer, response.c_str());
                    curr_log += "Server response (fd = " + to_string(i) + ") was: " + buffer;
                    writeLog();

                    send(i, buffer, strlen(buffer), 0);
                }
            }
        }
    }
}

void exitLog(string log)
{
    time_t now = time(0);
    char *dt = strtok(ctime(&now), "\n");
    string newLog = "[";
    newLog += dt;
    newLog += "] ";
    newLog += log;
    newLog += "\n";

    ofstream logFile;
    logFile.open(string(SERVER_ABSOLUTE_PATH) + LOG_FILE_NAME, ios_base::app);
    logFile << newLog;
    logFile.close();
}

void signal_callback_handler(int signum)
{
    exitLog("Server is offline.");
    printf("\n");
    exit(signum);
}