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

int main(int argc, const char *argv[])
{
    int count = atoi(argv[2]); // kac kez calistirilacagi
    char *program = argv[3];   // girilen programin adi
    char *newArgv[3];
    newArgv[0] = program; // writef
    newArgv[1] = argv[4]; //-f
    newArgv[2] = argv[5]; // myfile

    for (int i = 0; i < count; i++)
    { // girilen artarda programin calismasi icin for dongusu olusturuldu.
        pid_t pid;
        int k;
        pid = fork();
        if (pid == 0)
        { // child process calisti.
            if (newArgv[0] == NULL || newArgv[1] == NULL || newArgv[2] == NULL)
            { // parametre eksikse hata mesaji verdirdi.
                printf("Missing Parameter.\n");
            }
            k = execve(program, newArgv, NULL); // execve parametre olarak girilen programa dallandi.
            printf("Exec oldu.\n");
            perror("exec failed");
        }
        else
        {
            wait(&k); // dallandigi programdan buraya donmesini bekledim.
        }
    }

    return 0;
}



