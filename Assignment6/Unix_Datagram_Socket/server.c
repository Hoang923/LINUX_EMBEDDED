#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>     
#include <sys/un.h>
#include <unistd.h>

#define BUFF_SIZE 256
#define SOCKET_PATH "./socket"

int main(int argc, char *argv[])
{
    int server_sd;
    struct sockaddr_un serv_addr, client_addr;
    char buff[BUFF_SIZE];

    memset(&serv_addr, 0, sizeof(struct sockaddr_un));
    memset(&client_addr, 0, sizeof(struct sockaddr_un));

    /*socket*/
    server_sd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (server_sd == -1){
        fprintf(stderr, "socket() failed\n");
        exit(EXIT_FAILURE);
    }

    remove(SOCKET_PATH);

    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, SOCKET_PATH, sizeof(serv_addr.sun_path) - 1);

    /*bind*/
    if (bind(server_sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
        fprintf(stderr, "bind() failed\n");
        exit(EXIT_FAILURE);
    }

    system("clear");
    printf("WAITING TO CLIENT...\n");

    socklen_t client_len = sizeof(client_addr);

    while(1){
        /*recvfrom*/
        if (recvfrom(server_sd, buff, BUFF_SIZE, 0, (struct sockaddr *)&client_addr, &client_len) == -1){
            fprintf(stderr, "recvfrom() failed\n");
            exit(EXIT_FAILURE);
        }
        printf("Message from client: %s", buff);
        if (strncmp("exit", buff, 4) == 0){
            printf("Server close...\n");
            break;
        }

        const char reply[] = "Server received message\n";
        
        /*sendto*/
        if (sendto(server_sd, reply, sizeof(reply), 0, (struct sockaddr *)&client_addr, client_len) == -1){
            fprintf(stderr, "sendto() failed\n");
            exit(EXIT_FAILURE);
        }
    }
    close(server_sd);
    remove(SOCKET_PATH);
    return 0;
}