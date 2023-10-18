#include "shell.h"

char *env_error(char **args);
char *exit_error(char **args);
char *cd_error(char **args);
char *syntax_error(char **args);

char *name = "hsh"; /* define and initialize name */
int cmd_hist = 0; /* define and initialize cmd_hist */

/**
 * cd_error - Creates an error message for 'cd' errors
 * @args: An array of arguments passed to the command line
 *
 * Return: On SUCCESS, returns (error) ie the error string
 *	   On FAILURE, returns (NULL)
 */
char *cd_error(char **args)
{
	int len;
	char *error, *histStr;

	histStr = _itoa(cmd_hist);
	if (!histStr)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(histStr);
	return (error);
}

/**
 * env_error - Creates an error message for the function '_printenv' errors
 * @args: An array of arguments passed to the command line
 *
 * Return: On SUCCESS, returns (error) ie the error string
 *	   On FAILURE, returns (NULL)
 */
char *env_error(char **args)
{
	int len;
	char *error, *histStr;

	histStr = _itoa(cmd_hist);
	if (!histStr)
		return (NULL);
	args--;
	len = _strlen(name) + _strlen(histStr) + _strlen(args[0]) + 45;
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
	_strcat(error, ": Unable to add/remove from environment\n");

	free(histStr);
	return (error);
}

/**
 * syntax_error - Creates an error message for syntax errors
 * @args: An array of arguments passed to the command line
 *
 * Return: On SUCCESS, returns (error) ie the error string
 *	   On FAILURE, returns (NULL)
 */
char *syntax_error(char **args)
{
	int len;
	char *error, *histStr;

	histStr = _itoa(cmd_hist);
	if (!histStr)
		return (NULL);

	len = _strlen(name) + _strlen(histStr) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(histStr);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, histStr);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(histStr);
	return (error);
}

/**
 * exit_error - Creates an error message for shellexit errors
 * @args: An array of arguments passed to the command line
 *
 * Return: On SUCCESS, returns (error) ie the error string
 *	   On FAILURE, returns (NULL)
 */
char *exit_error(char **args)
{
	int len;
	char *error, *histStr;

	histStr = _itoa(cmd_hist);
	if (!histStr)
		return (NULL);

	len = _strlen(name) + _strlen(histStr) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(histStr);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, histStr);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(histStr);
	return (error);
}
