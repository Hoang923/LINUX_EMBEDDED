#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>     
#include <netinet/in.h>     
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_BACKLOG 50
#define BUFF_SIZE 256

void chat_func(int new_socket_sd)
{
    int num_read, num_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];

    while(1){
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);

        num_read = read(new_socket_sd, recvbuff, BUFF_SIZE);

        if (num_read == -1){
            fprintf(stderr, "read() failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp("exit", recvbuff, 4) == 0){
            printf("\nServer close...\n");
            break;
        }

        printf("\nMessage from client: %s\n", recvbuff);

        printf("Respond: ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        num_write = write(new_socket_sd, sendbuff, sizeof(sendbuff));
        if (num_write == -1){
            fprintf(stderr, "write() failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp("exit", sendbuff, 4) == 0){
            printf("Server close...\n");
            break;
        }
    }
    close(new_socket_sd);
}

int main(int argc, char *argv[])
{
    int port_no;
    int server_sd, new_socket_sd;
    struct sockaddr_in serv_addr;

    if (argc != 2){
        printf("Command: ./server <port_no>\n");
        exit(EXIT_FAILURE);
    }

    port_no = atoi(argv[1]);

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));

    /*socket*/
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
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

    /*listen*/
    if (listen(server_sd, LISTEN_BACKLOG) == -1){
        fprintf(stderr, "listen() failed\n");
        exit(EXIT_FAILURE);
    }

    printf("server is listening at port: %d \n...\n", port_no);
    new_socket_sd = accept(server_sd, NULL, NULL);
    if (new_socket_sd == -1){
        fprintf(stderr, "accept() failed\n");
        exit(EXIT_FAILURE);
    }

    system("clear");

    printf("Server connection\n");
    chat_func(new_socket_sd);

    close(new_socket_sd);
    return 0;
}