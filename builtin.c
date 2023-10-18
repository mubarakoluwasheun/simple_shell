#include "shell.h"

int (*check_builtins(char *cmd))(char **args, char **arg0);
int _shellexit(char **args, char **arg0);
int _cd(char **args, char __attribute__((__unused__)) **arg0);

/**
 * check_builtins - Matches a command with the associated builtin function
 * @cmd: The command to match
 *
 * Return: Returns a function pointer to the associated builtin
 */
int (*check_builtins(char *cmd))(char **args, char **arg0)
{
	int i;

	builtins func_list[] = {
		{"exit", _shellexit},
		{"env", _printenv},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd },
		{NULL, NULL}
	};
	for (i = 0; func_list[i].name; i++)
	{
		if (_strcmp(func_list[i].name, cmd) == 0)
			break;
	}
	return (func_list[i].fpt);
}

/**
 * _shellexit - Terminates program execution of the shell
 * @args: Array of arguments containing the exit value
 * @arg0: A double pointer to the start of the arguments
 *
 * Return: On SUCCESS, exits with the given status value
 *	   On FAILURE,	returns (-3) if there are no arguments
 *	   returns (-2) if the exit value is invalid
 */
int _shellexit(char **args, char **arg0)
{
	int i, max_len = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			max_len++;
		}
		for (i = 0; args[0][i]; i++)
		{
			if (i <= max_len && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (_error(--args, 2));
	args -= 1;
	free_stdin_cmd(args, arg0);
	free_environ();
	exit(num);
}

/**
 * _cd - Changes the current directory of the shell
 * @args: An array of arguments
 * @arg0: A double pointer to the beginning of args
 *
 * Return: On SUCCESS,	returns (0)
 *	   On FAILURE,	returns (-2) if the string is not a directory
 *	   returns (-1) if an error occurs
 */
int _cd(char **args, char __attribute__((__unused__)) **arg0)
{
	struct stat dir;
	char **pathInfo, *new_line = "\n", *prev_dir = NULL, *pwd = NULL;

	prev_dir = getcwd(prev_dir, 0);
	if (!prev_dir)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(prev_dir);
				return (_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(prev_dir);
				return (_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	pathInfo = malloc(sizeof(char *) * 2);
	if (!pathInfo)
		return (-1);

	pathInfo[0] = "OLDPWD";
	pathInfo[1] = prev_dir;
	if (_setenv(pathInfo, pathInfo) == -1)
		return (-1);

	pathInfo[0] = "PWD";
	pathInfo[1] = pwd;
	if (_setenv(pathInfo, pathInfo) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(prev_dir);
	free(pwd);
	free(pathInfo);
	return (0);
}
