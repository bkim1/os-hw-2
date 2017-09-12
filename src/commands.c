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
Function for child processes
Executes the command with execvp 
*/
void child(char **args) {
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
Handles creation of new process 
Separates execution for parent and children
*/
void execArgs(char **args, int *pids, int *count) {
    int pid;

    switch(pid = fork()) {
        // Error with the fork() 
        case(-1):
            perror(ANSI_RED "Error: " ANSI_RESET "Fork failed.");
            exit(1);
        
        // In child process 
        case(0):
            child(args);
            break;

        // In parent process
        default: {
            pids[*count] = pid;

            int childPID;
            int code;
            childPID = waitpid(pid, &code, 0);
        }
    }
}

/*
Changes current working directory
Sets environment variables correctly
*/
void execCD(char *path, int max) {
    char oldCWD[max];
    getcwd(oldCWD, sizeof(oldCWD));

    chdir(path);
    char pwd[max];
    getcwd(pwd, sizeof(pwd));
    
    /* Set new ENV paths */
    setenv("PWD", pwd, 1);
    setenv("OLDPWD", oldCWD, 1);
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