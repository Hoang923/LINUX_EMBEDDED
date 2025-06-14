#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>     
#include <netinet/in.h>     
#include <arpa/inet.h>
#include <unistd.h>

#define BUFF_SIZE 256

void chat_func(int new_socket_sd)
{
    int num_read, num_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];

    while(1){
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);

        printf("Enter the message: ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        num_write = write(new_socket_sd, sendbuff, sizeof(sendbuff));
        if (num_write == -1){
            fprintf(stderr, "write() failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp("exit", sendbuff, 4) == 0){
            printf("Server exit...\n");
            break;
        }

        num_read = read(new_socket_sd, recvbuff, BUFF_SIZE);
        if (num_read == -1){
            fprintf(stderr, "read() failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp("exit", recvbuff, 4) == 0){
            printf("\nServer exit...\n");
            break;
        }
        printf("\nMessage from server: %s\n", recvbuff);      
    }
    close(new_socket_sd);
}

int main(int argc, char *argv[])
{
    int port_no;
    int server_sd, new_socket_sd;
    struct sockaddr_in serv_addr;

    if (argc != 3){
        printf("command: ./client <inet> <port_no>\n");
        exit(EXIT_FAILURE);
    }

    port_no = atoi(argv[2]);

    memset(&serv_addr, 0, sizeof(serv_addr));

    /*socket*/
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sd == -1){
        fprintf(stderr, "socket() failed\n");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);

    /*connect*/
    new_socket_sd = connect(server_sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (new_socket_sd == -1){
        fprintf(stderr, "connect() failed\n");
        exit(EXIT_FAILURE);
    }

    system("clear");

    chat_func(server_sd);

    close(server_sd);
    return 0;
}