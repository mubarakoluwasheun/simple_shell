#include "shell.h"

int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t num);
int _strspn(char *str, char *prfx);
char *_strchr(char *str, char c);

/**
 * _strcmp - Compares two strings lexicographically
 * @str1: The first string to be compared
 * @str2: The second string to be compared
 *
 * Return: Returns (0) if str1 == str2 and
 * (*str1 - *str2) if str1 is greater than str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/**
 * _strncmp - Compare n charcaters of two strings
 * @str1: The first string to be compared
 * @str2: The second string to be compared
 * @num: Number of bytes to compare
 *
 * Return: Returns (0) if str1 = str2
 *         Returns (str1[i] - str2[i]) if str1 is greater than str2
 */
int _strncmp(const char *str1, const char *str2, size_t num)
{
	size_t p;

	for (p = 0; str1[p] && str2[p] && p < num; p++)
	{
		if (str1[p] > str2[p])
			return (str1[p] - str2[p]);
		else if (str1[p] < str2[p])
			return (str1[p] - str2[p]);
	}
	if (p == num)
		return (0);
	else
		return (-10);
}

/**
 * _strspn - Get length of a prefix substring
 *	     that consists only of accept chars
 * @str: The string to be searched
 * @prfx: The prefix to be measured
 *
 * Return: Returns the number of bytes in the string
 */
int _strspn(char *str, char *prfx)
{
	int count, byte = 0;

	while (*str)
	{
		for (count = 0; prfx[count]; count++)
		{
			if (*str == prfx[count])
			{
				byte++;
				break;
			}
		}
		str++;
	}
	return (byte);
}


/**
 * _strchr - finds a character in a string
 * @str: The string to be searched
 * @c: The character to be located
 *
 * Return: A pointer to first occurence of c in str,
 *        or NULL if not found
 */
char *_strchr(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}
