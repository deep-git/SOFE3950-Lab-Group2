#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include "myshell.h"

#define STRING_NUM 8
#define TOTAL_STRING_SIZE 500

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

int changeDir(char* path[]) {
    if (path[1] == NULL){
        chdir(getenv("HOME"));
        return 1;
    }else{
		if (chdir(path[1]) == -1) {
			printf(" %s: Directory NOT FOUND!\n", path[1]);
            return -1;
		}
	}
	return 0;
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

  printf("||============ C SHELL HELP GUIDE ============||");
  printf("The following are available in-built commands that can be utilized: ");

  for (int i = 0; i < STRING_NUM; i++) {
    //options[i] = malloc(TOTAL_STRING_SIZE * sizeof(char));
    printf("%s \n", options[i]);
  }
}

void pause(void) {
    printf("Operation currrently PAUSED. Press ENTER key to Continue\n");
    getchar();
}

int quit(char **argv) {
	return 0;
}

void clearScreen(void) {
	system("clear");
}

int main (int argc, char *argv[]){

  char user_command[TOTAL_STRING_SIZE];

    initialize();   ///welcome screen

    while(1){

        shellPrompt();
        printDir();

        //getline(&input, &len, stdin); // Read the user input
        fgets(user_command, TOTAL_STRING_SIZE, stdin);
        user_command[strlen(user_command) - 1] = '\0';

        if (strcmp(user_command, "clr") == 0) {
          printf("Hello world");
        }



    }
}
