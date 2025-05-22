
#include<stdio.h> 
#include<stdlib.h>
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 
  
int main (int argc, char *argv[]) 
{ 
    if (argc != 5){
        printf("%s filename numb_bytes [r/w] \"Hello\"\n", argv[0]);
        return 1;
    }
    
    char *filename = argv[1];
    int numb_bytes = atoi(argv[2]);
    char mode = argv[3][0];
    char *data = argv[4];
     
    int fd; 
    int numb_read, numb_write;
    char buffer[100];

    fd = open("hello.txt", O_RDWR);         
    if (-1 == fd) { 
	printf("open() hello.txt failed\n");
    close(fd);
    return 1;
    }  

    if (mode == 'r'){
        numb_read = read(fd, buffer, numb_bytes);
        if (numb_read == -1){
            printf("read() hello.txt failed\n");
            close(fd);
            return 1;
        }
        printf("%s",buffer);
    }
    else if (mode == 'w'){
        int len = strlen(data);
        int bytes_to_write = numb_bytes < len ? numb_bytes : len;

        numb_write = write(fd, data, bytes_to_write);
        if (numb_write == -1 ){
            printf("write() hello.txt failed\n");
            close(fd);
            return 1;
        }
    } else{
        printf("NO MODE\n");
        close(fd);
        return 1;
    }

    
    
    close(fd); 
  
    return 0; 
} 