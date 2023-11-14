#include "albady_shell.h"
/**
 * albady_clear_info - initializes albady_info_t struct
 * @info: struct address
 */
void albady_clear_info(albady_info_t *info)
{
	info->arg = NULL;
	albady_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * albady_set_info - initializes albady_info_t struct
 * @info: struct address
 * @av: argument vector
 */
void albady_set_info(albady_info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
	info->argv = albady_strtow(info->arg, " \t");
	if (!info->argv)
	{
	info->argv = albady_realloc(info->argv,
	sizeof(char *) * 2, sizeof(char *) * 2);
	if (info->argv)
	{
	info->argv[0] = albady_strdup(info->arg);
	info->argv[1] = NULL;
	}
	}
	for (i = 0; info->argv && info->argv[i]; i++)
	;
	info->argc = i;

	albady_replace_alias(info);
	albady_replace_vars(info);
	}
}

/**
 * albady_free_info - frees albady_info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void albady_free_info(albady_info_t *info, int all)
{
	albady_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
	if (!info->cmd_buf)
	albady_ffree((void *)info->arg);
	if (info->env)
	albady_free_list(&(info->env));
	if (info->history)
	albady_free_list(&(info->history));
	if (info->alias)
		albady_free_list(&(info->alias));
	albady_ffree(info->environ);
	info->environ = NULL;
	albady_bfree((void **)info->cmd_buf);
	if (info->readfd > 2)
		close(info->readfd);
	putchar(ALBADY_BUF_FLUSH);
	}
}
