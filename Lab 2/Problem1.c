#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main (int argc, char* argv[])
{
    char* filepath = argv[1];
    int returnval;
    // Check file existence
    returnval = access (filepath, F_OK);
    
    if(returnval == 0){
        printf ("%s exists\n", filepath);
    }else{
        if(errno == ENOENT){
            printf ("%s does not exist\n", filepath);
        }
        else if(errno == EACCES){
            printf ("%s is not accessible\n", filepath);
        }
    }
    //We try to access the file with read permission
    returnval = access(filepath, R_OK);
    if(returnval != 0){
            printf ("%s cannot be read\n", filepath);
    }
    
    //We try to access the file with write permission
    returnval = access(filepath, W_OK);
    if(errno != 0){
        printf ("%s cannot write\n", filepath);
    }
    return 0;
}