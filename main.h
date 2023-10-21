#ifndef MAIN_H
#define MAIN_H

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


#endif /* MAIN_H */
