#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]){

    if(argc < 2){
        printf("--------------------------------------\n");
        printf("USAGE: ./virtMemManager.o <filename>\n");
        printf("--------------------------------------\n");
        exit(0);
    }

    FILE *f = fopen(argv[1], "r");



    
}