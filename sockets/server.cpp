#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <sys/types.h>

int main() { 
	int s = socket(AF_INET, SOCK_STREAM, 0);

	if (s == -1) {
		perror("socket error\n");
		exit(1);
	}

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54132);
    //inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    
    if (bind(s, (sockaddr *) &hint, sizeof(hint)) == -1) {
        perror("bind error\n");
        exit(1);
    }

    if(listen(s, SOMAXCONN) == -1) {
        perror("listen error\n");
        exit(1); 
    }

    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientSocket = accept(s, (sockaddr *)&client, &clientSize);

    if (clientSocket == -1) {
        perror("accept error\n");
        exit(1);
    }

    close(s);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, sizeof(client), 
            host, NI_MAXHOST, svc, NI_MAXSERV, 0);

    if (result) {
        std::cout << host << " connected on " << svc << std::endl;
    }
    else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on " << svc << std::endl;
    }

    char msg[4096];
    std::cout << "server is waiting\n";
    while(true) {
        memset(msg, 0, 4096);
        int byteRecv = recv(clientSocket, msg, 4096, 0);

        if (byteRecv == -1) {
            perror("connection issue\n");
            break;
        }

        if (byteRecv == 0) {
            std::cout << "The client disconnected\n";
            break;
        }

        std::cout << "Received: " << std::string(msg, 0, byteRecv) << std::endl;

        send(clientSocket, msg, byteRecv + 1, 0);
    }

    close(clientSocket);
}
