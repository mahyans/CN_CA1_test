#include "../include/IncludeAndDefine.hpp"
#include "../include/Parser.hpp"

using namespace std;

int connectServer(int port) {
    int fd;
    struct sockaddr_in server_address;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(port); 
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

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
    int cmd_port = stoi(inputs[COMMAND_CHANNEL_PORT][0]);
    int data_port = stoi(inputs[DATA_CHANNEL_PORT][0]);

    data_socket = connectServer(data_port);
    cmd_socket = connectServer(cmd_port);

    printf("Welcome!\n");
    while (1) {
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
    close(data_socket);
    close(cmd_socket);
}