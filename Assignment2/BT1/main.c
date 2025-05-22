#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 
  
int main (void) 
{ 
    int fd; 
    int numb_write;
  
    fd = open("hello.txt", O_RDWR | O_APPEND);         
    if (-1 == fd) { 
	printf("open() hello.txt failed\n");
    return 1;
    }      
 
    lseek(fd, 0, SEEK_SET);
    numb_write = write(fd, "hello ", strlen("hello "));
    printf("Write %d bytes to hello.txt\n", numb_write);
    
    close(fd); 
  
    return 0; 
} 