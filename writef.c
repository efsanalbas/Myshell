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
            printf("Dosyaya yazıldı.\n");
            fclose(in_file);
        }
        
        else {//in_file null değilse dosya vardır ve append modunda açılır.
            FILE *in_file = fopen(filename, "a");
            fprintf(in_file, "%s", buffer);
            printf("Dosyaya yazıldı.\n");
            fclose(in_file);
        }
    }
}
void writef2(char const filename[20]){
    FILE *in_file ;
    if(in_file != NULL){
    in_file = fopen(filename, "r");//Baştan dosya oluştururum.
    }
    else{
    in_file = fopen(filename, "r");
    }
    
}

int main(int argc, char *argv[]){
    if(argc <2){
        writef2(argv[1]);
    }
    else{
        char *message = malloc(sizeof(char) * 200);
        
        int i = 2;
        int j = 0;
        char *ch;
        while(i < argc){
            while(*(argv + i) != '\0'){
                ch = *(argv+i);
                for(int j=0; j<sizeof(ch)/sizeof(ch[0]); j++){
                    message[j] = ch[j];
                }
                i++;
            }
        }
        writef(argv[1], message);
    }
    return 0;
}


