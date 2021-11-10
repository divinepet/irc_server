#include "../server/Server.hpp"
#include "../services/Service.hpp"
#include "../services/MessageParse.hpp"

int main(int argc, char *argv[]) {
    system("clear");
    int port = -1;
    if (argc < 2)
        printf("No port is provided.\n");
    else
        port = atoi(argv[1]);

    Server serv(port);
    serv.start();
    return 0;
}
