#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(){
    int Qchild = fork();
    // The first child was created.

    if(Qchild == 0){
        printf("I am child one, my PID is: %d\n", getpid());
    }
    else if (Qchild > 0){
        int stat;
        //Wait for the first child to stop before procedding.
        waitpid(Qchild,&stat,0);

        int Rchild = fork();
        // The second child was created.

        if (Rchild == 0){
            printf("I am child two, my PID is: %d\n", getpid());
        }
        else if (Rchild > 0){
            //Wait for the second child to stop before procedding with the parent.
            waitpid(Rchild,&stat,0);
            printf("I am parent, my PID is: %d\n", getpid());
        }
    }
    return 0;
}
