#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(){
        
    //parent P
    int a=10, b=25, fq=0, fr=0;

    fq = fork(); // fork a child

    if(fq == 0){ // Child successfully forked
        a = a + b;
        printf("First Child(a,b,fq) = (%d,%d,%d)\n",a,b,getpid());
        fr=fork(); // child of the child
        if(fr == 0){
            b = b + 20;
            printf("Second Child(a,b,fr) = (%d,%d,%d)\n",a,b,getpid());
        }
        else if (fr > 0){
            //Now working the with the first child
            a = (a * b) + 30;
            printf("First Child-Parent of Second(a,b,fq) = (%d,%d,%d)\n",a,b,getpid());
        }
    }
    else if(fq > 0){
        //The parent of the process
        b = a + b - 5;
        printf("Main Parent(a,b,parentID) = (%d,%d,%d)\n",a,b,getpid());
    }

    return 0;
}
