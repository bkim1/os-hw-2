#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "commands.h"

#define ANSI_RED   "\x1B[31m"
#define ANSI_MAG   "\x1B[35m"
#define ANSI_RESET "\x1B[0m"

extern char **environ;


/*
Handles creation of new process 
Separates execution for parent and children
*/
int execArgs(char **args, int argCount, int backgrd) {
    int pid;

    switch(pid = fork()) {
        // Error with the fork() 
        case(-1):
            perror(ANSI_RED "Error: " ANSI_RESET "Fork failed.");
            exit(1);
        
        // In child process 
        case(0):
            child(args, argCount, backgrd);
            break;

        // In parent process
        default: {
            if (backgrd != 1) {
                int childPID;
                int code;

                childPID = waitpid(pid, &code, 0);
            }
            return pid;
        }
    }
    return 0;
}

/* 
Function for child processes
Executes the command with execvp 
*/
void child(char **args, int argCount, int backgrd) {
    int i;
    int redirect = 0;

    // Check for any I/O Redirection
    for (i = 0; i < argCount; i++) {
        // Input Redirection
        if (strcmp("<", args[i]) == 0) {
            i++;
            
            if ( access(args[i], F_OK | R_OK) == 0 ) {
                redirect = 1;
                freopen(args[i], "r", stdin);
            }
            else {
                perror("Not a valid file");
            }
            args[i - 1] = NULL;
            args[i] = NULL;
        }
        // Output Redirection
        else if (strcmp(">", args[i]) == 0) {
            redirect = 1;
            i++;
            freopen(args[i], "w", stdout);

            args[i - 1] = NULL;
            args[i] = NULL;
        }
    }

    if (backgrd == 1 && redirect == 0) { printf("\n"); }
    
    execvp(args[0], args);

    perror(ANSI_RED "Error: " ANSI_RESET "Command failed");
    exit(1);
}

/* 
Prints all environment variables 
Original Author: Professor Signorile
*/
void printEnv() {
    char **env = environ;
    while (*env) { printf("%s\n", *env++); }
}

/*
Changes current working directory
Sets environment variables correctly
*/
void execCD(char *path, int max) {
    char oldCWD[max];
    getcwd(oldCWD, sizeof(oldCWD));

    if (chdir(path) == -1) {
        perror(ANSI_RED "Error" ANSI_RESET);
    }
    else {
        char pwd[max];
        getcwd(pwd, sizeof(pwd));
        
        /* Set new ENV paths */
        setenv("PWD", pwd, 1);
        setenv("OLDPWD", oldCWD, 1);
    }
}

/*
Prints last 5 PIDs created
*/
void showPID(int *pids, int max) {
    for (int i = 0; i < max; i++) {
        if (pids[i] != 0) {
            printf("%i\n", pids[i]);
        }
    }
}