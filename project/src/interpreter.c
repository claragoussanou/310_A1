#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellmemory.h"
#include "shell.h"
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>

int MAX_ARGS_SIZE = 3;

int badcommand() {
    printf("Unknown Command\n");
    return 1;
}

// For source command only
int badcommandFileDoesNotExist() {
    printf("Bad command: File not found\n");
    return 3;
}

int badcommandmkdir() {
    printf("Bad command: my_mkdir\n");
    return 4;
}

int comp(const void *a,const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}


int help();
int quit();
int set(char *var, char *value);
int print(char *var);
int source(char *script);
int echo(char *var);
int my_ls();
int my_mkdir(char *var);
int my_touch(char *var);
int badcommandFileDoesNotExist();

// Interpret commands and their arguments
int interpreter(char *command_args[], int args_size) {
    int i;

    if (args_size == 0 && !isatty(fileno(stdin))) {
            return quit();
    }

    if (args_size < 1 || args_size > MAX_ARGS_SIZE) {
        return badcommand();
    }

    for (i = 0; i < args_size; i++) {   // terminate args at newlines
        command_args[i][strcspn(command_args[i], "\r\n")] = 0;
    }

    if (strcmp(command_args[0], "help") == 0) {
        //help
        if (args_size != 1)
            return badcommand();
        return help();

    } else if (strcmp(command_args[0], "quit") == 0) {
        //quit
        if (args_size != 1)
            return badcommand();
        return quit();

    } else if (strcmp(command_args[0], "set") == 0) {
        //set
        if (args_size != 3)
            return badcommand();
        return set(command_args[1], command_args[2]);

    } else if (strcmp(command_args[0], "print") == 0) {
        if (args_size != 2)
            return badcommand();
        return print(command_args[1]);

    } else if (strcmp(command_args[0], "source") == 0) {
        if (args_size != 2)
            return badcommand();
        return source(command_args[1]);

    } else if (strcmp(command_args[0], "echo") == 0) {
        //echo
        if (args_size != 2)
            return badcommand();
        return echo(command_args[1]);

    } else if (strcmp(command_args[0], "my_ls") == 0) {
        //my_ls
        if (args_size != 1)
            return badcommand();
        return my_ls();

    } else if (strcmp(command_args[0], "my_mkdir") == 0) {
        //my_mkdir
        if (args_size != 2)
            return badcommand();
        return my_mkdir(command_args[1]);

    } else if (strcmp(command_args[0], "my_touch") == 0) {
        //my_touch
        if (args_size != 2)
            return badcommand();
        return my_touch(command_args[1]);

     } else if (strcmp(command_args[0], "my_ls") == 0) {
        if (args_size != 1)
            return badcommand();
        return my_ls(command_args[1]);

    } else
        return badcommand();
}

int help() {

    // note the literal tab characters here for alignment
    char help_string[] = "COMMAND			DESCRIPTION\n \
help			Displays all the commands\n \
quit			Exits / terminates the shell with “Bye!”\n \
set VAR STRING		Assigns a value to shell memory\n \
print VAR		Displays the STRING assigned to VAR\n \
source SCRIPT.TXT	Executes the file SCRIPT.TXT\n ";
    printf("%s\n", help_string);
    return 0;
}

int quit() {
    printf("Bye!\n");
    exit(0);
}

int set(char *var, char *value) {
    // Challenge: allow setting VAR to the rest of the input line,
    // possibly including spaces.

    // Hint: Since "value" might contain multiple tokens, you'll need to loop
    // through them, concatenate each token to the buffer, and handle spacing
    // appropriately. Investigate how `strcat` works and how you can use it
    // effectively here.

    mem_set_value(var, value);
    return 0;
}


int print(char *var) {
    printf("%s\n", mem_get_value(var));
    return 0;
}

int source(char *script) {
    int errCode = 0;
    char line[MAX_USER_INPUT];
    FILE *p = fopen(script, "rt");      // the program is in a file

    if (p == NULL) {
        return badcommandFileDoesNotExist();
    }

    fgets(line, MAX_USER_INPUT - 1, p);
    while (1) {
        errCode = parseInput(line);     // which calls interpreter()
        memset(line, 0, sizeof(line));

        if (feof(p)) {
            break;
        }
        fgets(line, MAX_USER_INPUT - 1, p);
    }

    fclose(p);

    return errCode;
}


int echo(char *var) {
    if (var[0] == '$') {
        char *result = mem_get_value(&var[1]);
        if (strcmp(result,"Variable does not exist")) {
            printf("%s\n", result);
        } else {
            printf("\n");
        }
    } else {
    printf("%s\n", var);
    }
    return 0;
}

int my_ls() {
    DIR *directory = opendir(".");
    struct dirent *dircontents = readdir(directory);

    int len = 0;
    while (dircontents) {
        len++;
        dircontents = readdir(directory);
    }

    char *files[len];
    rewinddir(directory);
    struct dirent *dircontents2 = readdir(directory);
    for (int i = 0; i < len; i++) {
        files[i] = dircontents2->d_name;
        dircontents2 = readdir(directory);
    }
    closedir(directory);

    qsort(files,len, sizeof(char *),comp);
    for (int i = 0; i < len; i++)
        printf("%s\n", files[i]);
    return 0;
}

int my_mkdir(char *var) {
    int len = strlen(var);
    for (int i = 1; i < len; i++){
        if (!isalnum(var[i])) {
            return badcommandmkdir();
        }
    }

    if (var[0] == '$') {
        char *result = mem_get_value(&var[1]);
        if (strcmp(result,"Variable does not exist")) {
            int i = 0;
            while (result[i] != '\0') {
                if (!isalnum(result[i])) {
                    return badcommandmkdir();
                }
                i++;
            }
            mkdir(result,755);
            return 0;
        }
        
    } else if (isalnum(var[0])) {
        mkdir(var,755);
        return 0;
    }
    return badcommandmkdir();
}

int my_touch(char *var) {
    int len = strlen(var);
    for (int i = 1; i < len; i++){
        if (!isalnum(var[i])) {
            return badcommandmkdir();
        }
    }

    FILE *fp = fopen(var,"w");
    fclose(fp);
    return 0;
}

