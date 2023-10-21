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

#include "main.h"

#endif
