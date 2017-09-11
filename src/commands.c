#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "commands.h"

void execArgs(char **args) {
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
            int child_pid;
            int code;
            child_pid = wait(&code);

            printf("Exited with code: %i\n", code);
        }
    }
}

void child(char **args) {
    // printf("IM THE CHILD!!!\n");
    
    printf("%s\n", args[0]);
    execvp(args[0], args);

    perror("excevp failed");
    exit(1);
}

void showPID() {
    printf("showpid command called\n");
}

void execCD() {
    printf("CD command called\n");
}