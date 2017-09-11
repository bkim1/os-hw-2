#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "commands.h"

void execArgs(char **args) {
    int pid;
    pid = fork();

    switch(pid) {
        // Error with the fork() 
        case(-1):
            perror("Fork failed.");
            exit(1);
        
        // In child process 
        case(0):
            child(args);
            break;

        // In parent process
        default:
            printf("IM THE PARENT!!!\n");
            int status;
            int child_pid;
            child_pid = wait(&status);

            printf("Child: %i\n", child_pid);
            printf("Exited with status: %i\n", status);
    }
}

void child(char **args) {
    printf("IM THE CHILD!!!\n");
    exit(0);
}

void showPID() {
    printf("showpid command called\n");
}

void execCD() {
    printf("CD command called\n");
}