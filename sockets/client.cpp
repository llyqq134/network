#include <cstdlib>
#include <cstring>
#include <strings.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    char buffer[256];

    int sockfd, portno, n;
    struct sockaddr serv_addr;
    struct hostent *server;

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        perror("error opening socket");

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr, "error, no such host");
        exit(0);
    }

    inet_pton(AF_INET, "127.0.0.1", &serv_addr);

    if (connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0)
        perror("error connecting");

    printf("please enter your message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);

    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
        perror("error writing to socket");
    bzero(buffer, 256);

    n = read(sockfd, buffer, 255);
    if (n < 0)
        perror("error reading from socket");

    printf("%s", buffer);

    return 0;
}
