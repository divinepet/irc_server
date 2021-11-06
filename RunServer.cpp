#include "Server.hpp"

int main(int argc, char *argv[]) {
    system("clear");
    int iPort = -1;
    if (argc < 2)
        printf("No port is provided.\n");
    else
        iPort = atoi(argv[1]);

    Server sServer(iPort);
    sServer.start();
    return 0;
}
