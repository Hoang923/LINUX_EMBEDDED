#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>     
#include <netinet/in.h>     
#include <arpa/inet.h>
#include <unistd.h>

#define BUFF_SIZE 256

int main(int argc, char *argv[])
{
    int server_sd;
    int port_no;
    struct sockaddr_in serv_addr;
    char buff[BUFF_SIZE];
    char recv[BUFF_SIZE];

    if (argc != 3){
        printf("command: ./client <inet> <port_no>\n");
        exit(EXIT_FAILURE);
    }

    port_no = atoi(argv[2]);

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));

    /*socket*/
    server_sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sd == -1){
        fprintf(stderr, "socket() failed\n");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

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
    return 0;
}