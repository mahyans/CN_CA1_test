#include "../include/Server.hpp"
using namespace std;

char SERVER_ABSOLUTE_PATH[BUFFER_SIZE];

void Server::setValue(map<string, vector<string>> inputs)
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

User *Server::findUserByName(string username_)
{
    for (auto &user : users)
        if (user.isValid(username_))
            return &user;
    return NULL;
}

Room *Server::findRoomByNumber(string num){
    for (auto &room : rooms)
        if (room.numMatches(num))
            return &room;
    return NULL;
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





string Server::handleCommand(string command, string argument, int userFd)
{
    stringstream ss;
    ss << userFd;
    string S_userFd = ss.str();
    try{
        curr_log += "Client (fd = " + to_string(userFd) + ") requested: " + command;
        writeLog();

    string argument1, argument2, argument3, argument4;
    
    

    if (command == SIGN_IN_COMMAND | command == CANCLE_COMMAND)
    {
        stringstream ss(argument);
        getline(ss, argument1, ' ');
        getline(ss, argument2, '\n');
    }
    else if (command == BOOK_COMMAND | command == USER_DATA)
    {
        stringstream ss(argument);
        getline(ss, argument1, ' ');
        getline(ss, argument2, ' ');
        getline(ss, argument3, ' ');
        getline(ss, argument4, '\n');
    }
    else if (command == ADD_COMMAND | command == MODIFY_COMMAND | command == NEW_DATA)
    {
        stringstream ss(argument);
        getline(ss, argument1, ' ');
        getline(ss, argument2, ' ');
        getline(ss, argument3, '\n');
    }
    else if (command == DELE_COMMAND || command == RENAME_COMMAND)
    {
        stringstream ss(argument);
        getline(ss, argument1, ' ');
        getline(ss, argument2, '\n');
    }
    else
        argument1 = argument;

    User* currUser = findUserByFd(userFd);
    
    if (command == SET_TIME_COMMAND)
    {
        try
        {
            setDate(argument);
            checkExpiredReservation();
            return S_userFd + SUCCESSFUL;
            curr_log += "Set time to "+ systemDate.toSting() + " (fd = " + to_string(userFd);
        }
        catch (...)
        {
            return S_userFd + BAD_ARGUMENT;
        }
    }

    else if (command == SIGN_UP_COMMAND)
    {
        if (fdLoggedInUser.find(userFd) != fdLoggedInUser.end())
            return S_userFd + NEED_TO_LOGOUT;

        if (findUserByName(argument1) == NULL)
        {
            fdLastRequest[userFd] = argument1;
            return S_userFd + ENTER_USER_DATA;
        }
        else
            return S_userFd + USER_ALREADY_EXIST;
    }

    else if (command == USER_DATA)
    {
        try
        {
            if (fdLastRequest.find(userFd) != fdLastRequest.end())
            {
                string username = fdLastRequest[userFd];
                User newUser(username, argument1, argument2, argument3, argument4);
                users.push_back(newUser);
                curr_log += "Signup  successfully (fd = " + to_string(userFd) + " )";
                writeLog();
                return S_userFd + SUCCESSFUL_SIGNUP;
                
            }
            else
                return S_userFd + BAD_SEQUENCE;
        }
        catch (...)
        {
            return S_userFd + BAD_ARGUMENT;
        }
    }

    else if (command == SIGN_IN_COMMAND)
    {
        if (fdLoggedInUser.find(userFd) != fdLoggedInUser.end())
            return S_userFd + NEED_TO_LOGOUT;
        User *currUser = findUserByName(argument1);
        if (currUser)
        {
            if (currUser->login(argument2))
            {
                currUser->updateFd(userFd);
                fdLoggedInUser[userFd] = argument1;
                curr_log += "Signin  successfully (fd = " + to_string(userFd) + ")";
                writeLog();
                return S_userFd + SUCCESSFUL_LOGIN;
            }
            else{
                return S_userFd + INVALID_USERNAME_PASS;
            }
        }
        else
            return S_userFd + INVALID_USERNAME_PASS;
    }

    else if (command == VIEW_USER_INFO)
    {
        return "\n--------YOUR_PROFILE----------\n" + currUser->toString();
    }

    else if (command == VIEW_ALL_USERS)
    {
        stringstream users_data;
        if (currUser->isAdmin())
        {
            users_data << "\n--------USER_LIST----------\n";
            for (auto user : users)
            {
                users_data << user.toString();
            }
            return S_userFd + users_data.str();
        }
        else
            return S_userFd + ACCESS_DENIED;
    }
    
    else if (command == VIEW_ROOMS_INFO)
    {
        stringstream ss;
        ss << "\n--------ROOMS_INFO----------\n";
        if (!currUser->isAdmin()){ 
            for(auto room : rooms){
                ss << room.toString();
            }
        }
        else{
            for(auto room : rooms){
                ss << room.toStringAdmin();
            }
        }
        return S_userFd + ss.str();
    }

    else if (command == BOOKING)
    {
        stringstream ss;
        ss << "* Format: book <RoomNumber> <NumOfBeds> <CheckinDate> <CheckoutDate>\n"
            << "* Help : RomNumber is number of room, NumOfBeds is number of beds.";
        return S_userFd + ss.str();
    }
   
    else if (command == BOOK_COMMAND){
        if(currUser->isAdmin())return S_userFd + ACCESS_DENIED;
        Room* wantedRoom = findRoomByNumber(argument1);
        int num_of_beds = stoi(argument2);
        if(wantedRoom){
            if(currUser->canAfford(wantedRoom->getPrice() * num_of_beds)){
                try{
                    Reservation newRes(currUser, num_of_beds, argument3, argument4);
                    if(wantedRoom->hasConflict(&newRes))return S_userFd + ROOM_IS_FULL;
                    else{
                        wantedRoom->addReservation(&newRes);
                        currUser->reduceMoney(wantedRoom->getPrice() * num_of_beds);
                        currUser->reservs.push_back("[room number]"+wantedRoom->getNum()+" "+newRes.toString());
                        return S_userFd + SUCCESSFUL;
                    } 
                }catch(...){
                    return S_userFd + BAD_ARGUMENT;
                }
            }
            else return S_userFd + NOT_ENOUGH_MONEY;
        }else return S_userFd + ROOM_NOT_FOUND;
    }
    
    else if (command == CANCELING)
    {
        stringstream ss;
        ss << "------------YOUR_RESERVATIONS---------------\n";
        for(auto res:currUser->reservs) ss << res;
        ss << "\n* Format: cancel <RoomNumber> <Num>\n"
            << "* Help : RomNumber is number of room. Num is numbe of reserved beds that you want to cancel.";
        return S_userFd + ss.str();
    }
    
    else if (command == CANCLE_COMMAND)
    {
        try{
            Room* wantedRoom = findRoomByNumber(argument1);
            if(!wantedRoom)return S_userFd + ROOM_NOT_FOUND;
            int num = stoi(argument2);
            if(currUser->reservs.size() < num)return S_userFd + RESERVATIONN_NOT_FOUND;
            if(wantedRoom->findNumOfreserveById(currUser->getId()) < num) return S_userFd + RESERVATIONN_NOT_FOUND; 
            wantedRoom->removeReservationById(currUser->getId(), num);
            return S_userFd + SUCCESSFUL;
        }catch(...){
            return S_userFd + INVALID_VAL;
        }
    }

    else if (command == PASSDAY)
    {
        return S_userFd + "\n* Format: passDay <value>\n* Help: value is the number of days.";
    }

    else if (command == PASS_DAY_COMMAND)
    {
        if (fdLoggedInUser.find(userFd) == fdLoggedInUser.end())
            return S_userFd + SHOULD_LOGIN;
        try
        {
            if (currUser->isAdmin())
            {
                systemDate.addDay(stoi(argument));
                cout << systemDate.toSting() << endl;
                checkExpiredReservation();
                return S_userFd + SUCCESSFUL;
            }
            return S_userFd + ACCESS_DENIED;
        }
        catch (...)
        {
            return S_userFd + BAD_ARGUMENT;
        }
    }
    
    else if (command == EDIT_INFO)
    {
        return S_userFd + ENTER_NEW_DATA;
    }

    else if (command == NEW_DATA){
        currUser->edit(argument1, argument2, argument3);
        return S_userFd + SUCCESSFUL_CHANGE;
    }

    else if (command == LEAVING_ROOM)
    {
        stringstream ss;
        ss << "\n* Format: room <Value> \n"
            << "* Help : Value is number of room.";
        return S_userFd + ss.str();
    }
    else if (command == ROOM_COMMAND)
    {
        try{
            Room* wantedRoom = findRoomByNumber(argument1);
            if(!wantedRoom)return S_userFd + ROOM_NOT_FOUND;
            if(currUser->isAdmin()){
                wantedRoom->removeAllReservation();
                return S_userFd + "The room was successfully emptied";
            }
            else{
                if(wantedRoom->findNumOfreserveById(currUser->getId()) == 0) return S_userFd + RESERVATIONN_NOT_FOUND; 
                wantedRoom->removeReservationById(currUser->getId(), 1);
                return S_userFd + SUCCESSFUL_LEAVING;
            }
        }catch(...){
            return S_userFd + INVALID_VAL;
        }
    }
    else if (command == EDIT_ROOMS){
        stringstream ss;
        ss << "\n* Format: add <RoomNum> <maXCapacity> <Price>\n"
            << "* Format: modify <RoomNum> <newMaXCapacity> <newPrice>\n"
            << "* Format: remove <RoomNum> ";
        return S_userFd + ss.str();
    }
    
    else if (command == MODIFY_COMMAND){
        if (!currUser->isAdmin())return S_userFd + ACCESS_DENIED;
        Room* wantedRoom = findRoomByNumber(argument1);
        if(!wantedRoom) return S_userFd + ROOM_NOT_FOUND;
        wantedRoom->editRoom(stoi(argument2), stoi(argument3));
        return S_userFd + SUCCESSFUL_MODIFY;
    }

    else if (command == REMOVE_COMMAND){
        if (!currUser->isAdmin())return S_userFd + ACCESS_DENIED;
        for(int i = 0; i < rooms.size(); i++){
            if(rooms[i].numMatches(argument1)){
                rooms.erase(rooms.begin()+i);
                return S_userFd + SUCCESSFUL_DELETE;
            }
        }
    }

    else if (command == ADD_COMMAND){
        if (!currUser->isAdmin())return S_userFd + ACCESS_DENIED;
        Room* wantedRoom = findRoomByNumber(argument1);
        if(wantedRoom) return S_userFd + ROOM_ALREADY_EXISTS;
        Room newRoom(argument1, stoi(argument3), stoi(argument2), stoi(argument2));
        rooms.push_back(newRoom);
        return S_userFd + SUCCESSFUL_ADD;
    }

    else if (command == LOGOUT)
    {
        User* currUser = findUserByFd(userFd);
        fdLoggedInUser.erase(userFd);
        currUser->logout();
        return S_userFd + SUCCESSFUL_LOGOUT;
    }

    return S_userFd + SYNTAX_ERROR;
    }catch(...){
        return S_userFd + INVALID_VAL;
    }
    
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
            User* user = findUserById(id);
            user->reservs.push_back(newRes.toString());
            newRoom.addReservation(&newRes);
            index += 1;
        }
        rooms.push_back(newRoom);
    }
}

void Server::checkExpiredReservation(){
    for(int j = 0; j < rooms.size(); j++){
        for(int i = 0; i< rooms[j].users.size(); i++){
            if(rooms[j].users[i].getInterval(0) < systemDate.toInt()){
                
                rooms[j].users.erase(rooms[j].users.begin()+i);

            }
        }
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
                    updateJsonFiles();
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
                        updateJsonFiles();
                        write(1, "Client disconnected!\n", 22);
                        close(i);
                        
                        FD_CLR(i, &cmd_master_set);
                        continue;
                    }
                    stringstream ss(buffer);
                    string command, argument;
                    getline(ss, command, ' ');
                    getline(ss, argument, '\n');
                    if (command.back() == '\n')
                        command.pop_back();
                    string response = handleCommand(command, argument, i);
                    updateJsonFiles();
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

void Server::updateJsonFiles()
{
    stringstream rs, us;
    for(auto room : rooms){
        rs << room.toStringAdmin() << endl;
    }
    ofstream MyFile("updatedRooms.txt");
    MyFile << rs.str();
    MyFile.close();

    for(auto user : users){
        us << user.toString() << endl;
    }
    ofstream MyFile2("updatedUsers.txt");
    MyFile2 << us.str();
    MyFile2.close();    
}

void signal_callback_handler(int signum){
    exitLog("Server is offline.");
    printf("\n");
    exit(signum);
}