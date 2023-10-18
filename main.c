#include "shell.h"

void check_sig(int sig);
int execute(char **args, char **arg0);
int main(int ac, char **av);
/**
 * check_sig - Verifies if Ctrl+C key combination is pressed
 *	       and prints a new prompt upon a signal
 * @sig: The signal
 */
void check_sig(int sig)
{
	char *prompt = "\n>$ ";

	(void)sig;
	signal(SIGINT, check_sig);
	write(STDIN_FILENO, prompt, 4);
}

/**
 * execute - Executes a command in a child process
 * @args: An array of arguments
 * @arg0: A 2D pointer to the start of args
 *
 * Return: On SUCCESS, returns the exit value of the last executed command
 *	   If an error occurs returns the associated error code
 */
int execute(char **args, char **arg0)
{
	pid_t pid;
	int status, flag = 0, ret = 0;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = find_path(cmd);
	}
	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (_error(args, 126));
		else
			ret = (_error(args, 127));
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				ret = (_error(args, 126));
			free_environ();
			free_stdin_cmd(args, arg0);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmd);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter
 * @ac: The number of arguments from the command line
 * @av: An array of argument strings from the command line
 *
 * Return: On SUCCESS, returns (ret) ie the value of the last executed command
 */
int main(int ac, char **av)
{
	char *prompt = ">$ ", *newline = "\n";
	int ret_val = 0, exec_retn;
	int *ret = &exec_retn;

	name = av[0];
	cmd_hist = 1;
	signal(SIGINT, check_sig);

	*ret = 0;
	environ = _envcopy();
	if (!environ)
		exit(-100);

	if (ac != 1)
	{
		ret_val = execute_commands(av[1], ret);
		free_environ();
		return (*ret);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (ret_val != _EOF && ret_val != EXIT)
			ret_val = handle_stdin_cmd(ret);
		free_environ();
		return (*ret);
	}
	while (1)
	{
		write(STDOUT_FILENO, prompt, 3);
		ret_val = handle_stdin_cmd(ret);
		if (ret_val == _EOF || ret_val == EXIT)
		{
			if (ret_val == _EOF)
				write(STDOUT_FILENO, newline, 1);
			free_environ();
			exit(*ret);
		}
	}
	free_environ();
	return (*ret);
}
