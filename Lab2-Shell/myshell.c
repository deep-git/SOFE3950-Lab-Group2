#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include "myshell.h"

#define STRING_NUM 8
#define TOTAL_STRING_SIZE 500
#define LIGHTBLUE "\033[1m\033[34m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[1m\033[33m"
#define NORMALCOLOUR "\033[0m"

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
  printf(YELLOW "~/myShell$ " NORMALCOLOUR);
}

void printDir(void){
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("%s ", cwd);
}

int changeDir(char* dir) {
    char path[125];

    if (dir != NULL){
        getcwd(path, sizeof(path));

        strncat(path, "/", 1);
		strncat(path, dir, strlen(dir));		
		if (chdir(path) < 0)		
			printf("ERROR: File / Directory could not be found %s\n", dir);			
		return;	
    }
}

void dir(void) {
}

void environ(void) {
  /*
	char environment[STRING_NUM];
	for (int i = 0; environment[i] != NULL; i++) {
		printf("Environment: %s \n", environment[i]);
	}
  */
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

  printf("||============ C SHELL HELP GUIDE ============|| \n\n");
  printf("The following are available in-built commands that can be utilized: \n\n");

  for (int i = 0; i < STRING_NUM; i++) {
    //options[i] = malloc(TOTAL_STRING_SIZE * sizeof(char));
    printf("%s \n\n", options[i]);
  }
}

void pauses(void) {
    printf("Operation currrently PAUSED. Press ENTER key to Continue\n");
    getchar();
}

int quit(char **argv) {
	return 0;
}

void clearScreen(void) {
	system("clear");
}

void fileIO(void){
    
}

int main (int argc, char *argv[]){

  char user_command[TOTAL_STRING_SIZE];

    initialize();   ///welcome screen

    while(1){

        shellPrompt();
        //printDir();

        //getline(&input, &len, stdin); // Read the user input
        fgets(user_command, TOTAL_STRING_SIZE, stdin);
        user_command[strlen(user_command) - 1] = '\0';

        if (strcmp(user_command, "clr") == 0) {
          clearScreen();
        } else if (strcmp(user_command, "help") == 0) {
          help();
        } else if (strcmp(user_command, "pauses") == 0) {
          pauses();
        } else if (strcmp(user_command, "quit") == 0) {
          quit(argv);
          break;
        } else if (strcmp(user_command, "echo") == 0) {
          echo(argc, argv);
        } else if (strcmp(user_command, "cd") == 0) {
          changeDir(argv);
        }

    

    }
}
