#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "commands.h"

#define MAX_TOKEN 10
#define MAX_LINE_LEN 80 //MAX_SIZE size for string length

char string[MAX_LINE_LEN];
char *args[MAX_TOKEN];

int getInput(char *line);
int getArguments(char *line, char **args, char *delimiters);

int main(int argc, char **argv) {
    char delimiters[] = " \n";

    while (1) {
        int argCount;

        if (getInput(string) == 1) {
            argCount = getArguments(string, args, delimiters);
        }

        if (argCount > 0) {
            if (strcmp("exit", args[0]) == 0){
                printf("exit\n");
                exit(0);
            }
            else if (strcmp("cd", args[0]) == 0) {
                execCD();
            }
            else if (strcmp("showpid", args[0]) == 0) {
                showPID();
            }
            else {
                execArgs(args);
            }            
        }

    }
}

/* 
Prompts the User for input
Checks for leading whitespace and going over line length
 */
int getInput(char *line) {
    printf("prompt$ ");

    /* Skip leading whitespace */
    while (1) { 
        int c = getchar();
        if (c == EOF || c == 10) { break; }
        if (!isspace(c)) {
             ungetc(c, stdin);
             break;
        }
    }

    int i = 0;
    while (1) {
        int c = getchar();
        if (c == EOF || c == 10) { /* at end, add terminating zero */
            line[i] = 0;
            break;
        }
        line[i] = c;
        if (i == MAX_LINE_LEN - 1) { /* buffer full */
            perror("Line is too long");

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
            perror("Too many arguments given");
            return -1;
        }
        count++;
    }
    return count;
}


