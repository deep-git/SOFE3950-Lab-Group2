#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
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

void printDir(void){
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("\n %s \n", cwd);
}

int main (int argc, char *argv[]){

    initialize();   
    
    while(1){

        shellPrompt();
        printDir();

        getline(&input, &len, stdin); // Read the user input
        
        //printf(input);





    }
}