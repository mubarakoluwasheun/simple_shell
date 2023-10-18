#include "shell.h"

int file_error_handler(char *path);
int execute_commands(char *path, int *ret);

/**
 * file_error_handler - Prints "can't open" if the file doesn't exist or
 *		    lacks proper permissions
 * @path: Path to the file
 *
 * Return: Returns (127)
 */
int file_error_handler(char *path)
{
	int len;
	char *error, *hist_str;

	hist_str = _itoa(cmd_hist);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, path);
	_strcat(error, "\n");
	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * execute_commands - Runs a file command stored within
 * @path: Path to the file
 * @ret: Return value of the last executed command
 *
 * Return: On SUCCESS, returns value of the last command ran
 *	   On FAILURE, returns 127 if the file can't be opened
 *	   Returns -1 if  malloc fails
 */
int execute_commands(char *path, int *ret)
{
	int status;
	char *file_line, **args, **arg0, buffer[128];
	ssize_t file, bytes, i;
	unsigned int fline_size = 0, old_size = 128;

	cmd_hist = 0;
	file = open(path, O_RDONLY);
	if (file == -1)
	{
		*ret = file_error_handler(path);
		return (*ret);
	}
	file_line = malloc(sizeof(char) * old_size);
	if (!file_line)
		return (-1);
	do {
		bytes = read(file, buffer, 127);
		if (bytes == 0 && fline_size == 0)
			return (*ret);
		buffer[bytes] = '\0';
		fline_size += bytes;
		file_line = _realloc(file_line, old_size, fline_size);
		_strcat(file_line, buffer);
		old_size = fline_size;
	} while (bytes);
	for (i = 0; file_line[i] == '\n'; i++)
		file_line[i] = ' ';
	for (; i < fline_size; i++)
	{
		if (file_line[i] == '\n')
		{
			file_line[i] = ';';
			for (i += 1; i < fline_size && file_line[i] == '\n'; i++)
				file_line[i] = ' ';
		}
	}
	var_replace(&file_line, ret);
	split_line(&file_line, fline_size);
	args = _strtok(file_line, " ");
	free(file_line);
	if (!args)
		return (0);
	if (check_stdin_cmd(args) != 0)
	{
		*ret = 2;
		free_stdin_cmd(args, args);
		return (*ret);
	}
	arg0 = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			status = call_stdin_cmd(args, arg0, ret);
			args = &args[++i];
			i = 0;
		}
	}
	status = call_stdin_cmd(args, arg0, ret);

	free(arg0);
	return (status);
}
