#include "shell.h"

char *find_path(char *cmd);
char *fill_path(char *path);
list_node *get_path(char *path);
/**
 * find_path - Locates a command in the PATH
 * @cmd: The command to locate
 *
 * Return: On SUCCESS, returns the full path of the command and NULL on FAILURE
 */
char *find_path(char *cmd)
{
	struct stat st;
	char **path, *tmp;
	list_node *dirs, *head;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);
	dirs = get_path(*path + 5);
	head = dirs;
	while (dirs)
	{
		tmp = malloc(_strlen(dirs->dir) + _strlen(cmd) + 2);
		if (!tmp)
			return (NULL);
		_strcpy(tmp, dirs->dir);
		_strcat(tmp, "/");
		_strcat(tmp, cmd);
		if (stat(tmp, &st) == 0)
		{
			free_list(head);
			return (tmp);
		}
		dirs = dirs->next;
		free(tmp);
	}
	free_list(head);

	return (NULL);
}

/**
 * fill_path - Copies and replaces leading colons (:) with current directory
 * @path: Colon-separated list of directories
 *
 * Return: On SUCCESS, returns (pathdup) ie the copy of path
 */
char *fill_path(char *path)
{
	char *pathdup, *pwd;
	int i, len = 0;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	pathdup = malloc(sizeof(char) * (len + 1));
	if (!pathdup)
		return (NULL);
	pathdup[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(pathdup, pwd);
				_strcat(pathdup, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(pathdup, ":");
				_strcat(pathdup, pwd);
			}
			else
				_strcat(pathdup, ":");
		}
		else
			_strncat(pathdup, &path[i], 1);
	}
	return (pathdup);
}

/**
 * get_path - Splits a colon-separated list of directories
 * @path: The colon-separated list of directories
 *
 * Return: Returns a pointer to the linked list
 */
list_node *get_path(char *path)
{
	char **dirs, *pathdup;
	int i;
	list_node *head = NULL;

	pathdup = fill_path(path);
	if (!pathdup)
		return (NULL);
	dirs = _strtok(pathdup, ":");
	free(pathdup);
	if (!dirs)
		return (NULL);

	for (i = 0; dirs[i]; i++)
	{
		if (append_node(&head, dirs[i]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}
	free(dirs);

	return (head);
}
