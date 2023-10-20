#include "shell.h"

int _toklen(char *str, char *delim);
int _tokcount(char *str, char *delim);
char **_strtok(char *str, char *delim);

/**
 * _toklen - Finds the delimiter marking the end of a string
 * @str: The string to obtain the len
 * @delim: The string containing the delimiters
 *
 * Return: Returns length of the token
 */
int _toklen(char *str, char *delim)
{
	int count = 0, len = 0;

	while (*(str + count) && *(str + count) != *delim)
	{
		len++;
		count++;
	}
	return (len);
}

/**
 * _tokcount - Counts the number of delimited words in a string
 * @str: The string to count
 * @delim: The delimiter
 *
 * Return: Returns (token) ie the number of words in a line of strings
 */
int _tokcount(char *str, char *delim)
{
	int count, tokens = 0, len = 0;

	for (count = 0; *(str + count); count++)
		len++;

	for (count = 0; count < len; count++)
	{
		if (*(str + count) != *delim)
		{
			tokens++;
			count += _toklen(str + count, delim);
		}
	}
	return (tokens);
}

/**
 * _strtok - Tokenizes a string
 * @str: The string to be tokenized
 * @delim: The string containing the delimiters
 *
 * Return: A pointer to an array of the tokenized words
 * or NULL if none
 */
char **_strtok(char *str, char *delim)
{
	int i = 0, token, j, next, k;
	char **ptr;

	token = _tokcount(str, delim);
	if (token == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (token + 2));
	if (!ptr)
		return (NULL);

	for (j = 0; j < token; j++)
	{
		while (str[i] == *delim)
			i++;

		next = _toklen(str + i, delim);

		ptr[j] = malloc(sizeof(char) * (next + 1));
		if (!ptr[j])
		{
			for (i -= 1; i >= 0; i--)
				free(ptr[i]);
			free(ptr);
			return (NULL);
		}
		for (k = 0; k < next; k++)
		{
			ptr[j][k] = str[i];
			i++;
		}
		ptr[j][k] = '\0';
	}
	ptr[j] = NULL;
	ptr[j + 1] = NULL;

	return (ptr);
}
