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

void reverse(char s[])
{
    int i, j;
    char c;
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
char * itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
    reverse(s);
    return s;
 }
void printValues(FILE* in_file){
    char pid[10];
    char ppid[10];
    time_t a = time(NULL);
    char * time = ctime(&a);
    time[strlen(time)-1] = '\0';
    fprintf(in_file, "%s", "\n");
    fprintf(in_file, "Pid:%s, Parent Pid:%s,  System Time:%s", itoa (getpid(),pid),itoa (getppid(),ppid), time);
    fprintf(in_file, "%s", "\n");

}

void writef(char const filename[20],char *buffer){
    FILE *in_file ;
    if(buffer == NULL){
        if(in_file != NULL)
        in_file = fopen(filename, "r");//Okunacak dosyayı bulamazsa dosya yoktur.
    }
    else{
        if (in_file == NULL){
            in_file = fopen(filename, "w");//Baştan dosya oluştururum.
            fprintf(in_file, "%s", buffer);
            fprintf(in_file, "%s", " ");
            printValues(in_file);
            fclose(in_file);
        }
        
        else {//in_file null değilse dosya vardır ve append modunda açılır.
            FILE *in_file = fopen(filename, "a");
            fprintf(in_file, "%s", buffer);
            fprintf(in_file, "%s", " ");
            printValues(in_file);
            fclose(in_file);
        }
    }
}
void writef2(char const filename[20]){
    FILE *in_file ;
    if(in_file != NULL){
    in_file = fopen(filename, "r");//Baştan dosya oluştururum.
        fprintf(in_file, "%s", " ");
        printValues(in_file);

    }
    else{
    in_file = fopen(filename, "r");
        fprintf(in_file, "%s", " ");
        printValues(in_file);
    }
    
}

int main(int argc, char *argv[]){
    if(argc <3){
        writef2(argv[2]);
    }
    else{
        char *message = malloc(sizeof(char) * 200);
        
        int i = 3;
        int j = 0;
        char *ch;
        while(i < argc){
            while(*(argv + i) != '\0'){
                ch = *(argv+i);
                for(int j=0; j<strlen(ch); j++){
                    message[j] = ch[j];
                }
                i++;
            }
        }
        writef(argv[2], message);
    }
    return 0;
}


 
