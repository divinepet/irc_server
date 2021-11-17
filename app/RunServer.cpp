#include "../server/Server.hpp"

int main(int argc, char *argv[]) {

//	pthread_t request_thread;
//	A a(4);
//	pthread_create(&request_thread, NULL, &pr, &a);
//	usleep(100000);
//	cout << a.getId() << endl;
    system("clear");
    if (argc < 3) {
        printf("Usage: ./ircserv <port> <password>\n");
		return 1;
	}
    try {
		int port = atoi(argv[1]);
		Server serv(port, argv[2]);
    	serv.start();
	} catch (const char* s) {
		cout << s << endl;
	} catch (exception &e) {
		cout << e.what() << endl;
    }
    return 0;
}
