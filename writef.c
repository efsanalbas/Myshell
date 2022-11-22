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
    FILE *in_file;
    if(buffer == NULL){// buffer parametresi girilmediyse
        in_file  = fopen(filename, "r");//Okunacak dosyayı bulamazsa dosya yoktur.
    }
    else{
        
        if (in_file == NULL){
            in_file = fopen(filename, "w");//Baştan dosya oluştururum.
            gets(buffer);
            fprintf(in_file, "%s",buffer);
        }
        
        
        else{//in_file null değilse dosya vardır ve append modunda açılır.
            FILE *in_file = fopen(filename, "a");
            if (in_file == NULL)// Ekleme yapılmak üzere açılan in_file doğru oluşturuldumu kontrol ediyorum.
            {
                printf("\nUnable to open file.\n");
                exit(0);
            }
            else{
                printf("Dosya yazılmayı bekliyor.");
                gets(buffer);
                fprintf(in_file, "%s",buffer);
            }
        }
        
    }
    }

int main(int argc, char *argv[]){
    char *kullaniciMesaji = malloc(100 * sizeof(char*));
    int j=0;
    for (int i = 2; i < argc; i++){
        kullaniciMesaji[j] = *argv[i];
        j++;
    }
    writef(argv[1],kullaniciMesaji);
    return 0;
}

