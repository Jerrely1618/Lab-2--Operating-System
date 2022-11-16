#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    char* sourceFile = "quiz_grades.txt";
    int sf = open(sourceFile,O_RDONLY);
    int ret = 1;

    if(sf == -1){
        perror("Error");
    }
    else{
        int row = 1,column = 1;
        int n = 0,t = 0, p = 0;
        char input[256];
        char c;    
        while(ret != 0){
            ret = read(sf, &c, 1);
            if(c!= '\n'){
                input[t] = c;
                if(c== ' '){
                    column++;
                }
            }
            else{
                input[t] = ' ';
                row++;
                column = 1;
            }
            t++;
        }
        close(sf);
        input[t-1] = ' ';
        char* num = strtok(input," ");
        int grades[column][row];
        while(num != NULL){
            if(p>column-1){
                p=0;
                n++;
            }
            grades[p][n] = atoi(num);
            p++;
            num = strtok(NULL," ");
        }
        int stat; 
        double totalAvg = 0; 
        int ManagersMade = column%2 == 1? column-2:column;
        for(int i = 0; i < ManagersMade; i+=2){
            p = i;
            int manager = fork();
            if(manager == 0){
                int workersMade = ((i==0) && (column % 2 == 1))? 3 : 2;
                for(int j = 0; j < workersMade; j++){
                    p = i + j;
                    p += ((i!=0) && (column % 2 == 1))? 1 : 0;
                    int worker = fork();
                    if(worker == 0){
                        double total = 0;
                        for(int h = 0; h<row; h++){
                            total += (double)(grades[p][h]);
                        } 
                        totalAvg += total/row;
                        printf("total[%d] = %f \n",p,totalAvg);
                        break;
                    }
                    else{
                        waitpid(worker,&stat,0);
                    }
                }
                break;
            }
            else{
                waitpid(manager,&stat,0);
            }
        }
    }
    return 0;
}