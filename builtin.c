#include "main.h"

/**
	* handle_exit - Handles the exit built-in command
	*
	* Return: void (exits the program)
	*/
void handle_exit(void)
{
	exit(0);
}

/**
	* handle_env - Handles the env built-in command
	*
	* Return: 0 on success
	*/
int handle_env(void)
{
	char **env = environ;

	while (*env)
	{
	printf("%s\n", *env);
	env++;
	}
	return (0);
}

/**
 * is_builtin - Checks if command is a built-in command
 * @args: Array of command arguments
 *
 * Return: 1 if built-in executed, 0 otherwise
 */
int is_builtin(char **args)
{
    if (args == NULL || args[0] == NULL)
        return (0);

      if (strcmp(args[0], "exit") == 0)
    {
        handle_exit();
        return (1);
    }

    return (0);
}
