#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(){
    int Qchild = fork();
    
    if(Qchild == 0){
        printf("I am child one, my PID is: %d\n", getpid());
    }
    else if (Qchild > 0){
        int stat;
        waitpid(Qchild,&stat,0);

        int Rchild = fork();
        if (Rchild == 0){
            printf("I am child two, my PID is: %d\n", getpid());
        }
        else if (Rchild > 0){
            waitpid(Rchild,&stat,0);
            printf("I am parent, my PID is: %d\n", getpid());
        }
    }
    return 0;
}
