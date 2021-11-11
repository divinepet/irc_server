#include "../server/Server.hpp"

int main(int argc, char *argv[]) {
    system("clear");
    int port = -1;
	int pass = -1;
    if (argc < 3)
        printf("Usage: ./ircserv <port> <password>\n");
    else {
        port = atoi(argv[1]);
		pass = atoi(argv[2]);
	}

    try {
		Server serv(port, pass);
    	serv.start();
	} catch (const char* s) {
		cout << s << endl;
	}
    return 0;
}
