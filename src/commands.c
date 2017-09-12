#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "commands.h"

extern char **environ;

void child(char **args) {
    execvp(args[0], args);

    perror("Error: Command failed");
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
            perror("Fork failed.");
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

            if (code != 0) {
                printf("Exited with code: %i\n", code);
            }
        }
    }
}

void execCD() {
    printf("CD command called\n");
}

void showPID(int *pids, int max) {
    for (int i = 0; i < max; i++) {
        if (pids[i] != 0) {
            printf("%i\n", pids[i]);
        }
    }
}