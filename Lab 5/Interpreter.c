#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){

    while(1){
        int fd[2];
        pipe(fd);
        char commandInput[256];
        fgets(commandInput,sizeof(commandInput),stdin);
        if(strcmp(commandInput,"exit")==10){
            break;
        }

        commandInput[strcspn(commandInput,"\n")] = 0;

        char* cmd = strtok(commandInput," ");
        char* argCmd [256];
        char* arg = "";                
        int i = 0,secondPart = 0;
        argCmd[i++]=cmd;

        while (arg != NULL){
            arg = strtok(NULL, " ");
            if (arg != NULL && strchr(arg,'|') != NULL){
                secondPart = 1;
                break;
            }
            argCmd[i] = arg;
            i++;
        }
        argCmd[i] = NULL;

        int interp = fork();
        if (interp == 0){
            if(secondPart == 1){
                close(fd[0]);
                dup2(fd[1],STDOUT_FILENO);
                close(fd[1]);
            }
            // char* tmpArg[4] = {"ps","-u","jerrely",NULL};
            // char* tmp = "ps";
            execvp(cmd,argCmd);
        }
        else{
            int stat;
            waitpid(interp,&stat,0);
            if(secondPart == 1){
                char* secondArg[256];
                int j = 0;
                cmd = strtok(NULL, " ");
                secondArg[j++] = cmd;
                while (arg != NULL){
                    arg = strtok(NULL, " ");
                    secondArg[j] = arg;
                    j++;
                }

                int second = fork();
                if(second == 0){
                    close(fd[1]);
                    dup2(fd[0],STDIN_FILENO);
                    close(fd[0]);
                    fd[0] = execvp(cmd,secondArg);
                }
            }
        }
    }
    return 0;
}