#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "commands.h"

#define ANSI_RED   "\x1B[31m"
#define ANSI_RESET "\x1B[0m"

extern char **environ;

void child(char **args) {
    execvp(args[0], args);

    // printf(ANSI_RED "Error: " ANSI_RESET);
    perror(ANSI_RED "Error: " ANSI_RESET "Command failed");
    exit(1);
}

void printEnv() {
    char **env = environ;
    while (*env) { printf("%s\n", *env++); }
}

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
            childPID = wait(&code);
        }
    }
}

void execCD(char *path, int max) {
    char oldcwd[max];
    getcwd(oldcwd, sizeof(oldcwd));

    chdir(path);
    char pwd[max];
    getcwd(pwd, sizeof(pwd));
    
    /* Set new ENV paths */
    setenv("PWD", pwd, 1);
    setenv("OLDPWD", oldcwd, 1);
}

void showPID(int *pids, int max) {
    for (int i = 0; i < max; i++) {
        if (pids[i] != 0) {
            printf("%i\n", pids[i]);
        }
    }
}