#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "commands.h"

#define ANSI_RED   "\x1B[31m"
#define ANSI_MAG   "\x1B[35m"
#define ANSI_RESET "\x1B[0m"

#define MAX_TOKEN     10
#define MAX_LINE_LEN  80
#define MAX_PID_COUNT 5
#define MAX_PATH_LEN  100

int pids[MAX_PID_COUNT];
char string[MAX_LINE_LEN];
char *args[MAX_TOKEN];

void reorderPIDS();
void prompt();
int getInput(char *line);
int getArguments(char *line, char **args, char *delimiters);

int main(int argc, char **argv) {
    char delimiters[] = " \n";
    int pidCount = 0;

    while (1) {
        int argCount;
        int backgrd;
        int pid;

        // Get user input
        if (getInput(string) == 1) { 
            argCount = getArguments(string, args, delimiters);
        }
        else { argCount = 0; }

        // Execute correct function depending on command
        if (argCount > 0 && strcmp(args[0], "\n") != 0) {
            if (strcmp("exit", args[0]) == 0){
                printf("exit\n");
                exit(0);
            }
            else if (strcmp("cd", args[0]) == 0) {
                execCD(args[1], MAX_PATH_LEN);
            }
            else if (strcmp("showpid", args[0]) == 0) {
                showPID(pids, MAX_PID_COUNT);
            }
            else if (strcmp("environ", args[0]) == 0) {
                printEnv();
            }
            else {
                // Check for background processing
                if (strcmp("&", args[argCount - 1]) == 0) {
                    args[argCount - 1] = NULL;
                    argCount--;
                    backgrd = 1;
                }
                else { backgrd = 0; }

                pid = execArgs(args, argCount, backgrd);
                pidCount++;

                if (pidCount == MAX_PID_COUNT) {
                    reorderPIDS();
                    pids[MAX_PID_COUNT - 1] = pid;
                    pidCount--;
                }
                else { pids[pidCount] = pid; }
            }            
        }

    }
}

/* Makes room for new PID in the list */
void reorderPIDS() {
    for (int i = 0; i < MAX_PID_COUNT - 1; i++) {
        pids[i] = pids[i+1];
    }
    pids[MAX_PID_COUNT - 1] = 0; 
}

/* 
Prints the prompt for the user
Displays the current folder the user is in and the user
*/
void prompt() {
    /* Get current Username */
    char *user;
    user = getenv("USER");

    /* Get Current Folder Path */
    char cwd[MAX_PATH_LEN];
    char *currFolder;
    int c = '/';
    
    getcwd(cwd, sizeof(cwd));
    currFolder = strrchr(cwd, c);
    currFolder++;
    
    printf("bkims-shell:%s " ANSI_MAG "%s" ANSI_RESET "$ ", currFolder, user);
}

/* 
Prompts the User for input
Checks for leading whitespace and going over line length
 */
int getInput(char *line) {
    prompt();

    /* Skip leading whitespace */
    while (1) { 
        int c = getchar();
        if (c == 10) { return 0; }
        if (!isspace(c)) {
             ungetc(c, stdin);
             break;
        }
    }

    int i = 0;
    while (1) {
        int c = getchar();

        if (c == 10) { /* at end, add terminating zero */
            line[i] = 0;
            break;
        }
        line[i] = c;
        if (i == MAX_LINE_LEN - 1) { /* buffer full */
            perror(ANSI_RED "Error: " ANSI_RESET "Line is too long");

            /* Clear Input Buffer */
            while ((c = getchar()) != '\n' && c != EOF) { }
            return 0;
        }
        i++;
    }
    return 1;
}

/* 
Reuse getArguments() method for parsing line
Added check for maximum number of string tokens allowed 
Original Author: Professor Signorile
*/
int getArguments(char *line, char **args, char *delimiters) {
    int count = 0;
    char *cp;

    cp = strdup (line);               //Make writable copy.
    args[count] = strtok (cp, delimiters); //get first token
    count++;

    while ( (args[count] = strtok (NULL, delimiters)) ) { 
        // printf("%d. %s\n", count, args[count]);
        if (count > MAX_TOKEN) {
            perror(ANSI_RED "Error: " ANSI_RESET "Too many arguments given");
            return -1;
        }
        count++;
    }
    return count;
}


