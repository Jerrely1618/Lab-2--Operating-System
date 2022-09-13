#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main(int argc, char* argv[]){
    char* filepath = argv[1];
    int ret,returnval,fd;
    char buf[1024];
    
    returnval = access(filepath, F_OK);
    if(returnval == 0){
        fd = open(filepath,O_RDWR);
        ret = read(fd, buf, sizeof(buf)-1);
        buf[ret] = 0x00;
        printf("%s\n", buf);
        close(fd);
    }
    else{
        if(errno == ENOENT){
            printf ("%s does not exist\n", filepath);
        }
        else if(errno == EACCES){
            printf ("%s is not accessible\n", filepath);
        }
    }
        
//https://www.ibm.com/docs/en/i/7.2?topic=ssw_ibm_i_72/apis/write.htm
    return 0;
}