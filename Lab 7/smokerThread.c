#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>
#define People 4
#define REPEAT 9
sem_t semAgent,semSmoker_Tobacco,semSmoker_Paper,semSmoker_Matches;
int takes = REPEAT;
int table = 0;
pthread_mutex_t buffer_mutex;
void* Agent(void* args){
    for(int i = 0; i < REPEAT; i++){
        pthread_mutex_lock(&buffer_mutex); /* protecting critical section */
        printf("Agent supplying ");
        table = (rand()%3)+1;
        if(table == 0){
            printf("with Tobacco and Paper\n");
            sem_post(&semSmoker_Matches);
        }
        else if (table == 1){
            printf("with Matches and Paper\n");
            sem_post(&semSmoker_Tobacco);
        }
        else{
            printf("with Tobacco and Macthes\n");
            sem_post(&semSmoker_Paper);
        }
        pthread_mutex_unlock(&buffer_mutex);
        sem_wait(&semAgent);
        takes--;
    }
    sem_post(&semSmoker_Matches);//At the end the agent call everyone
    sem_post(&semSmoker_Tobacco);
    sem_post(&semSmoker_Paper);
    printf("Agent is done.\n");
    free(args);
}

void* SmokerMatches(void* args) {
    while(takes > 0){
        printf("Smoker with Matches waiting\n");
        sem_wait(&semSmoker_Matches);
        if(takes == 0){break;}//If the agent is done supplying it will break the loop
        pthread_mutex_lock(&buffer_mutex); /* protecting critical section */
        
        printf("Smoker with Matches rolling\n");
        
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&semAgent);
    }
    free(args);
}
void* SmokerTobacco(void* args) {
    while(takes > 0){
        printf("Smoker with Tobacco waiting\n");
        sem_wait(&semSmoker_Tobacco);
        if(takes == 0){break;}
        pthread_mutex_lock(&buffer_mutex); /* protecting critical section */
        
        printf("Smoker with Tobacco rolling\n");
        
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&semAgent);
    }
    free(args);
}
void* SmokerPaper(void* args) {
    while(takes > 0){
        printf("Smoker with Paper waiting\n");
        sem_wait(&semSmoker_Paper);
        if(takes == 0){break;}
        pthread_mutex_lock(&buffer_mutex); /* protecting critical section */
        
        printf("Smoker with Paper rolling\n");
        
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&semAgent);
    }
    free(args);
}
int main(int argc, char *argv[]) {
    pthread_t th[People];
    sem_init(&semAgent, 0, 0);
    sem_init(&semSmoker_Matches, 0, 0);
    sem_init(&semSmoker_Tobacco, 0, 0);
    sem_init(&semSmoker_Paper, 0, 0);//One thread per person in the table
    pthread_mutex_init(&buffer_mutex, NULL);
    int i;
    for(i=0;i < People;i++){
        int* a = malloc(sizeof(int));
        *a = i;
        if(i == 0 && pthread_create(&th[i], NULL, &Agent,a) != 0) {
            perror("Failed to create thread");
        }
        if(i == 1 && pthread_create(&th[i], NULL, &SmokerMatches, a) != 0) {
            perror("Failed to create thread");
        }
        if(i == 2 && pthread_create(&th[i], NULL, &SmokerPaper, a) != 0) {
            perror("Failed to create thread");
        }
        if(i == 3 && pthread_create(&th[i], NULL, &SmokerTobacco, a) != 0) {
            perror("Failed to create thread");
        }
    }
    for (i = 0; i < People; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semAgent);
    sem_destroy(&semSmoker_Matches);
    sem_destroy(&semSmoker_Paper);
    sem_destroy(&semSmoker_Tobacco);
    return 0;
}