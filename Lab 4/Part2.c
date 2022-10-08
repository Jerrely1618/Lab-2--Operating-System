#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    int fr = fork();
    
    if (fr == 0){
        printf("My Id is: %d\n",getpid());
        execvp("ls",&argv[0]);
    }

    return 0;
}