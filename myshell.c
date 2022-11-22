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
        if (ch == '\n' || ch == EOF) {//Okuduğumuz karakter dosya sonu yada boşluk ise,
            line[index] = '\0';//okurken oluşturduğumuz line arrayinin ilgili indexini null yaptık.
            return line;
        } else {
            line[index] = ch;//Boşluk değilse ilgili index o karaktere eşit olur.
        }
        index++;//İndexi arttırarak bir sonraki line[index]'e yazmaya devam ettik.
        
        if (index >= linesize) {//Boyut aşımı yaşadıysak yani 200'den fazla karakter girdiysek yeni alan açmamız gerekir.
            linesize += 200;//Line boyutumuzu 2 katına çıkarttık.
            char *temp = realloc(line, linesize);
            if (temp==false) {//Bu boyutu da aşarsak depolama hatası verdirdik.
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
    if(argLine[0]==NULL){//Bunu kontrol etmezsek segmentation fault alırız.
        perror("Error");
        return true;
    }
    if (strcmp(argLine[0], arrCommand[0]) == 0)  { //Komut dizisinin 0. elemanıyla argüman satırının 0. elemanını karşılaştırır.                                                Aynı ise 0 döner.
        return shellexit(argLine);
    }
    else if(strcmp(argLine[0], arrCommand[1])==0){
        if(strcmp(argLine[0], arrCommand[1])==0 ){
            int i;
            int f=fork();
            if(f == 0){
                i=execl("/usr/bin/bash", "/usr/bin/bash", "-r", "-t", "-l", (char*) 0);
                perror("exec failed");
            }
            else{
                wait(&i);//Burada wait alt sorgudan ana sorguya geri dönmemizi sağlıyor.
            }
        }
        if(strcmp(argLine[0], arrCommand[0])==0){
            shell();
        }
    }
    else if (strcmp(argLine[0], arrCommand[3]) == 0)  {
        pid_t pid;
        int i;
        int ev;
        pid = fork();
        if (pid == 0) {
            if(argLine[1] == NULL ){
                printf("Missing Parameter.\n");
            }
            ev=execve("writef",argLine,NULL);
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
        printf("Cat: %s \n",argLine[1]);
    }
    else if(strcmp(argLine[0], arrCommand[5]) == 0) {
        system("clear");
    }
    else if (strcmp(argLine[0], arrCommand[6]) == 0) {
        int i;
        int f=fork();
        if(f == 0){
            i=execl("/bin/ls", "/bin/ls", "-r", "-t", "-l", (char*) 0);
            perror("exec failed");
        }
        else{
            wait(&i);//Burada wait alt sorgudan ana sorguya geri dönmemizi sağlıyor.
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

