#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char* argv[]){
    int fr = fork();
    
    if (fr == 0){
        execv("Prcs1.exe",("\n",NULL));
    }
    else if (fr > 0){
        int stat;
        waitpid(fr,&stat,0);
        int dp = fork();
        if(dp == 0){
            execv("Prcs2.exe",("\n",NULL));
        }
        else if(dp < 0){
            perror("Error");
        }
    }
    else{
        perror("Error");
    }

    return 0;
}