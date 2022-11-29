//
//  myshell.c
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

char *arrCommand[] = {"exit", "bash", "execx", "writef", "cat", "clear", "ls"};
void shell();
char *myread()
{ // Terminalden komutu alip okumamizi sagliyor.
    int linesize = 200;
    char *line = malloc(sizeof(char) * linesize);
    int index = 0;

    if (line == false)
    {
        perror("Error : You don't have enough allocation! \n");
        exit(0);
    }

    while (true)
    {
        int ch = getchar();
        if (ch == '\n' || ch == EOF)
        {                       // okudugumuz karakter dosya sonu yada bosluk ise
            line[index] = '\0'; // okurken olusturdugumuz line arrayinin ilgili indexini null yaptim.
            return line;
        }
        else
        {
            line[index] = ch; // Bosluk degilse ilgili index o karaktere esit olur.
        }
        index++; // Indexi arttirarak bir sonraki line[index]'e yazmaya devam ettim.

        if (index >= linesize)
        {                    // Boyut asimina ugradiysak yani 200'den fazla karakter girdiysek yeni alan acmamiz gerekir.
            linesize += 200; // Line boyutumuzu 2 katina cikarttik.
            char *temp = realloc(line, linesize);
            if (temp == false)
            { // Bu boyutu da asarsak depolama hatasi verdirdik.
                perror("Error : You don't have enough allocation! \n");
                exit(0);
            }
            temp = line;
        }
    }
}

char **mySplit(char *argLine)
{ // Okudugumuz girdileri arguman dizisine donusturdum.
    int linesize = 100;
    int index = 0;
    char **tokens = malloc(linesize * sizeof(char *)); // klavyeden okudugumuz argumanların arraya atanmis haline tokens dedim.
    char *token;

    if (!tokens)
    {
        perror("Error");
        exit(0);
    }

    token = strtok(argLine, " \t\r\n\a"); // Burada girilen karakterlere gore argLine'a parcalara ayirdim.
    while (token != NULL)
    {
        tokens[index] = token;
        index++;

        if (index >= linesize)
        { // boyut asiminda linesize'i arttirdim.
            linesize += 100;
            tokens = realloc(tokens, 100 * sizeof(char *));
            if (!tokens)
            {
                perror("Error");
                exit(0);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[index] = NULL;
    return tokens;
}
int executeCommand(char **argLine)
{ // komutlari calistiran method.

    if (argLine[0] == NULL)
    { // ArgLine[0] NULL olup olmadigini kontrol etmezsek segmentation fault aliriz.
        perror("Error");
        return true;
    }
    if (strcmp(argLine[0], arrCommand[0]) == 0)// Komut dizisinin 0. elemaniya argLine'in 0. elemanini karsilastirdim. Ayni ise 0 doner.
    {
        printf("Program ended.\n");
        return 0; //Cikis yapar
    }
    else if (strcmp(argLine[0], arrCommand[1]) == 0)
    { // Bu kod satirlarinda bash komutuna gecis yaptim.
        if (strcmp(argLine[0], arrCommand[1]) == 0)
        {
            int i;
            int f = fork();
            if (f == 0)
            {                                           // child process calisti
                i = execve("/bin/bash", argLine, NULL); // bash programina execve ile dallanma yaptik.
                perror("exec failed");
            }
            else
            {
                wait(&i); // Burada wait alt sorgudan ana sorguya geri donmemizi sagliyor.
            }
        }
        if (strcmp(argLine[0], arrCommand[0]) == 0)
        {            // bash'de exit dedigimizde
            shell(); // myshell calismaya devam ediyor.
        }
    }
    else if (strcmp(argLine[0], arrCommand[2]) == 0)
    { // execx kodunu calistiran kodlar
        pid_t pid;
        int i;
        pid = fork();
        if (pid == 0)
        { // child process calisti
            if (argLine[1] == NULL || argLine[2] == NULL || argLine[3] == NULL || argLine[4] == NULL)
            { // parametre eksikse hata mesaji verdirdim.
                printf("Missing Parameter.\n");
            }
            i = execve("execx", argLine, NULL); // execx programina execve ile dallanma yaptim.
            perror("exec failed");
        }
        else
        {
            wait(&i); // Burada wait alt sorgudan ana sorguya geri donmemizi sagliyor.
        }
    }
    else if (strcmp(argLine[0], arrCommand[3]) == 0)
    { // writefi calistiran kod satirlari.
        pid_t pid;
        int i;
        pid = fork();
        if (pid == 0)
        {
            if (argLine[1] == NULL || argLine[2] == NULL)
            { // burada da eksik parametre kontrolu yaptim.
                printf("Missing Parameter.\n");
            }
            i = execve("writef", argLine, NULL); // execve ile writef programina dallanma yaptim
            perror("exec failed");
        }
        else
        {
            wait(&i);
        }
    }
    else if (strcmp(argLine[0], arrCommand[4]) == 0)
    { // cat komutu.
        int size = 200;
        char *echo = malloc(sizeof(char) * size);   //argline dan aldigim verileri eklemek icin bir echo arrayi olusturdum.

        while (*(++argLine) != NULL)    //argline null olana kadar butun degerleri aldim.
        {
            strcat(echo, *argLine);    //strcat ile arguman satirindaki cumleleri birlestirdim.
            strcat(echo, " ");         //kelimeler arasında bosluk biraktim.
        }
        printf("Cat: %s\n", echo);     //en son ekrana yazdirdim.
    }
    else if (strcmp(argLine[0], arrCommand[5]) == 0)
    { // Clear komutu
        system("clear");
    }
    else if (strcmp(argLine[0], arrCommand[6]) == 0)
    { // ls komutu
        int i;
        int f = fork();
        if (f == 0)
        {                                         // child process olustu.
            i = execve("/bin/ls", argLine, NULL); // ls programina dallanma yaptim.
            perror("exec failed");
        }
        else
        {
            wait(&i); // Burada wait alt sorgudan ana sorguya geri donmemizi sagliyor.
        }
    }
    else
    {
        printf("myshell: Command not found: %s\n", argLine[0]); // komut bulunamama hatasi
    }
    return 1;
}
void shell()
{ // shell komutu mainde cagrilan ana kod parcasi
    char *command;
    char **argLine;
    int state;
    do
    {
        printf("myShell-->> ");
        command = myread();              // komutu okudu
        argLine = mySplit(command);      // token haline getirdi
        state = executeCommand(argLine); // komutlari calistirdi

    } while (state); // 0 dönene kadar calisti.
}

int main(int argc, const char *argv[])
{
    shell();
    return 0;
}

