#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

/* Environment variable */
extern char **environ;

/* Main shell functions */
void display_prompt(void);
char *read_line(void);
char **parse_line(char *line);
void free_array(char **array);

/* Path and execution functions */
char *find_path(char *command);
int execute_command(char **args, char *argv0);
int fork_and_execute(char *command_path, char **args, char *argv0);

/* Built-in command functions */
void handle_exit(void);
int handle_env(void);
int is_builtin(char **args);

#endif /* MAIN_H */
