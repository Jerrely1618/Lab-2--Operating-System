#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main(int argc, char* argv[]){
    int fd;
    if(argc !=2){
        printf("File parameter is missing\n");
        return 1;
    }

    //Open the document if it exist else create it
    fd = open(argv[1],O_CREAT|O_RDWR,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(fd == -1){
        printf("\n open () failed with error [%s]\n", strerror(errno));
        return 1;
    }
    else {
        printf("\n Open() successful\n");
    }
    //Close the file
    close(fd);
    return 0;
}