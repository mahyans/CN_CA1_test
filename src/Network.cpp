#include "../include/IncludeAndDefine.hpp"
#include "../include/Server.hpp"
#include "../include/Parser.hpp"
using namespace std;
Server* Server ::serverPtr = NULL;

int main(int argc, char const *argv[]) {
    auto inputs = parseJson(CONFIG_FILE);
    Server* server = Server::getInstance();
    server->setValue(inputs);
    signal(SIGINT, signal_callback_handler);

    //uncomment to see server info ("config.json")
    //server.printServer();

    server->run();
}
