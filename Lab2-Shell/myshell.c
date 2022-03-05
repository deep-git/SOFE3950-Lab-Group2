#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>
#include "myshell.h"

// Define specifications
#define STRING_NUM 8
#define TOTAL_STRING_SIZE 500
#define MAX_SIZE 1024

// Define colours
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

<<<<<<< Updated upstream

=======
// Prompts the user
>>>>>>> Stashed changes
void shellPrompt(void){
  char cwd[PATH_MAX];
  printf(YELLOW "%s$ " NORMALCOLOUR, getcwd(cwd, MAX_SIZE));
  //printf(YELLOW "%s" NORMALCOLOUR, "~/myShell$ ");             

}

// Prints the current directory
void printDir(void){
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("\n%s\n\n", cwd);
}

<<<<<<< Updated upstream
void changeDir(char *dir) {
    char cwd[MAX_SIZE];
    
    if (dir != NULL){
      // printf("I am here");
      putenv(dir);                    
      getcwd(cwd, sizeof(cwd));       //grab current dir

      strncat(cwd, "/", 2);               
		  strncat(cwd, dir, strlen(dir)); //apppend change in directory to cwd

      //printf("\n%s\n\n", cwd);        //testing - display current directory

      if (chdir(cwd) < 0)             //checks if no file/directory of that name is found 
        printf("ERROR: File / Directory could not be found (%s)\n", dir);
      return;
=======
// Function to change the directory
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
>>>>>>> Stashed changes
    }

}

// Function to print the contents of the current directory
void dir(void) {
}

// Function to print the environment strings
void environ(void) {

}

// Function to display echo message
void echo(int argc, char **argv) {

  // If the user entered a message after the word echo
	if (argv[1] != NULL) {
    // Loops through the amount of words to echo
		for (int i = 1; i < argc; i++) {
      // Prints the echoed word
			printf("%s ", argv[i]);
		}
    printf("\n");

  // If the user did not enter anything to echo
	} else {
		printf("Invalid echo format: echo <comment>\n");
	}
}

// Function to provide user with help manual
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

  // Displays the help manual
  for (int i = 0; i < STRING_NUM; i++) {
    printf("%s \n\n", options[i]);
  }
}

// Function to pause the command line
void pauses(void) {
    printf("Operation currrently PAUSED. Press ENTER key to Continue\n");
    getchar();
}

// Exits the program
int quit(char **argv) {
	return 0;
}

// Function to clear the screen
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

// Performs actions based on specific user input entered
void choices(int argc, char **argv) {

  // If the user entered clr
  if (strcmp(argv[0], "clr") == 0) {
    clearScreen();

      // If the user entered help
  } else if (strcmp(argv[0], "help") == 0) {
    help();

      // If the user entered pauses
  } else if (strcmp(argv[0], "pauses") == 0) {
    pauses();

      // If the user entered quit
  } else if (strcmp(argv[0], "quit") == 0) {
    quit(argv);
    exit(0);

      // If the user entered echo
  } else if (strcmp(argv[0], "echo") == 0) {
    echo(argc, argv);

      // If the user entered environ
  } else if (strcmp(argv[0], "environ") == 0) {
    environ();

      // If the user entered cd
  } else if (strcmp(argv[0], "cd") == 0) {
    changeDir(argv);
    printDir();

     // If the user entered myshell
  } else if (strcmp(argv[0], "myshell") == 0) {
    fileIO(args);
  }
}

int main () {

  // Variables to keep track of user input
  char **argv = malloc(sizeof(char) * TOTAL_STRING_SIZE);
  char *token;
  char spaces[] = " \n\t";
  int argc = 0;

  char user_command[TOTAL_STRING_SIZE];

    initialize();   ///welcome screen

    // While loop to prompt user to enter command line input as long as the program is still running
    while(1){

        shellPrompt();
        //printDir();

        // Resets the argv array and user inputs
        argc = 0;
        for (int i = 0; i < argc; i++) {
          argv[i] = NULL;
        }

        // Takes in user input
        fgets(user_command, TOTAL_STRING_SIZE, stdin);

        // Splices the user input into separate words and stores them within the argv array
        token = strtok(user_command, spaces);
        argv[argc] = token;

        while (token != NULL) {
          token = strtok(NULL, spaces);
          argc++;
          argv[argc] = token;
        }

        // Sends the user input to the choices function to determine the action based on the input
        choices(argc, argv);
    }
}
