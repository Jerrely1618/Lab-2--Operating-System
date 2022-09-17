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
    int sf,df,ret,writ;
    
    sf = open(SourceFile,O_RDONLY);
    df = open(DestinationFile,O_WRONLY);
    
    if(sf == -1 || df == -1){
        perror("Error");
    }
    else{
        ret = 1;
        while(ret != 0){
            char* buf;
            for(int i = 0; i < 100;i++){
                char c;
                ret = read(sf, &c, 1);
                if (ret == 0){break;}
                if(c == '1'){
                    c = 'L';
                }
                writ = write(df,&c,1);
            }
            buf = "XYZ";
            writ = write(df,buf,3);
        }

        close(sf);
        close(df);
    }
    
    
    return 0;
}