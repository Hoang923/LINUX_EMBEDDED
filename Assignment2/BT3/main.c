#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char *argv[])
{
    char *filename = argv[1];
    struct stat sb;

    if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
    }

    if (lstat(filename, &sb) == -1) {
       printf("fail");
       exit(EXIT_FAILURE);
    }
    
    printf("File type: ");
    switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }
    
    printf("Filename: %s\n", filename);
    printf("File size: %jd bytes\n",(intmax_t) sb.st_size);
    printf("Last file modification: %s", ctime(&sb.st_mtime));

    exit(EXIT_SUCCESS);
}