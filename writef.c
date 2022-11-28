//
//  writef.c
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
#include <sys/stat.h>
#include <time.h>

char *convert(int number)
{
    int count=0;
    int numbertmp=number;
    while(numbertmp>0)
    {
        int digit= numbertmp%10;
        numbertmp/=10;
        count++;
    }
    char * value= (char * ) calloc (count,sizeof(unsigned char)  );
    numbertmp=number;
    count--;
    while(numbertmp>0)
    {
        int digit= numbertmp%10;
        numbertmp/=10;
        char x=(char) 48+digit;
        *(value+count)=x;
        count--;
    }

    return value;
}
void printValues(FILE* in_file){
    char *pid = convert(getpid());
    char *ppid = convert(getppid());
    time_t a = time(NULL);
    char * time = ctime(&a);
    time[strlen(time)-1] = '\0';
    fprintf(in_file, "%s", "\n");
    fprintf(in_file, "Pid:%s, Parent Pid:%s,  System Time:%s", pid,ppid, time);
    fprintf(in_file, "%s", "\n");

}

void writef(char const filename[20],char *buffer){
    FILE *in_file ;
    if(buffer == NULL){
        if(in_file != NULL)
        in_file = fopen(filename, "r");//Okunacak dosyay\u0131 bulamazsa dosya yoktur.
    }
    else{
        if (in_file == NULL){
            in_file = fopen(filename, "w");//Ba\u015ftan dosya olu\u015ftururum.
            fprintf(in_file, "%s", buffer);
            fprintf(in_file, "%s", " ");
            printValues(in_file);
            fclose(in_file);
        }
        
        else {//in_file null de\u011filse dosya vard\u0131r ve append modunda a\u00e7\u0131l\u0131r.
            FILE *in_file = fopen(filename, "a");
            fprintf(in_file, "%s", buffer);
            fprintf(in_file, "%s", " ");
            printValues(in_file);
            fclose(in_file);
        }
    }
}


int main(int argc, char *argv[]){

        char * message =malloc(sizeof(char) * 200);

          for(int i = 3; i < argc; i++) {
              strcat(message, argv[i]);
              strcat(message, " ");
          }

          printf("%s\n", message);
          writef(argv[2], message);
    
    return 0;
}





 
