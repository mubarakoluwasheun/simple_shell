#include "shell.h"

void split_line(char **line, ssize_t len);
ssize_t newLen(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * split_line - Splits a line read from standard input
 * @line: A pointer to a line read from standard input
 * @len: The line length
 */
void split_line(char **line, ssize_t len)
{
	size_t i, j;
	ssize_t new_len;
	char *old_line, *new_line, prev, currentchar, nxt;

	new_len = newLen(*line);
	if (new_len == len - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	j = 0;
	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		currentchar = old_line[i];
		nxt = old_line[i + 1];
		if (i != 0)
		{
			prev = old_line[i - 1];
			if (currentchar == ';')
			{
				if (nxt == ';' && prev != ' ' && prev != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				}
				else if (prev == ';' && nxt != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (prev != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (nxt != ' ')
					new_line[j++] = ' ';
				continue;
			}
			else if (currentchar == '&')
			{
				if (nxt == '&' && prev != ' ')
					new_line[j++] = ' ';
				else if (prev == '&' && nxt != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (currentchar == '|')
			{
				if (nxt == '|' && prev != ' ')
					new_line[j++]  = ' ';
				else if (prev == '|' && nxt != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (currentchar == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (nxt != ' ' && nxt != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * newLen - Obtains the new length of a line separated by
 *	    ";", "||", "&&&", or "#"
 * @line: The line to obtain the length
 *
 * Return: Returns the new length of the line
 */
ssize_t newLen(char *line)
{
	size_t i;
	ssize_t new_len = 0;
	char current, next;

	for (i = 0; line[i]; i++)
	{
		current = line[i];
		next = line[i + 1];
		if (current == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[i], &new_len);
		}
		else if (current == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}

/**
 * logical_ops - Checks a line for logical operators "||" or "&&"
 * @line: A pointer to the character to check in the line
 * @new_len: Pointer to new_len in get_new_len function
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
	}
}
