#include "main.h"

/**
	* check_absolute_path - Checks if command is absolute or relative path
	* @command: The command to check
	*
	* Return: Full path if exists, NULL otherwise
	*/
char *check_absolute_path(char *command)
{
	struct stat st;

	if (command[0] == '/' || command[0] == '.')
	{
	if (stat(command, &st) == 0)
	return (strdup(command));
	}
	return (NULL);
}

/**
	* search_in_path - Searches for command in PATH directories
	* @command: The command to find
	* @path_copy: Copy of PATH environment variable
	*
	* Return: Full path if found, NULL otherwise
	*/
char *search_in_path(char *command, char *path_copy)
{
	char *dir, *full_path;
	struct stat st;

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
