#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "myshell.h"

void initialize(void){

    system("clear");
    //system("pwd");

    // prompt user with welcome msg
    printf("\n****************************************************");
    printf("\n      This is a Shell/Command Line Interpreter");
    printf("\n                  Written in C");
    printf("\n****************************************************\n");

}

void shellPrompt(void){ 
    printf("~/myShell$ ");
}

int main (int argc, char *argv[]){

    // call function
    initialize();   
    
    while(1){
        shellPrompt();
        getline(&input, &len, stdin); // Read the user input
        printf(input);

    }
}