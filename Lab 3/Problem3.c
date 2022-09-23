#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Missing parameters\n");
        return 0;
    }

    int seriesNum = atoi(argv[1]);
    int totalEven = 0, totalOdd = 0, total = 0;

    int Qchild = fork();
    if(Qchild == 0){
        for(int i = 0; i <= seriesNum; i+=2){
            totalEven += i;
        }
        printf("Total(Even Child): %d\n",totalEven);
        exit(totalEven);
    }
    else if (Qchild > 0){
        int stat;
        waitpid(Qchild,&stat,0);
        int Rchild = fork();
        if (Rchild == 0){
            for(int i = 1; i <= seriesNum; i+=2){
                totalOdd += i;
            }
            printf("Total(Odd Child): %d\n",totalOdd);
            exit(totalOdd);
        }
        else if (Rchild > 0){
            waitpid(Rchild,&stat,0);
            total = totalEven + totalOdd;
            printf("Total(Parent): %d,%d,%d\n",totalEven,totalOdd,total);
        }
    }
    return 0;
}