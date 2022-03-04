#include <stddef.h>
#include <unistd.h>

// Declare global variables
    //int system(const char *command);

char *input = NULL;
size_t len = 0;

// Initializes cmd line interpreter
extern void initialize(void);

// Prints "~/myShell$ "
extern void shellPrompt(void);

// Print current working directory
extern void printDir(void);

// Change working directory
extern int changeDir(char* path[]);

// List contents of directory
extern void dir(void);

// List all the environment strrings
extern void environ(void);

// Print given <comment> on display followed by a new line
extern void echo(int argc, char **argv);

// Display the user manual
extern void help(void);

// Pause operation of the shell until 'Enter' is pressed
extern void pauses(void);

// Display the user manual
extern int quit(char **argv);
