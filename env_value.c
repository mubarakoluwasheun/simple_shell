#include "shell.h"

char *_getpid(void);
char *environ_value(char *var, int len);
void var_replace(char **args, int *ret);

/**
 * _getpid - Gets the current process ID of the shell
 *
 * Return: On SUCCESS, returns (pid) ie the current process ID
 *	   On FAILURE, returns (NULL)
 */
char *_getpid(void)
{
	char *pid;
	size_t i = 0;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	pid = malloc(128);
	if (!pid)
	{
		close(file);
		return (NULL);
	}
	read(file, pid, 128);

	for (i = 0; pid[i] != ' '; i++)

	pid[i] = '\0';
	close(file);

	return (pid);
}

/**
 * environ_value - Gets the value associated with an environment variable
 * @var: The environment variable to search for
 * @len: The length of the environment variable to search for
 *
 * Return: On SUCCESS, returns (env_fetched) ie the value of the env variable
 *	   On FAILURE, returns (NULL) to indicate env variable is not found
 *
 */
char *environ_value(char *var, int len)
{
	char *i, *environ_name, **environ_addr, *environ_fetched = NULL;

	environ_name = malloc(len + 1);
	if (!environ_name)
		return (NULL);
	environ_name[0] = '\0';
	_strncat(environ_name, var, len);

	environ_addr = _getenv(environ_name);
	free(environ_name);
	if (environ_addr)
	{
		for (i = *environ_addr; *i != '='; i++)
		i++;
		environ_fetched = malloc(_strlen(i) + 1);
		if (environ_fetched)
			_strcpy(environ_fetched, i);
	}
	return (environ_fetched);
}

/**
 * var_replace - Handles variable replacement
 * @args: A 2D pointer containing the command line arguments
 * @ret: A pointer to the return value of the last command
 */

void var_replace(char **args, int *ret)
{
	int len, i = 0, j = 0;
	char *new_bytes, *old_bytes = NULL, *value = NULL;

	old_bytes = *args;
	while (old_bytes[i])
	{
		if (old_bytes[i] == '$' && old_bytes[i + 1] && old_bytes[i + 1] != ' ')
		{
			if (old_bytes[i + 1] == '$')
			{
				value = _getpid();
				j = i + 2;
			}
			else if (old_bytes[i + 1] == '?')
			{
				value = _itoa(*ret);
				j = i + 2;
			}
			else if (old_bytes[i + 1])
			{
				j = i + 1;
				while (old_bytes[j] && old_bytes[j] != '$' && old_bytes[j] != ' ')
					j++;
				len = j - (i + 1);
				value = environ_value(&old_bytes[i + 1], len);
			}
			new_bytes = malloc(i + _strlen(value) + _strlen(&old_bytes[j]) + 1);
			if (!args)
				return;
			new_bytes[0] = '\0';
			_strncat(new_bytes, old_bytes, i);
			if (value)
			{
				_strcat(new_bytes, value);
				free(value);
				value = NULL;
			}
			_strcat(new_bytes, &old_bytes[j]);
			free(old_bytes);
			*args = new_bytes;
			old_bytes = new_bytes;
			i = -1;
		}
		i++;
	}
}

