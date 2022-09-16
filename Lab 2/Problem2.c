#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main(int argc, char* argv[]){
    char* filepath = argv[1];
    int fd,ret;
    fd = open(filepath,O_RDONLY);
    if(fd == -1){
        perror("Error");
    }
    else{
        char c;
        ret = read(fd, &c, 1);
        while(ret != 0){
            printf("%c",c);
            ret = read(fd, &c, 1);
        }
        close(fd);
    }
        
//https://www.ibm.com/docs/en/i/7.2?topic=ssw_ibm_i_72/apis/write.htm
    return 0;
}