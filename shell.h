#ifndef SHELL_H
#define SHELL_H

/*
 * File: shell.h
 * Desc: This file contains prototypes for all the functions & struct
 *	 required for the project - (0x16. C - Simple Shell)
 *	by Idris Mubarak Oluwasheun
 */

/* Macro definition for EXIT & EOF markers */
#define EXIT -3
#define _EOF -1

/* Standard C Library Headers */
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* External Variable Declaration */
extern char **environ;

/* Global program name */
extern char *name;

/* Global command history counter */
extern int cmd_hist;

/**
 * struct list_node - A struct type defining a linked list
 * @dir: The directory path
 * @next: A pointer to the next node
 */
typedef struct list_node
{
	char *dir;
	struct list_node *next;
} list_node;

/**
 * struct builtins - A struct type defining builtin commands
 * @name: The command name
 * @fpt: A function pointer to the builtin command functions
 */
typedef struct builtins
{
	char *name;
	int (*fpt)(char **argv, char **first);
} builtins;

/* Some Of The Function Prototypes required for the execution of some commands  */
void _setlineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *str, char *delim);
char *find_path(char *command);
list_node *get_path(char *path);
int execute(char **args, char **arg0);
void free_list(list_node *head);
void split_line(char **line, ssize_t len);
void handle_comment(char *buf);
int is_whitespace(char c);


/* Prototypes for the environment */
char *environ_value(char *var, int len);
void var_replace(char **args, int *ret);
char *_getpid(void);
int _printenv(char **args, char __attribute__((__unused__)) **arg0);
int _setenv(char **args, char __attribute__((__unused__)) **arg0);
int _unsetenv(char **args, char __attribute__((__unused__)) **arg0);
char **_envcopy(void);
void free_environ(void);
char **_getenv(const char *var);


/* Prototypes for standard inputs commands */
char *get_stdin_cmd(char *line, int *ret);
int call_stdin_cmd(char **args, char **arg0, int *ret);
int run_stdin_cmd(char **args, char **arg0, int *ret);
int handle_stdin_cmd(int *ret);
int check_stdin_cmd(char **args);
void free_stdin_cmd(char **args, char **arg0);

/* Custom Strings Prototypes */
int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t num);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t num);
int _strspn(char *str, char *prfx);
char *_strchr(char *str, char c);

/* Prototypes for builtins */
int (*check_builtins(char *cmd))(char **args, char **arg0);
int _shellexit(char **args, char **arg0);
int _cd(char **args, char __attribute__((__unused__)) **arg0);


/* Error handlers prototypes */
char *cd_error(char **);
char *env_error(char **);
char *syntax_error(char **);
char *exit_error(char **);
char *error126(char **);
char *error127(char **);
int digitlen(int);
int _error(char **args, int err);
char *_itoa(int);

/* Other functions Prototypes */
list_node *append_node(list_node **head, char *path);
void free_list(list_node *head);
ssize_t newLen(char *line);
void logical_ops(char *line, ssize_t *new_len);
int file_error_handler(char *path);
int execute_commands(char *path, int *ret);

#endif
