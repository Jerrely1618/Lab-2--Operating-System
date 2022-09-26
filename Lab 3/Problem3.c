#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Missing parameters\n");
        return 0;
    }

    int seriesNum = atoi(argv[1]);
    int total = 0;

    int Qchild = fork();
    if(Qchild == 0){
        for(int i = 0; i <= seriesNum; i+=2){
            total += i;
        }
        printf("Total(Even Child): %d\n",total);
    }
    else if (Qchild > 0){
        int stat;
        waitpid(Qchild,&stat,0);
        int Rchild = fork();

        if (Rchild == 0){
            for(int i = 1; i <= seriesNum; i+=2){
                total += i;
            }
            printf("Total(Odd Child): %d\n",total);
        }
        else if (Rchild > 0){
            waitpid(Rchild,&stat,0);
            for(int i = 0; i <= seriesNum; i++){
                total += i;
            }
            printf("Total(Parent): %d\n",total);
        }
    }
    return 0;
}