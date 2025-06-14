#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>     
#include <sys/un.h>
#include <unistd.h>

#define BUFF_SIZE 256
#define SOCKET_PATH "./socket"
#define CLIENT_PATH "./client_socket"

int main(int argc, char *argv[])
{
    int server_sd;
    int port_no;
    struct sockaddr_un serv_addr, client_addr;
    char buff[BUFF_SIZE];
    char recv[BUFF_SIZE];

    memset(&serv_addr, 0, sizeof(struct sockaddr_un));
    memset(&client_addr, 0, sizeof(client_addr));

    /*socket*/
    server_sd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (server_sd == -1){
        fprintf(stderr, "socket() failed\n");
        exit(EXIT_FAILURE);
    }

    remove(CLIENT_PATH);

    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, SOCKET_PATH, sizeof(serv_addr.sun_path) - 1);
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, CLIENT_PATH, sizeof(client_addr.sun_path) - 1);

// Bind socket
if (bind(server_sd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
    perror("bind() failed");
    exit(EXIT_FAILURE);
}

    socklen_t addr_len = sizeof(serv_addr);

    system("clear");

    while(1){
        printf("Enter the message: ");
        fgets(buff, BUFF_SIZE, stdin);

        /*sendto*/
        if (sendto(server_sd, buff, sizeof(buff), 0, (struct sockaddr *)&serv_addr, addr_len) == -1){
            fprintf(stderr, "sendto() failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp("exit", buff, 4) == 0){
            printf("Server close...\n");
            break;
        }

        /*recvfrom*/
        if (recvfrom(server_sd, recv , BUFF_SIZE, 0, NULL, NULL) == -1){
            fprintf(stderr, "recvfrom() failed\n");
            exit(EXIT_FAILURE);
        }
        printf("%s\n", recv);
    }
    close(server_sd);
    remove(CLIENT_PATH);
    return 0;
}