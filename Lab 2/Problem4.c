#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main(int argc, char* argv[]){
    char* SourceFile = argv[1];
    char* DestinationFile = argv[2];
    int sf,df,off,ret,writ;
    
    sf = open(SourceFile,O_RDONLY);
    df = open(DestinationFile,O_WRONLY);
    
    if(sf == -1 || df == -1){
        perror("Error");
    }
    else{
        char c;
        ret = read(sf, &c, 1);
        while(ret != 0){
            char * buf;
            writ = write(df,&c,1);
            ret = read(sf, &c, 1);
        }
        char* buf = "XYZ";
        writ = write(df,buf,3);

        close(sf);
        close(df);
    }
    
    
    return 0;
}