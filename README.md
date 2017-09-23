# Programming Project 2
---
Author: Branden Kim

Class: Operating Systems

---

## How to run the project:
1. Ensure all files in same directory
2. Open a terminal window to the directory containing the files
3. Run `gcc -o shell shell.c commands.c`
4. Run `./shell`

## Differences from Project 1

* Added redirection of stdin and stdout
* Added background processing of tasks
    * Specified with an '&' at the end of the command
* Refactored parts of project to work with new commands

## List of Files:

`shell.c`

* Contains main function for running the shell
* Has functions for getting the input from the user
    * User input assumptions:
        * **ACCEPTS** leading & trailing whitespace
        * Line limited to 80 characters
        * Arguments limited to 10
* Prompt displays current folder

`commands.h`

* Header file for commands.c  

`commands.c`

* Separate file containing the functions used for commands
    * Created separate file in order to keep `shell.c` cleaner
* Handles the `fork()` command and handling the parent/child processes
* Has separate functions for following commands:
    * `cd`
    * `environ`
    * `showpid`


