#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "sem.h"
#include <time.h>
#define REPEAT  3//Times the processes will be repeated for

int main(){
    int semAgent = semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
    int semSmoker_Paper = semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
    int semSmoker_Tobacco = semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
    int semSmoker_Match = semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
    int semLock = semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
  
    sem_create(semAgent,0);
    sem_create(semSmoker_Match,0);
    sem_create(semSmoker_Paper,0);
    sem_create(semSmoker_Tobacco,0);
    sem_create(semLock,1);
    
    int agent = fork();
    if (agent==0){
        srand(time(NULL));
        for(int i = 0; i < REPEAT; i++){
            P(semLock);
            printf("Agent supplying ");
            int randNum = (rand()%3)+1;
            if(randNum==1){
                printf("Tobacco and Paper on the table.\n");
                V(semSmoker_Match);
            }
            else if(randNum==2){
                printf("Tobacco and Match on the table.\n");
                V(semSmoker_Paper);
            }
            else{
                printf("Paper and Match on the table.\n");
                V(semSmoker_Tobacco);
            }
            V(semLock);
            P(semAgent);
        }
    }
    else{
        int firstSmoker = fork();
        if (firstSmoker == 0){
            int id = getpid() % 20;
            for (int i = 0; i < REPEAT; i++){
                printf("Smoker %d with Tobacco waiting.\n",id);
                P(semSmoker_Tobacco);
                P(semLock);
                printf("Smoker %d rolling a cigarrete.\n",id);
                V(semAgent);
                V(semLock);
            }
        }
        else{
            int secondSmoker = fork();
            if (secondSmoker == 0){
                int id = getpid() % 20;
                for (int i = 0; i < REPEAT; i++){
                    printf("Smoker %d with Match waiting.\n",id);
                    P(semSmoker_Match);
                    P(semLock);
                    printf("Smoker %d rolling a cigarrete.\n",id);
                    V(semAgent);
                    V(semLock);
                }
            }
            else{
                int thirdSmoker = fork();
                if (thirdSmoker == 0){
                    int id = getpid() % 20;
                    for (int i = 0; i < REPEAT; i++){
                        printf("Smoker %d with Paper waiting.\n",id);
                        P(semSmoker_Paper);
                        P(semLock);
                        printf("Smoker %d rolling a cigarrete.\n",id);
                        V(semAgent);
                        V(semLock);
                    }
                }
            }
        }
    }
    return 0;
}