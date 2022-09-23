#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main(int argc, char* argv[]){
    if(argc !=3){
        printf("File parameter is missing\n");
        return 1;
    }
    char* SourceFile = argv[1];
    char* DestinationFile = argv[2];
    int sf,df,ret,writ;

    //Open the source file to read and the destination file to write
    sf = open(SourceFile,O_RDONLY);
    df = open(DestinationFile,O_WRONLY);
    
    if(sf == -1 || df == -1){
        perror("Error");
    }
    else{
        ret = 1;

        //The loop will close when all characters of the file have been read (ret == 0)
        while(ret != 0){
            
            //Read 100 characters at a time
            for(int i = 0; i < 100;i++){
                char c;
                ret = read(sf, &c, 1);
    
                //If there are less than 100 characters left we break 
                if (ret == 0){break;}
                
                //Subtitute '1' to 'L'
                if(c == '1'){
                    c = 'L';
                }

                //Write it on the destination file
                writ = write(df,&c,1);
            }
            //Write a string with XYZ after the 100 characters
            char* buf;
            buf = "XYZ";
            writ = write(df,buf,3);
        }
        //Close both files
        close(sf);
        close(df);
    }
    
    
    return 0;
}