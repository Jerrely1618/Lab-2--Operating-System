#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
int main(int argc, char* argv[]){
    int df = creat("destination.txt",S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    int df2 =creat("destination2.txt",S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(df == -1 || df2 == -1){
        perror("Error");
        return 1;
    }
    return 0;
}