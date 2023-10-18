#include "shell.h"

int digitlen(int n);
char *_itoa(int n);
int _error(char **args, int err);

/**
 * digitlen - Counts the length of a digit
 * @n: The number to count
 *
 * Return: Returns (len) ie the digit length
 */
int digitlen(int n)
{
	unsigned int n1;
	int len = 1;

	if (n < 0)
	{
		len++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		len++;
		n1 /= 10;
	}
	return (len);
}

/**
 * _itoa - Converts an integer to a string
 * @n: The integer to convert
 *
 * Return: On SUCCESS, returns (str) ie the converted string
 *	   On FAILURE, returns (NULL)
 */
char *_itoa(int n)
{
	int len = digitlen(n);
	unsigned int n1;
	char *str;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		n1 = n * -1;
		str[0] = '-';
	}
	else
	{
		n1 = n;
	}

	len--;
	do {
		str[len] = (n1 % 10) + '0';
		n1 /= 10;
		len--;
	} while (n1 > 0);

	return (str);
}

/**
 * _error - Writes a custom error message to standard error (stderr)
 * @args: An array of arguments
 * @err: The error value
 *
 * Return: Returns (err) ie the error value
 */
int _error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = env_error(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = exit_error(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = syntax_error(args);
		else
			error = cd_error(args);
		break;
	case 126:
		error = error126(args);
		break;
	case 127:
		error = error127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);

	return (err);
}
