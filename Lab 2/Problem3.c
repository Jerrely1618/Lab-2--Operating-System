#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    //Tried with deFile.txt and soFile.txt
    if(argc !=3){
        printf("File parameter is missing\n");
        return 1;
    }
    char* SourceFile = argv[1];
    char* DestinationFile = argv[2];
    int sf,df,ret,writ,off;
    
    //Open the source file to read and the destination file to write
    sf = open(SourceFile,O_RDONLY);
    df = open(DestinationFile,O_WRONLY);
    
    if(sf == -1 || df == -1){
        perror("Error");
    }
    else{
        
        char c;
        ret = read(sf, &c, 1);

        //Read the file until no char is left
        while(ret != 0){
            writ = write(df,&c,1);
            ret = read(sf, &c, 1);
        }

        //Close both files
        close(sf);
        close(df);
    }
    
    
    return 0;
}