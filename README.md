# Programming Project 1
---
Author: Branden Kim

Class: Operating Systems

---

## How to run the project:
1. Ensure all files in same directory
2. Open a terminal window to the directory containing the files
3. Run `gcc -o shell shell.c commands.c`
4. Run `./shell`

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

## Challenges:

Writing in C
* Been a while since I had written in C, so it took some time to get used to it again
* Dealing with pointers

Ignoring leading and trailing whitespace
* Had to get input for every character given in line
* Function adapted from StackOverflow answer 

Issues with displaying current folder in prompt
* Originally had a separate function for returning the PWD
* Ran into issues with returning the pointer to the array of chars
* Worked around it by having a separate function that prints the prompt instead of returning a pointer

## Sources used:

StackOverflow

Canvas (Professor Signorile's code)
* Noted in comments

