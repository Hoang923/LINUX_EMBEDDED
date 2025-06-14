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
    struct sockaddr_in serv_addr, client_addr;
    char buff[BUFF_SIZE];


    if (argc != 2){
        printf("command: ./server <port_no>\n");
        exit(EXIT_FAILURE);
    }

    port_no = atoi(argv[1]);

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    /*socket*/
    server_sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sd == -1){
        fprintf(stderr, "socket() failed\n");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

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
    return 0;
}