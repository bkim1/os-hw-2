#ifndef _commands_h
#define _commands_h

void sigCatch();
void child(char **args, int argCount, int backgrd);
void printEnv();
int execArgs(char **args, int argCount,int backgrd);
void execCD(char *path, int max);
void showPID();


#endif