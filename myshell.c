//
//  main.c
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

char *arrCommand[] = {"exit","bash","execx","writef","cat","clear","ls"};
void shell();
char *myread(){
    int linesize = 200;
    char *line = malloc(sizeof(char) * linesize);
    int index = 0;
    
    if (line == false){
        perror("Error : You don't have enough allocation! \n");
        exit(0);
    }
    
    while (true) {
        int ch = getchar();
        if (ch == '\n' || ch == EOF) {//Okudu\u011fumuz karakter dosya sonu yada bo\u015fluk ise,
            line[index] = '\0';//okurken olu\u015fturdu\u011fumuz line arrayinin ilgili indexini null yapt\u0131k.
            return line;
        } else {
            line[index] = ch;//Bo\u015fluk de\u011filse ilgili index o karaktere e\u015fit olur.
        }
        index++;//\u0130ndexi artt\u0131rarak bir sonraki line[index]'e yazmaya devam ettik.
        
        if (index >= linesize) {//Boyut a\u015f\u0131m\u0131 ya\u015fad\u0131ysak yani 200'den fazla karakter girdiysek yeni alan a\u00e7mam\u0131z gerekir.
            linesize += 200;//Line boyutumuzu 2 kat\u0131na \u00e7\u0131kartt\u0131k.
            char *temp = realloc(line, linesize);
            if (temp==false) {//Bu boyutu da a\u015farsak depolama hatas\u0131 verdirdik.
                perror("Error : You don't have enough allocation! \n");
                exit(0);
            }
            temp=line;
        }
    }
}


char **mySplit(char *argLine){
    int linesize = 100;
    int index = 0;
    char **tokens = malloc(linesize * sizeof(char*));
    char *token;
    
    if (!tokens){
        perror("Error");
        exit(0);
    }
    
    token = strtok(argLine, " \t\r\n\a");
    while (token != NULL) {
        tokens[index] = token;
        index++;
        
        if (index >= linesize) {
            linesize += 100;
            tokens = realloc(tokens, 100 * sizeof(char*));
            if (!tokens) {
                perror("Error");
                exit(0);
            }
        }
        
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[index] = NULL;
    return tokens;
}
int shellexit(char **argLine){
    printf("Program ended.\n");
    return 0;
}


int executeCommand(char **argLine){
    if(argLine[0]==NULL){//Bunu kontrol etmezsek segmentation fault al\u0131r\u0131z.
        perror("Error");
        return true;
    }
    if (strcmp(argLine[0], arrCommand[0]) == 0)  { //Komut dizisinin 0. eleman\u0131yla arg\u00fcman sat\u0131r\u0131n\u0131n 0. eleman\u0131n\u0131 kar\u015f\u0131la\u015ft\u0131r\u0131r.                                                Ayn\u0131 ise 0 d\u00f6ner.
        return shellexit(argLine);
    }
    else if(strcmp(argLine[0], arrCommand[1])==0){
        if(strcmp(argLine[0], arrCommand[1])==0 ){
            int i;
            int f=fork();
            if(f == 0){
                i=execve("/bin/bash",argLine,NULL);
                perror("exec failed");
            }
            else{
               i= wait(&i);//Burada wait alt sorgudan ana sorguya geri d\u00f6nmemizi sa\u011fl\u0131yor.
            }
        }
        if(strcmp(argLine[0], arrCommand[0])==0){
            shell();
        }
    }
    else if (strcmp(argLine[0], arrCommand[2]) == 0)  {
        pid_t pid;
        int i;
        pid = fork();
        if (pid == 0) {
            if(argLine[1] == NULL || argLine[2] == NULL|| argLine[3] == NULL|| argLine[4] == NULL){
                printf("Missing Parameter.\n");
            }
            i=execve("execx",argLine,NULL);
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
    else if (strcmp(argLine[0], arrCommand[3]) == 0)  {
        pid_t pid;
        int i;
        pid = fork();
        if (pid == 0) {
            if(argLine[1] == NULL || argLine[2] == NULL){
                printf("Missing Parameter.\n");
            }
            i=execve("writef",argLine,NULL);
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
    else if(strcmp(argLine[0], arrCommand[4]) == 0) {
        char message[200];

          for(int i = 1; i < 10; i++) {
               strcat(message, argLine[i]);
              strcat(message, " ");
          }
        printf("Cat:%s\n",message);
          
        
    }
    else if(strcmp(argLine[0], arrCommand[5]) == 0) {
        system("clear");
    }
    else if (strcmp(argLine[0], arrCommand[6]) == 0) {
        int i;
        int f=fork();
        if(f == 0){
            i=execl("/bin/ls",argLine,NULL);
            perror("exec failed");
        }
        else{
            wait(&i);//Burada wait alt sorgudan ana sorguya geri d\u00f6nmemizi sa\u011fl\u0131yor.
        }
    }
    
    else {
        printf("myshell: Command not found: %s\n",argLine[0]);
    }
    return 1;
}
void shell(){
    
    char *command;
    char **argLine;
    int state;
    do{
        printf("myShell-->> ");
        command = myread();
        argLine = mySplit(command);
        state = executeCommand(argLine);
        
    }while(state);
}

int main(int argc, const char * argv[]) {
    shell();
    return 0;
}

