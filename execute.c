#include "main.h"

/**
 * find_path - Finds the full path of a command
 * @command: The command to find
 *
 * Return: Full path of command, or NULL if not found
 */
char *find_path(char *command)
{
    char *path_env, *path_copy, *dir;
    char *full_path;
    struct stat st;

    if (command[0] == '/' || command[0] == '.')
    {
        if (stat(command, &st) == 0)
            return (strdup(command));
        return (NULL);
    }

    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);

    path_copy = strdup(path_env);
    dir = strtok(path_copy, ":");

    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path)
        {
            free(path_copy);
            return (NULL);
        }
        sprintf(full_path, "%s/%s", dir, command);

        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return (full_path);
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}

/**
 * execute_command - Executes a command
 * @args: Array of arguments
 * @argv0: Program name for error messages
 *
 * Return: 0 on success, 1 on failure
 */
int execute_command(char **args, char *argv0)
{
    pid_t pid;
    int status;
    char *command_path;

    if (strcmp(args[0], "exit") == 0)
        exit(0);

    if (strcmp(args[0], "env") == 0)
    {
        char **env = environ;

        while (*env)
        {
            printf("%s\n", *env);
            env++;
        }
        return (0);
    }

    command_path = find_path(args[0]);
    if (!command_path)
    {
        fprintf(stderr, "%s: 1: %s: not found\n", argv0, args[0]);
        return (1);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(command_path);
        return (1);
    }

    if (pid == 0)
    {
        if (execve(command_path, args, environ) == -1)
        {
            perror(argv0);
            free(command_path);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
        free(command_path);
    }

    return (0);
}
