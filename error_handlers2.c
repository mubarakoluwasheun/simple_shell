#include "shell.h"

char *error126(char **args);
char *error127(char **args);

/**
 * error126 - Creates an error message for permission denied failures
 * @args: An array of arguments passed to the command line
 *
 * Return: On SUCCESS, returns (error) ie the error string
 *	   On FAILURE, returns (NULL)
 *
 */
char *error126(char **args)
{
	int len;
	char *error, *histStr;

	histStr = _itoa(cmd_hist);
	if (!histStr)
		return (NULL);

	len = _strlen(name) + _strlen(histStr) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(histStr);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, histStr);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(histStr);
	return (error);
}

/**
 * error127 - Creates an error message for command not found failures
 * @args: An array of arguments passed to the command line
 *
 * Return: On SUCCESS, returns (error) ie the error string
 *	   On FAILURE, returns (NULL)
 */
char *error127(char **args)
{
	int len;
	char *error, *histStr;

	histStr = _itoa(cmd_hist);
	if (!histStr)
		return (NULL);

	len = _strlen(name) + _strlen(histStr) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(histStr);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, histStr);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(histStr);
	return (error);
}
