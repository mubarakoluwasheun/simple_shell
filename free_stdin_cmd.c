#include "shell.h"

void free_stdin_cmd(char **args, char **arg0);

/**
 * free_stdin_cmd - Frees up memory taken by stdin commands
 * @args: A 2D pointer to the commands entered
 * @arg0: A 2D pointer to the start of commands
 */
void free_stdin_cmd(char **args, char **arg0)
{
	size_t i = 0;

	while (args[i] || args[i + 1])
	{
		free(args[i]);
		i++;
	}
	free(arg0);
}
