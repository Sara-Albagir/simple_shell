#ifndef _ALBADY_SHELL_H_
#define _ALBADY_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define ALBADY_READ_BUF_SIZE 1024
#define ALBADY_WRITE_BUF_SIZE 1024
#define ALBADY_BUF_FLUSH -1

/* for command chaining */
#define ALBADY_CMD_NORM    0
#define ALBADY_CMD_OR      1
#define ALBADY_CMD_AND     2
#define ALBADY_CMD_CHAIN   3

/* for convert_number() */
#define ALBADY_CONVERT_LOWERCASE   1
#define ALBADY_CONVERT_UNSIGNED    2

/* 1 if using system getline() */
#define ALBADY_USE_GETLINE 0
#define ALBADY_USE_STRTOK  0

#define ALBADY_HIST_FILE   ".albady_simple_shell_history"
#define ALBADY_HIST_MAX    4096

extern char **albady_environ;

/**
 * struct albady_liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct albady_liststr
{
	int num;
	char *str;
	struct albady_liststr *next;
} albady_list_t;

/**
 *struct albady_passinfo - contains pseudo-arguments to pass into a function,
 *      allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: albady modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct albady_passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	albady_list_t *env;
	albady_list_t *history;
	albady_list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* ptr to cmd ; chain buffer, for mem mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} albady_info_t;

#define ALBADY_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
 *struct albady_builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct albady_builtin
{
	char *type;
	int (*func)(albady_info_t *);
} albady_builtin_table;

/* albady_atoi.c */
int albady_hsh(albady_info_t *, char **);
int albady_find_builtin(albady_info_t *);
void albady_find_cmd(albady_info_t *);
void albady_fork_cmd(albady_info_t *);

/* albady_parser.c */
int albady_is_cmd(albady_info_t *, char *);
char *albady_dup_chars(char *, int, int);
char *albady_find_path(albady_info_t *, char *, char *);

/* albady_loophsh.c */
int albady_loophsh(char **);

/* albady_errors.c */
void albady_eputs(char *);
int albady_eputchar(char);
int albady_putfd(char c, int fd);
int albady_putsfd(char *str, int fd);

/* albady_string.c */
int albady_strlen(char *);
int albady_strcmp(char *, char *);
char *albady_starts_with(const char *, const char *);
char *albady_strcat(char *, char *);

/* albady_string1.c */
char *albady_strcpy(char *, char *);
char *albady_strdup(const char *);
void albady_puts(char *);
int albady_putchar(char);

/* albady_exits.c */
char *albady_strncpy(char *, char *, int);
char *albady_strncat(char *, char *, int);
char *albady_strchr(char *, char);

/* albady_tokenizer.c */
char **albady_strtow(char *, char *);
char **albady_strtow2(char *, char);

/* albady_realloc.c */
char *albady_memset(char *, char, unsigned int);
void albady_ffree(char **);
void *albady_realloc(void *, unsigned int, unsigned int);

/* albady_memory.c */
int albady_bfree(void **);

/* albady_atoi.c */
int albady_interactive(albady_info_t *);
int albady_is_delim(char, char *);
int albady_isalpha(int);
int albady_atoi(char *);

/* albady_errors1.c */
int albady_erratoi(char *);
void albady_print_error(albady_info_t *, char *);
int albady_print_d(int, int);
char *albady_convert_number(long int, int, int);
void albady_remove_comments(char *);

/* albady_builtin.c */
int albady_myexit(albady_info_t *);
int albady_mycd(albady_info_t *);
int albady_myhelp(albady_info_t *);

/* albady_builtin1.c */
int albady_myhistory(albady_info_t *);
int albady_myalias(albady_info_t *);

/* albady_getline.c */
ssize_t albady_get_input(albady_info_t *);
int albady_getline(albady_info_t *, char **, size_t *);
void albady_sigintHandler(int);

/* albady_getinfo.c */
void albady_clear_info(albady_info_t *);
void albady_set_info(albady_info_t *, char **);
void albady_free_info(albady_info_t *, int);

/* albady_environ.c */
char *albady_getenv(albady_info_t *, const char *);
int albady_myenv(albady_info_t *);
int albady_mysetenv(albady_info_t *);
int albady_myunsetenv(albady_info_t *);
int albady_populate_env_list(albady_info_t *);

/* albady_getenv.c */
char **albady_get_environ(albady_info_t *);
int albady_unsetenv(albady_info_t *, char *);
int albady_setenv(albady_info_t *, char *, char *);

/* albady_history.c */
char *albady_get_history_file(albady_info_t *info);
int albady_write_history(albady_info_t *info);
int albady_read_history(albady_info_t *info);
int albady_build_history_list(albady_info_t *info, char *buf, int linecount);
int albady_renumber_history(albady_info_t *info);

/* albady_lists.c */
albady_list_t *albady_add_node(albady_list_t **, const char *, int);
albady_list_t *albady_add_node_end(albady_list_t **, const char *, int);
size_t albady_print_list_str(const albady_list_t *);
int albady_delete_node_at_index(albady_list_t **, unsigned int);
void albady_free_list(albady_list_t **);

/* albady_lists1.c */
size_t albady_list_len(const albady_list_t *);
char **albady_list_to_strings(albady_list_t *);
size_t albady_print_list(const albady_list_t *);
albady_list_t *albady_node_starts_with(albady_list_t *, char *, char);
ssize_t albady_get_node_index(albady_list_t *, albady_list_t *);

/* albady_vars.c */
int albady_is_chain(albady_info_t *, char *, size_t *);
void albady_check_chain(albady_info_t *, char *, size_t *, size_t, size_t);
int albady_replace_alias(albady_info_t *);
int albady_replace_vars(albady_info_t *);
int albady_replace_string(char **, char *);

#endif
