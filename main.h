#ifndef _MAIN_H_
#define _MAIN_H_

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

/* for read/write bufers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USEget_line 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **envir;

char *starts_with(const char *str, const char *prefix);

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next section
 */
typedef struct liststr
{
	int num;
	char *str;
	int ind_num;
	struct liststr *next;
} list_t;

/**
 * struct passads- It contains pseudo-args to pass into a function,
 * which allows uniform prototype for function pointer struct.
 * @arg: String generated from getline containing args.
 * @argc: Array of strings generated from args.
 * @filepath: String filepath for the current command.
 * @argv: Argument count.
 * @count_lin: Error count.
 * @err_num: Error code for exit()s.
 * @count_lin_flag: This line of input, if on count.
 * @fname: The filename of the program.
 * @env: The linked list, local copy of envir.
 * @envir: The custom modified copy of envir from LL env.
 * @history: The section of the history.
 * @alias: Alias section.
 * @_changedenv: On, if envir was changed.
 * @status: Return status of the last executed commd.
 * @cmd_buf: Address of pointer to cmd_buf, on if chaining.
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd from which to, read line input.
 * @histcount: History line num count
 */

typedef struct passads
{
	char *arg;
	int argc;
	char **argv;
	char *filepath;
	unsigned int count_lin;
	char *fname;
	int err_num;
	int count_lin_flag;
	list_t *env;
	list_t *alias;
	list_t *history;
	char **envir;
	int _changedenv;
	int status;

	char **cmd_buf; /* The pointer to cmd ; chain bufer, for memo mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int histcount;
	int readfd;
} ads_t;

#define ADS_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct createdin - contains a createdin string and related function
 *@type: command flag createdin
 *@func: function
 */
typedef struct createdin
{
	char *type;
	int (*func)(ads_t *);
} createdin_table;


/* _shloop.c */
int hsh(ads_t *, char **);
int find_createdin(ads_t *);
void _cmdfounder(ads_t *);
void _cmdfork(ads_t *);

/* _analyzer.c */
int _iscmd(ads_t *, char *);
char *_chardup(char *, int, int);
char *find_filepath(ads_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* _errors.c */
void my_puts(char *);
int _aputchar(char);
int _putfd(char c, int fd);
int putsfd(char *str, int fd);

/* _funrow_string.c */
int strg_len(char *);
int _cmpstr(char *, char *);
char *begins_with(const char *, const char *);
char *_strconcat(char *, char *, int);

/* _funrow_string1.c */
char *_cpy_strg(char *, char *);
char *dup_strg(const char *);
void inp_strg(char *);
int _printchar(char);

/* _exits.c */
char *str_cpy(char *, char *, int);
char *_strconcat(char *, char *, int);
char *_chrstr(char *, char);

/* _funsplitter.c */
char **spltstr(char *, char *);
char **spltstr2(char *, char);

/* alloc_memo.c */
char *bits_memo(char *, char, unsigned int);
void strg_free(char **);
void *alloc_memo(void *, unsigned int, unsigned int);

/* _memo.c */
int bfree(void **);

/* str_to_int.c */
int _inter_active(ads_t *);
int delim(char, char *);
int alpha(int);
int str_to_int(char *);

/* _errors1.c */
int _toi(char *);
void _error(ads_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* _createdin.c */
int s_exit(ads_t *);
int _cds(ads_t *);
int myhelp(ads_t *);

/* _createdin2.c */
int myhistory(ads_t *);
int _aliass(ads_t *);

/* _get_line.c */
ssize_t _getinput(ads_t *);
int get_line(ads_t *, char **, size_t *);
void sigintHandler(int);

/* _getads.c */
void clear_ads(ads_t *);
void set_ads(ads_t *, char **);
void free_ads(ads_t *, int);

/* _envir.c */
char *gtenv(ads_t *, const char *);
int _myenv(ads_t *);
int _mysetenv(ads_t *);
int _myunsetenv(ads_t *);
int populate_env_list(ads_t *);

/* gtenv.c */
char **envir_getter(ads_t *);
int unset_env(ads_t *, char *);
int _envset(ads_t *, char *, char *);

/* _history.c */
char *history_file(ads_t *ads);
int write_history_file(ads_t *ads);
int _readhistory(ads_t *ads);
int history_list(ads_t *ads, char *buf, int linecount);
int re_num_history(ads_t *ads);

/* _shell_lists */
list_t *add_section(list_t **, const char *, int);
list_t *_add_section_end(list_t **, const char *, int);
size_t _strg_listprint(const list_t *);
int _section_delete(list_t **, unsigned int);
void _listfree(list_t **);

/* _lists1.c */
size_t list_len(const list_t *);
char **listso_strings(list_t *);
size_t pnt_list(const list_t *);
list_t *section_begins_with(list_t *, char *, char);
ssize_t get_section_index(list_t *, list_t *);

/* _funvars.c */
int _ischain(ads_t *, char *, size_t *);
void check_chain(ads_t *, char *, size_t *, size_t, size_t);
int _alias_rep(ads_t *);
int replace_vars(ads_t *);
int replace_string(char **, char *);

#endif
