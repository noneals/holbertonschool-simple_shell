#include "main.h"

/**
 * get_path_env - Gets the PATH environment variable
 *
 * Return: Pointer to PATH value, or NULL if not found
 */
char *get_path_env(void)
{
    int i = 0;

    while (environ[i])
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
            return (environ[i] + 5);
        i++;
    }
    return (NULL);
}

/**
 * find_path - Finds the full path of a command
 * @command: The command name to search for
 *
 * Return: Full path to command if found, NULL otherwise
 */

char *find_path(char *command)
{
    char *path_env, *path_copy, *dir, *full_path;
    struct stat st;

    if (command[0] == '/' || command[0] == '.')
    {
        if (stat(command, &st) == 0)
            return (strdup(command));
        return (NULL);
    }

    path_env = get_path_env();
    if (!path_env)
        return (NULL);

    path_copy = strdup(path_env);
    if (!path_copy)
        return (NULL);
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
