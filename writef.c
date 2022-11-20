#include <stdio.h>

void writef(char const filename[20]){
    FILE *filep = fopen(filename, "w");
    if(filep == NULL){
        printf("File couldn't be created");
    }
    else{
        printf("File created.");
        
    }
}
int main(int argc, char const *argv[]){
    writef(argv[1]);
    return 0;
}

