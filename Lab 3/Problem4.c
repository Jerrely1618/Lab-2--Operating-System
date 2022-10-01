#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int pipefd[2];
    int readFile = 1,ret,writ,size;
    char* file = "readme.txt";
    char c;
    if(pipe(pipefd) == -1){
        perror("Error");
    }
    int lg = fork();
    readFile = open(file,O_RDWR);
    
    if(lg == 0){
        close(pipefd[0]);
        if(readFile == -1){perror("Error");}

        ret = read(readFile,&c,1);
        while(ret != 0){
            size++;
            writ = write(pipefd[1],&c,1);
            ret = read(readFile,&c,1);
        }
        close(pipefd[1]);
    }
    else if (lg > 0){
        int stat;
        waitpid(lg,&stat,0);
        close(pipefd[1]);
        lseek(readFile,0,SEEK_END);
        writ = write(readFile,"\nParent is writing: ",20);
 
        ret = read(pipefd[0], &c, 1);
        while(ret != 0){
            writ = write(readFile,&c,1);
            ret = read(pipefd[0],&c,1);
        }
        close(pipefd[0]);
    }
    else{
        perror("Error");
    }

    return 0;
}