#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include "myshell.h"

#define STRING_NUM 8
#define TOTAL_STRING_SIZE 500
#define MAX_SIZE 1024

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

void changeDir(char* dir) {

    char path[125];

    if (dir != NULL){
      chdir(dir);
      putenv(dir);
      getcwd(path, sizeof(path));

      // strncat(path, "/", 1);
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

void fileIO(char *path){
  int commands[MAX_SIZE];
  int i = 0;
  
  FILE *file;

  if ( (file = fopen(path, "r")) ){
      while (fscanf(file, "%d", &commands[i]) != EOF){
          i++;
      }
      fclose(file);

      commands[i] = '\0';

      for (i=0; commands[i] != '\0'; i++){
         //pass to choices
      }

  }
}

void choices(int argc, char **argv) {
  if (strcmp(argv[0], "clr") == 0) {
    clearScreen();
  } else if (strcmp(argv[0], "help") == 0) {
    help();
  } else if (strcmp(argv[0], "pauses") == 0) {
    pauses();
  } else if (strcmp(argv[0], "quit") == 0) {
    quit(argv);
    exit(0);
  } else if (strcmp(argv[0], "echo") == 0) {
    echo(argc, argv);
  } else if (strcmp(argv[0], "cd") == 0) {
    // changeDir(argv);
    printDir();
  } else if (strcmp(argv[0], "myshell") == 0) {
    // fileIO(args);
  }
}

int main () {
  // int argc, char *argv[]
  char **argv = malloc(sizeof(char) * TOTAL_STRING_SIZE);
  char *token;
  char spaces[] = " \n\t";
  int argc = 0;

  char user_command[TOTAL_STRING_SIZE];

    initialize();   ///welcome screen

    while(1){

        shellPrompt();
        //printDir();

        //getline(&input, &len, stdin); // Read the user input
        fgets(user_command, TOTAL_STRING_SIZE, stdin);

        token = strtok(user_command, spaces);
        argv[argc] = token;

        while (token != NULL) {
          token = strtok(NULL, spaces);
          argc++;
          argv[argc] = token;
        }

        choices(argc, argv);

        /*
        user_command[strlen(user_command) - 1] = '\0';

        if (strcmp(user_command, "clr") == 0) {
          clearScreen();
        } else if (strcmp(argv[0], "help") == 0) {
          help();
        } else if (strcmp(user_command, "pauses") == 0) {
          pauses();
        } else if (strcmp(user_command, "quit") == 0) {
          quit(argv);
          break;
        } else if (strcmp(user_command, "echo") == 0) {
          echo(argc, argv);
        } else if (strcmp(user_command, "cd") == 0) {
          //changeDir(argv);
        }
        */
    }
}
