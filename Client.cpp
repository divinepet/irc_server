#include "Client.hpp"
#include "Helper.h"

Client::Client() {
    host = DEFAULT_SERVER;
    port = 5000;
}

Client::Client(const char* __host,int __port) {
    host = __host;
    port = __port;
}

Client::~Client() {
    close(socket_fd);
}

bool Client::connecting() {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) {
        printf("Error occurred while opening socket.\n");
        return false;
    }

    s_server = gethostbyname(host);
    if (s_server == NULL) {
        fprintf(stderr,"Error, no such host\n");
        return false;
    }

    bzero((char *) &s_serverAddr, sizeof(s_serverAddr));
    s_serverAddr.sin_family = AF_INET;

    bcopy((char *)s_server->h_addr, (char *)&s_serverAddr.sin_addr.s_addr, s_server->h_length);
    s_serverAddr.sin_port = htons(port);

    if (connect(socket_fd,(struct sockaddr *) &s_serverAddr,sizeof(s_serverAddr)) < 0) {
        printf("Error occurred while connecting to the server.\n");
        return false;
    }
    return true;
}

bool Client::writing(const char* __str) {
    int response = write(socket_fd, __str, strlen(__str));

    if (response < 0) {
        printf("Error occurred while writing to the socket.\n");
        return false;
    }
    return true;
}

string Client::reading() {
    char buf[BUFFER_SIZE];
    bzero(buf, BUFFER_SIZE);
    int response = read(socket_fd, buf, BUFFER_SIZE);

    if (response < 0) {
        printf("Error occurred while reading from socket.\n");
        string tmp = string("");
        return tmp;
    } else
        return string(buf);
}

int main(int argc, char *argv[])
{
    string _host = DEFAULT_SERVER;
    int port = DEFAULT_PORT;
    system("clear");
    if (argc < 3) {
        printf("Usage : %s <host> <port>\n",argv[0]);
        printf("No host or/and port specified. Using default settings.\n");
    } else {
        _host = string(argv[1]);
        port = atoi(argv[2]);
    }

    Client c(_host.c_str(), port);

    if(!c.connecting())
        Helper::Error("Can't connect to the server.\n");
    else
        printf("Successfully connected to the server %s:%i.\n", _host.c_str(), port);

    printf("Place your orders as <item name> <quantity>.\n");

    string sRead = c.reading();
    printf("%s\n", sRead.c_str());

    while (true) {
        char buf[BUFFER_SIZE];
        printf("Client: ");
        bzero(buf, BUFFER_SIZE);
        fgets(buf, BUFFER_SIZE, stdin);

        if (!c.writing(buf))
            printf("Can't send the message to the server.\n");

        string sRead = c.reading();
//        string sReq = sRead;

        if (sRead.empty())
            printf("Error occurred while reading from the socket.\n");
        else {
//            double dResponse = atof(sRead.c_str());
//
//            if (dResponse == -1) {
//                printf("Invalid request.\n");
//            }
//            else if (dResponse == -2) {
//                printf("Out of stock for %s\n", buf);
//            } else if (dResponse > 0) {
//                printf("Order %s Placed at %.2f \n\n", buf, dResponse);
//            } else {
//                printf("Stock : \n%s \n", sRead.c_str());
//            }
        }
    }
    return 0;
}
