#ifndef _commands_h
#define _commands_h

void child(char **args);
void printEnv();
void execArgs(char **args, int *pids, int *count);
void execCD();
void showPID();


#endif