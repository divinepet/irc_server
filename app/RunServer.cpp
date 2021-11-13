#include "../server/Server.hpp"
#include "../services/sha256.hpp"

int main(int argc, char *argv[]) {
    system("clear");
    int port;
    if (argc < 3) {
        printf("Usage: ./ircserv <port> <password>\n");
		return 1;
	}
    else
        port = atoi(argv[1]);

    try {
		Server serv(port, argv[2]);
    	serv.start();
	} catch (const char* s) {
		cout << s << endl;
	}
    return 0;
}
