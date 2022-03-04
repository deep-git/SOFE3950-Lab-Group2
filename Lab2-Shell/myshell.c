#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include "myshell.h"

#define STRING_NUM = 8
#define TOTAL_STRING_SIZE = 500

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

  char options[STRING_NUM][TOTAL_STRING_SIZE] = {"cd <directory>   : change directories",
                          "clr              : clear the screen",
                          "dir <directory>  : list the contents of the directory",
                          "environ          : list all the environment strings",
                          "echo <comment>   : display <comment>",
                          "help             : display the user manual",
                          "pause            : pause operation of the shell",
                          "quit             : quit the shell"};

  printf("||============ C SHELL HELP GUIDE ============||")
  printf("The following are available in-built commands that can be utilized: ");

  for (int i = 0; i < STRING_NUM; i++) {
    options[i] = malloc(TOTAL_STRING_SIZE * sizeof(char));
    printf("%s \n", options[i]);
  }
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
