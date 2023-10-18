#include "shell.h"

int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t num);

/**
 * _strlen - Returns the length of a string
 * @str: A pointer to the characters string
 *
 * Return: The length of the character string.
 */
int _strlen(const char *str)
{
	int len = 0;

	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

/**
 * _strcpy - Copies a string from src to desc buffer
 * @dest: The destination of copied string
 * @src: The source string
 *
 * Return: Returns destination string
 */
char *_strcpy(char *dest, const char *src)
{
	size_t p;

	for (p = 0; src[p] != '\0'; p++)
	{
		dest[p] = src[p];
	}
	dest[p] = '\0';
	return (dest);
}

/**
 * _strcat - Concatenates two strings
 * @dest: The destination string
 * @src: The source string
 *
 * Return: Returns destination string
 */
char *_strcat(char *dest, const char *src)
{
	int p;
	int dest_len = _strlen(dest);

	for (p = 0; src[p] != '\0'; p++)
	{
		dest[dest_len + p] = src[p];
	}
	dest[dest_len + p] = '\0';

	return (dest);
}

/**
 * _strncat - Concatenates num bytes of two strings
 * @dest: The destination string
 * @src: The source string
 * @num: number of bytes to copy from src
 *
 * Return: Returns the destination string
 */
char *_strncat(char *dest, const char *src, size_t num)
{
	size_t dest_len = _strlen(dest);
	size_t p;

	for (p = 0; p < num && src[p] != '\0'; p++)
	{
		dest[dest_len + p] = src[p];
	}
	dest[dest_len + p] = '\0';

	return (dest);
}
