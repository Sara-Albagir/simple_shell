#ifndef SHELL_H_INCLUDED
#define SHELL_H_INCLUDED

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

#define DLM " \t\n"

extern char **environ;

char **splitter(char *length);
char *_lnreader(void);

char *dup_strg(const char *srg);
int cmp_strg(char *a1, char *a2);
int len_strg(char *a);

char *cat_strg(char *fbuf, char *sbuf);
char *cpy_strg(char *fbuf, char *sbuf);

void _stringfreeing(char **ary);
int exe(char **cmd, char **vecar);

#endif
