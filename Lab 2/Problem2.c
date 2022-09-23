#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main(int argc, char* argv[]){
    if(argc !=2){
        printf("File parameter is missing\n");
        return 1;
    }
    char* filepath = argv[1];
    int fd,ret;

    //Opens the input file with Read only permissions
    fd = open(filepath,O_RDONLY);
    
    if(fd == -1){
        perror("Error");
    }
    else{
        //Start reading the document with the first char using read()
        //The open document and a char variable is passed
        char c;
        ret = read(fd, &c, 1);

        //The loop repeats until read() returns 0
        //0 means that no char was read
        while(ret != 0){
            printf("%c",c);
            ret = read(fd, &c, 1);
        }

        //close the file
        close(fd);
    }
    return 0;
}