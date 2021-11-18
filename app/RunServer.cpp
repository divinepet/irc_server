#include "../server/Server.hpp"

#define f(a) msg.find(a) != string::npos

int main(int argc, char *argv[]) {
	string msg = "e";
	if (msg.find("a") != string::npos)
		cout << "ha" << endl;
	if (f("e"))
		cout << "ee" << endl;
//    system("clear");
//    if (argc < 3) {
//        printf("Usage: ./ircserv <port> <password>\n");
//		return 1;
//	}
//    try {
//		int port = atoi(argv[1]);
//		Server serv(port, argv[2]);
//    	serv.start();
//	} catch (const char* s) {
//		cout << s << endl;
//	} catch (exception &e) {
//		cout << e.what() << endl;
//    }
    return 0;
}
