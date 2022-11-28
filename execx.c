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
    int count=atoi(argv[2]);
    char * program = argv[3];
    char *newArgv[4];
    newArgv[0]=program;//writef
    newArgv[1]=argv[4];//-f
    newArgv[2]=argv[5];//myfile
    newArgv[3]=argv[6];//yazdirilacak mesaj

    for (int i=0; i<count; i++) {
        
        pid_t pid;
        int k;
        int ev;
        pid = fork();
        if (pid == 0) {
            if(newArgv[0]== NULL || newArgv[1] == NULL || newArgv[2] ==NULL){
                printf("Missing Parameter.\n");
            }
            k=execve(program,newArgv,NULL);
            printf("Exec oldu.\n");

            return 0;
        }
        else if (pid < 0) {
            perror("error");
        }
        else {
        wait(&k);
        }
    }
    
    return 0 ;
}


