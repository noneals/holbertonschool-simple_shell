#include "main.h"

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

    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);

    path_copy = strdup(path_env);
    dir = strtok(path_copy, ":");

    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
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
