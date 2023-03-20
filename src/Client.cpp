#include "../include/IncludeAndDefine.hpp"
#include "../include/Parser.hpp"

using namespace std;
char ABSOLUTE_PATH[BUFFER_SIZE];
string curr_log = "";



int connectServer(int port, string host) {
    int fd;
    struct sockaddr_in server_address;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(port); 
    server_address.sin_addr.s_addr = inet_addr(host.c_str());

    if (connect(fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) { // checking for errors
        printf("Error in connecting to server\n");
        exit(0);
    }

    return fd;
}

void writeLog(string curr_log, string log_path)
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

int main(int argc, char const *argv[]) {
    

    int data_socket, cmd_socket;
    char cmdBuff[BUFFER_SIZE] = {0}, dataBuff[BUFFER_SIZE] = {0};
    char msgtoServer[BUFFER_SIZE] = {0};

    auto inputs = parseJson(CONFIG_FILE);
    int cmd_port = stoi(inputs[COMMAND_PORT][0]);
    string host_name = inputs[HOST][0];
    bool is_loged_in = false;

    cmd_socket = connectServer(cmd_port, host_name);
    getcwd(ABSOLUTE_PATH, BUFFER_SIZE);

    printf("Welcome!\n");
    while (1) {
        if(is_loged_in)
            printf("\n-----------MAIN_PAGE----------\n%s\n", MAIN_PAGE);
        write(1, "Command -> ",11);
        memset(cmdBuff, 0, BUFFER_SIZE);
        read(0, cmdBuff, BUFFER_SIZE);
        send(cmd_socket, cmdBuff, strlen(cmdBuff), 0);
        string command = cmdBuff;
        stringstream ss(command);
        string currCommand;
        getline(ss, currCommand, ' ');
        if (currCommand.back() == '\n')
            currCommand.pop_back();

        memset(cmdBuff, 0, BUFFER_SIZE);
        recv(cmd_socket, cmdBuff, BUFFER_SIZE, 0);
        char FD = cmdBuff[0];
        memmove(cmdBuff, cmdBuff + 1, strlen(cmdBuff));
        string log_path = string(ABSOLUTE_PATH) + LOG_FILE_CLIENT + FD + ".txt";
        writeLog(cmdBuff, log_path );


        printf("\n-----------SERVER_RESPONSE-----------\n%s\n", cmdBuff);

        if (!strcmp(cmdBuff, ENTER_USER_DATA)){
            stringstream ss;
            string pass, purse, phone, address;
            for(int i = 0; i < 4; i++){
                write(1, "Command -> ",11);
                memset(cmdBuff, 0, BUFFER_SIZE);
                read(0, cmdBuff, BUFFER_SIZE);
                ss << cmdBuff ;
            }
            getline(ss, pass, '\n');
            getline(ss, purse, '\n');
            getline(ss, phone, '\n');
            getline(ss, address, '\n');
            string data = "userData " + pass + " " + purse + " " + phone + " " + address + "\n";
            int a = send(cmd_socket, data.c_str(), strlen(data.c_str()), 0);
            memset(cmdBuff, 0, BUFFER_SIZE);
            recv(cmd_socket, cmdBuff, BUFFER_SIZE, 0);
            FD = cmdBuff[0];
            memmove(cmdBuff, cmdBuff + 1, strlen(cmdBuff));
            printf("\n-----------SERVER_RESPONSE-----------\n%s\n", cmdBuff);
            continue;
        }

        if (!strcmp(cmdBuff, ENTER_NEW_DATA)){
            stringstream ss;
            string pass, phone, address;
            for(int i = 0; i < 3; i++){
                write(1, "Command -> ",11);
                memset(cmdBuff, 0, BUFFER_SIZE);
                read(0, cmdBuff, BUFFER_SIZE);
                ss << cmdBuff ;
            }
            getline(ss, pass, '\n');
            getline(ss, phone, '\n');
            getline(ss, address, '\n');
            string data = "newData " + pass + " " + phone + " " + address + "\n";
            int a = send(cmd_socket, data.c_str(), strlen(data.c_str()), 0);
            memset(cmdBuff, 0, BUFFER_SIZE);
            recv(cmd_socket, cmdBuff, BUFFER_SIZE, 0);
            char FD = cmdBuff[0];
            memmove(cmdBuff, cmdBuff + 1, strlen(cmdBuff));
            printf("\n-----------SERVER_RESPONSE-----------\n%s\n", cmdBuff);
            continue;
        }
        
        if(!strcmp(cmdBuff, SUCCESSFUL_LOGIN)){
            is_loged_in = true;
            continue;
        }   

        if (!strcmp(cmdBuff, SHOULD_LOGIN))
            continue;

        if (!strcmp(cmdBuff, SUCCESSFUL_LOGOUT)){
            is_loged_in = false;
            continue;
        }   
            
 
    }
   
    close(cmd_socket);
}