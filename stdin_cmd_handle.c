#include "shell.h"

char *get_stdin_cmd(char *line, int *ret);
int call_stdin_cmd(char **args, char **arg0, int *ret);
int run_stdin_cmd(char **args, char **arg0, int *ret);
int handle_stdin_cmd(int *ret);
int check_stdin_cmd(char **args);

/**
 * get_stdin_cmd - Gets a command from standard input
 * @line: A buffer to store the command
 * @ret: The return value of the last executed command
 *
 * Return: On SUCCESS, returns (line) ie a pointer to the stored command
 *	   On FAILURE, returns (NULL) to indicate an error occurred
 */
char *get_stdin_cmd(char *line, int *ret)
{
	char *prompt = ">$ ";
	size_t input = 0;
	ssize_t read_bytes;

	if (line)
		free(line);

	read_bytes = _getline(&line, &input, STDIN_FILENO);
	if (read_bytes == -1)
		return (NULL);
	if (read_bytes == 1)
	{
		cmd_hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 3);
		return (get_stdin_cmd(line, ret));
	}

	line[read_bytes - 1] = '\0';
	var_replace(&line, ret);
	split_line(&line, read_bytes);

	return (line);
}

/**
 * call_stdin_cmd - Separates operators from commands and calls the commands
 * @args: An array of arguments
 * @arg0: A 2D pointer to the start of args
 * @ret: The return value of the last executed command of the parent process
 *
 * Return: Returns the return value of the last executed command
 */
int call_stdin_cmd(char **args, char **arg0, int *ret)
{
	int status, i = 0;

	if (!args[0])
		return (*ret);
	while (args[i])
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			status = run_stdin_cmd(args, arg0, ret);
			if (*ret != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				while (args[++i])
					free(args[i]);
				return (status);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			status = run_stdin_cmd(args, arg0, ret);
			if (*ret == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				while (args[++i])
					free(args[i]);
				return (status);
			}
		}
		else
		{
			i++;
		}
	}
	status = run_stdin_cmd(args, arg0, ret);
	return (status);
}

/**
 * run_stdin_cmd - Calls the execution of a command
 * @args: An array of arguments
 * @arg0: A 2D pointer to the start of args
 * @ret: The return value of the last executed command of the parent process
 *
 * Return: Returns the return value of the last executed command
 */
int run_stdin_cmd(char **args, char **arg0, int *ret)
{
	int status, i = 0;
	int (*builtins)(char **args, char **arg0);

	builtins = check_builtins(args[0]);

	if (builtins)
	{
		status = builtins(args + 1, arg0);
		if (status != EXIT)
			*ret = status;
	}
	else
	{
		*ret = execute(args, arg0);
		status = *ret;
	}
	cmd_hist++;
	while (args[++i])
		free(args[i]);

	return (status);
}

/**
 * handle_stdin_cmd - Gets, calls, and runs the execution of a command
 * @ret: The return value of the last executed command of the parent process
 *
 * Return: If end-of-file is read, returns _EOF
 *         If the input cannot be tokenized, returns -1
 *         Otherwise returns the exit value of the last executed command
 */
int handle_stdin_cmd(int *ret)
{
	char **args, **arg0, *size = NULL;
	int i = 0, status = 0;

	size = get_stdin_cmd(size, ret);
	if (!size)
		return (_EOF);

	args = _strtok(size, " ");
	free(size);
	if (!args)
		return (status);

	if (check_stdin_cmd(args) != 0)
	{
		*ret = 2;
		free_stdin_cmd(args, args);
		return (*ret);
	}
	arg0 = args;
	while (args[i])
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			status = call_stdin_cmd(args, arg0, ret);
			args = &args[++i];
			i = 0;
		}
		else
		{
			i++;
		}
	}
	if (args)
		status = call_stdin_cmd(args, arg0, ret);
	free(arg0);

	return (status);
}

/**
 * check_stdin_cmd - Checks if there are any leading ';', ';;', '&&', or '||'
 * @args: 2D pointer to tokenized commands and arguments
 *
 * Return: Returns (0) on SUCCESS
 *	   Returns (-2) if ';', '&&', or '||' is placed at an invalid position
 */
int check_stdin_cmd(char **args)
{
	char *current_char, *next;
	size_t i = 0;

	while (args[i])
	{
		current_char = args[i];
		if (current_char[0] == ';' || current_char[0] == '&'
			|| current_char[0] == '|')
		{
			if (i == 0 || current_char[1] == ';')
				return (_error(&args[i], 2));
			next = args[i + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (_error(&args[i + 1], 2));
		}
		i++;
	}
	return (0);
}
