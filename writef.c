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

char *convert(int number) // number stringe donusturuldu.
{
    int count = 0;
    int numbertmp = number;
    while (numbertmp > 0)
    {
        int digit = numbertmp % 10;
        numbertmp /= 10;
        count++;
    }
    char *value = (char *)calloc(count, sizeof(unsigned char));
    numbertmp = number;
    count--;
    while (numbertmp > 0)
    {
        int digit = numbertmp % 10;
        numbertmp /= 10;
        char x = (char)48 + digit;
        *(value + count) = x;
        count--;
    }

    return value;
}
void printValues(FILE *in_file)      // dosya uzerinde islem yapildiginda icerisine yazdirilacak degerler. (pid, ppid, sistem saati gibi)
{
    char *pid = convert(getpid());   // int deger stringe donusturuldu.
    char *ppid = convert(getppid()); // int deger stringe donusturuldu
    time_t a = time(NULL);
    char *time = ctime(&a);
    time[strlen(time) - 1] = '\0';
    fprintf(in_file, "%s", "\n");
    fprintf(in_file, "Pid:%s, Parent Pid:%s,  System Time:%s", pid, ppid, time);
    fprintf(in_file, "%s", "\n");
}
void writetoFile(FILE *in_file,char *buffer){  //argumanlari dosyaya yazar.
    fprintf(in_file, "%s", buffer); //Buffer'in icine yazar.
    fprintf(in_file, "%s", " ");    //Bosluklarini ekler.
    printValues(in_file);          //pid,ppid,sistem saatini yazdirir.
    fclose(in_file);               //Dosyayi kapatir.
}
void writef(char const filename[20], char *buffer)
{
    FILE *in_file;
    if (buffer == NULL) //Kullanici dosya icine birsey yazdırmak istemesse -buffer null ise- bu kod satiri calisir.
    {
        if (in_file != NULL)                  //dosya vardır
            in_file = fopen(filename, "r"); // Okunacak dosyayi bulamazsa dosya yoktur.
        else
            in_file = fopen(filename, "w"); //dosya yoksa bastan olusturur.
    }
    else
    {
        if (in_file == NULL)    //dosya yoksa, daha onceden olusturulmadiysa
        {
            in_file = fopen(filename, "w"); // Bastan dosya olusturur.
            writetoFile(in_file,buffer);
        }
        else
        { // in_file null degilse dosya vardır ve append modunda acilir.
            FILE *in_file = fopen(filename, "a"); //dosya varsa uzerine ekleme yapar.
            writetoFile(in_file,buffer);
        }
    }
}

int main(int argc, char *argv[])
{

    char *message = malloc(sizeof(char) * 200); //kullanicinin gonderecegi mesaji eklemek icin bir mesaj arrayi olusturdum.

    for (int i = 3; i < argc; i++) // 3.komuttan itibaren kullanici yazmaya basladigi icin mesajlar ucuncu komuttan itibaren                                         birlestirilir.
    {
        strcat(message, argv[i]); //satirlari birlestirir.
        strcat(message, " ");     //bosluklarini ekler.
    }
    writef(argv[2], message);    //mesaji writefe gönderir.

    return 0;
}

