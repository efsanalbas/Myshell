//
//  execv.c
//  MyShell
//
//  Created by Nur Efsan Albas on 19.11.2022.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, const char * argv[]){
    int count=argv[2];
    char * program = argv[3];
    char *newArgv[3];
    newArgv[0]=argv[3];
    newArgv[1]=argv[4];
    newArgv[2]=argv[5];

    for (int i=0; i<count; i++) {
        
        pid_t pid;
        int i;
        int ev;
        pid = fork();
        if (pid == 0) {
            if(newArgv[0]== NULL || newArgv[1] == NULL || newArgv[2] ==NULL){
                printf("Missing Parameter.\n");
            }
            ev=execve(program,newArgv,NULL);
            printf("Exec oldu.");
            return 0;
        }
        else if (pid < 0) {
            perror("error");
        }
        else {
            i = wait(&i);
        }
        return 1;
    }
    
    return 0 ;
}

