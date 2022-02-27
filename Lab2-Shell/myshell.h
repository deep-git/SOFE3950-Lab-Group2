#include <stddef.h>

// Declare global variables 
    //int system(const char *command);   

char *input = NULL;
size_t len = 0;

// Initializes cmd line interpreter
extern void initialize(void);

// Prints "~/myShell$ " 
extern void shellPrompt(void);
