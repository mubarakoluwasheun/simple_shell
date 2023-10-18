#include "shell.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void _setlineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/**
 * _realloc - Reallocates memory for a block
 * @ptr: A pointer to the previous memory allocation
 * @old_size: The size in bytes allocated to ptr
 * @new_size: The size in bytes allocated to the new memory block
 *
 * Return: On SUCCESS, returns (newMem) ie the pointer to the new memory block
 *	   On FAILURE, returns (ptr) if new_size == old_size and (NULL)
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *ptrdup, *buffer;
	unsigned int i;
	void *newMem;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		newMem = malloc(new_size);
		if (newMem == NULL)
			return (NULL);

		return (newMem);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	ptrdup = ptr;
	newMem = malloc(sizeof(*ptrdup) * new_size);
	if (newMem == NULL)
	{
		free(ptr);
		return (NULL);
	}
	buffer = newMem;
	for (i = 0; i < old_size && i < new_size; i++)
		buffer[i] = *ptrdup++;
	free(ptr);

	return (newMem);
}

/**
 * _setlineptr - Reassigns the lineptr for _getline function
 * @lineptr: A buffer to store an input string
 * @n: The size of lineptr
 * @buffer: The string to assign to lineptr
 * @b: The buffer size
 */
void _setlineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 128)
			*n = b;
		else
			*n = 128;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 128)
			*n = b;
		else
			*n = 128;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Reads input from a stream
 * @lineptr: A buffer to store the input
 * @n: The size of lineptr
 * @stream: The stream to read from
 *
 * Return: On SUCCESS, returns (bytes)ie the number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int r;
	char c = 'c', *buffer;
	ssize_t bytes;
	static ssize_t input;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 128);
	if (!buffer)
		return (-1);
	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 128)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';
	_setlineptr(lineptr, n, buffer, input);
	bytes = input;
	if (r != 0)
		input = 0;
	return (bytes);
}
