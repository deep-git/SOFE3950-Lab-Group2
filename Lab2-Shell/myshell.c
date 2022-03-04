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

void changeDir(void) {
}

void dir(void) {
}

void environ(void) {
	char **environment;
	for (int i = 0; environment[i] != NULL; i++) {
		printf("Environment: %s \n", environment[i]);
	}
}

void echo(int argc, char **argv) {
	if (argv[1] != NULL) {
		for (int i = 0; i < argc; i++) {
			printf("%s \n", argv[i]);
		}
	} else {
		printf("Invalid echo format \n");
	}
}

void help(void) {
}

void pause(void) {
}

int quit(char **argv) {
	return 0;
}

void clearScreen(void) {
	system("clear");
}

int main (int argc, char *argv[]){ 
    initialize();   
    
    while(1){

        shellPrompt();
        printDir();

        getline(&input, &len, stdin); // Read the user input



    }
}
