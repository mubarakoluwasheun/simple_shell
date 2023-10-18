#include "shell.h"

char **_envcopy(void);
void free_environ(void);
char **_getenv(const char *var);

/**
 * _envcopy - Creates a copy of the environment
 *
 * Return: On SUCCESS, returns (new_env) ie a 2D pointer to the new environ
 *	   On FAILURE, returns (NULL) to indicate an error occurred
 */
char **_envcopy(void)
{
	int i;
	size_t size;
	char **new_env;

	size = 0;
	while (environ[size])
		size++;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		new_env[i] = malloc(_strlen(environ[i]) + 1);

		if (!new_env[i])
		{
			for (i--; i >= 0; i--)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		_strcpy(new_env[i], environ[i]);
	}
	new_env[i] = NULL;

	return (new_env);
}

/**
 * free_env - Frees the environment copy
 *
 * Return: Returns nothing (void)
 */
void free_environ(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * _getenv - Gets an environment variable from the PATH
 * @var: The name of the environment variable to get
 *
 * Return: On SUCCESS, returns (value) ie a pointer to the environ variable
 *         On FAILURE, returns (NULL) to indicate the variable does not exist
 */
char **_getenv(const char *var)
{
	int i, len;

	len = _strlen(var);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(var, environ[i], len) == 0)
			return (&environ[i]);
	}
	return (NULL);
}
