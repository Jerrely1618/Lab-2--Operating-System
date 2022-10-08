#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char* argv[]){
    int fr = fork();
    
    if (fr == 0){
        printf("My Id is: %d\n",getpid());
        execvp("result.exe",&argv[0]);
    }
    // else if (fr > 0){
    //     int dp = fork();
    //     if(dp == 0){

    //     }
    //     else if(dp > 0){

    //     }
    //     else{
    //         perror("Error");
    //     }
    // }
    // else{
    //     perror("Error");
    // }

    return 0;
}