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
        perror("error socket\n");
        exit(1);
    }

    struct sockaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(54132);
    std::cout << "ok1\n";
    if (connect(s, (sockaddr *) &servAddr, sizeof(servAddr)) == -1) {
        perror("connection failed\n");
        exit(1);
    }
    std::cout << "ok2\n";
    char msg[256];

    while(true) {
        printf("please enter a message: ");
        memset(msg, 0, 256);
        fgets(msg, 255, stdin);

        int n = write(s, msg, strlen(msg));
        if (n == -1) {
            perror("error writing to socket\n");
            exit(1);
        }

        memset(msg, 0, 256);
        n = read(s, msg, 255);

        if (n == -1) {
            perror("error read from socket\n");
            exit(1);
        }

        printf("%s\n", msg);
    }

    close(s);

    return 0;
}
