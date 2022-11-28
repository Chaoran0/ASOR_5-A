#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]){
    //int nice(int inc);
    
    if (argc != 2){
        printf("Argument failed\n");
        exit(1);
    }
    int sol = nice(argv[1]);
    printf("El valor de nice es: %d\n", sol);

    return 0;
}
