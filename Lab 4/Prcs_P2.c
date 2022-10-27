#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    char* SourceFile = "source.txt";
    char* DestinationFile = "destination1.txt";
    char* DestinationFile2 = "destination2.txt";
    int sf,df,df2,ret,writ;
    //Open the source file to read and the destination file to write
    sf = open(SourceFile,O_RDONLY);
    df = open(DestinationFile,O_WRONLY);
    df2 = open(DestinationFile2,O_WRONLY);
    
    if(sf == -1 || df == -1 || df2 == -1){
        perror("Error");
    }
    else{
        ret = 1;

        //The loop will close when all characters of the file have been read (ret == 0)
        while(ret != 0){
            for(int i = 0; i < 100;i++){//100 characters are read into destination file 2
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
            for(int i = 0; i < 50;i++){//50 characters are read into destination file 2
                char c;
                ret = read(sf, &c, 1);
                //If there are less than 50 characters left we break 
                if (ret == 0){break;}
                //Subtitute '3' to 'e'
                if(c == '3'){
                    c = 'E';
                }
                //Write it on the destination file 2
                writ = write(df2,&c,1);
            }
        }
        //Close both files
        close(sf);
        close(df);
        close(df2);
    }
    return 0;
}