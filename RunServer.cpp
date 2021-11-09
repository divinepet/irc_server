#include "Server.hpp"
#include "Service.hpp"
#include "MessageParse.hpp"

int main(int argc, char *argv[]) {
	MessageParse msgParse;
	char *buf = strdup("hello");
	msgParse.splitMessage(buf);
//    system("clear");
//    int port = -1;
//    if (argc < 2)
//        printf("No port is provided.\n");
//    else
//        port = atoi(argv[1]);
//
//    Server serv(port);
//    serv.start();
    return 0;
}
