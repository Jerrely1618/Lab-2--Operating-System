#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[]){
    int pipefd[2];
    int readFile,ret,writ,fr = fork();
    char c;

    if(pipe(pipefd) == -1){
        perror("Error");
        exit(EXIT_FAILURE);
    }

    if(fr == 0){
        close(pipefd[0]);

        readFile = open("readme.txt",O_RDONLY);
        if(readFile == -1){perror("Error");}

        while(ret!=0){
            ret = read(readFile,&c,1);
            writ = write(pipefd[1],&c,1);
        }
        close(pipefd[1]);
        _exit(EXIT_SUCCESS);
    }
    else{
        close(pipefd[1]);
        wait(NULL);
        while(ret!=0){
            ret = read(pipefd[1],&c,1);
            writ = write(STDOUT_FILENO,&c,1);
        }
        close(pipefd[0]);
        exit(EXIT_SUCCESS);

    }



    return 0;
}