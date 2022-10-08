#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(){
    int fr = fork();
    
    if (fr == 0){
        printf("My Id is: %d\n",getpid());
        execl("/usr/bin/date","null","\n",NULL);
    }

    return 0;
}