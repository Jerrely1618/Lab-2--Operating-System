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
    //Initialize the variables
    int pipefd[2];
    int readFile = 1,ret,writ,size;
    char* file = "readme.txt";
    char c;

    if(pipe(pipefd) == -1){//Initialize the pipe to use between the processes
        perror("Error");
    }
    int lg = fork(); // Child created.
    readFile = open(file,O_RDWR); //"readme.txt file used to read"
    
    if(lg == 0){
        close(pipefd[0]); // Close the read section of the pipe
        if(readFile == -1){perror("Error");}

        ret = read(readFile,&c,1);
        while(ret != 0){//read the readme.txt and write it on the pipe
            size++;
            writ = write(pipefd[1],&c,1);
            ret = read(readFile,&c,1);
        }
        close(pipefd[1]);//close the write section of the pipe
    }
    else if (lg > 0){
        int stat;
        waitpid(lg,&stat,0); // parent will wait for the child
        close(pipefd[1]);// close the write section of the pipe

        lseek(readFile,0,SEEK_END);// proceed to the end of the "readme.txt" file to not overwrite it

        writ = write(readFile,"\nParent is writing: ",20);
 
        ret = read(pipefd[0], &c, 1);
        while(ret != 0){ // Write the contents of the pipe on top of the "readme.txt" file
            writ = write(readFile,&c,1);
            ret = read(pipefd[0],&c,1);
        }
        close(pipefd[0]); // Close the read section of the pipe
    }
    else{
        perror("Error");
    }

    return 0;
}