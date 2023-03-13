#include "../include/IncludeAndDefine.hpp"
#include "../include/Parser.hpp"

using namespace std;

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

int main(int argc, char const *argv[]) {
    int data_socket, cmd_socket;
    char cmdBuff[BUFFER_SIZE] = {0}, dataBuff[BUFFER_SIZE] = {0};
    char msgtoServer[BUFFER_SIZE] = {0};

    auto inputs = parseJson(CONFIG_FILE);
    int cmd_port = stoi(inputs[COMMAND_PORT][0]);
    string host_name = inputs[HOST][0];
    bool is_loged_in = false;

    cmd_socket = connectServer(cmd_port, host_name);

    printf("Welcome!\n");
    while (1) {
        if(is_loged_in)
            printf("%s\n", MAIN_PAGE);
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
        printf("%s\n", cmdBuff);

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
            printf("%s\n", cmdBuff);
            continue;
        }

        if(!strcmp(cmdBuff, SUCCESSFUL_LOGIN)){
            is_loged_in = true;
            continue;
        }   

        if (!strcmp(cmdBuff, SHOULD_LOGIN))
            continue;
        if(string(currCommand) == LS_COMMAND || string(currCommand) == RETR_COMMAND) {
            memset(dataBuff, 0, BUFFER_SIZE);
            recv(data_socket, dataBuff, BUFFER_SIZE, 0);
            if(!dataBuff)
                continue;
            printf("The data recieved from server is as follows:\n%s\n", dataBuff);
        } 
        if(string(currCommand) == RETR_COMMAND) {
            stringstream ss(dataBuff);
            string fileName, dump;
            getline(ss, fileName, ':');
            getline(ss, dump, '\n');
            int sizeOfFilename = fileName.size()+1;
            string res = string(dataBuff).substr(sizeOfFilename+1);
            ofstream out("copy_of_"+string(fileName));
            out << res;
            out.close();
        } 
    }
    
    close(cmd_socket);
}