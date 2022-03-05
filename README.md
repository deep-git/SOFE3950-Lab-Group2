# SOFE3950-Lab-Group2
Description : 
Shell Scrpting is a open scource computer program desgin which is run by Unix/Linux shell. This scrpit is a program used to write many commands for the shell to execute. These commands can be stored and excuted at anytime which reduces programming efforts.  

A simple shell is a basic shell program that supports commands which I/O redirection. This waits for a user to input a command string and the program parser the command line and determines whether it contains I/O redirection. The sign for output is y > 1 to a file and for input from a file is <. The program has three built in commands which is cd, pwd and exit. These built in functions are not executed by forking. However the shell process executes them itself all other commands must be executed in the child process. 

Some basic knowleage needed for shell : 
I/O redirection : This feature of the command line allows you to redirect the input or output commands from or to files. It can also join multiple commandss together using pipes to form what we call a command pipeline. This is considered one of the most important and interesting topics. 

Program Environment : In unix based systems the enviroment variables are a sets of dynamic named values which are stored within the system. These varibles are used by applications lunched in shells or subshells.  

BackGround Execution : This is the execution of a program that is not visble on the screen whiole the user is free to run other programs on the screen at the same time. This consumes limited resources like RAM and battery. This can affect battry life and performance issues. 
