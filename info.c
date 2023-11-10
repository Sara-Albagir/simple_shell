#include "main.h"

/**
 * clear_ads - initializes ads_t struct.
 * @ads: The struct address.
 */
void clear_ads(ads_t *ads)
{
	ads->arg = NULL;
	ads->argv = NULL;
	ads->path = NULL;
	ads->argc = 0;
}

/**
 * set_ads - initializes ads_t struct.
 * @ads: The struct address.
 * @av: The argument vectors.
 */
void set_ads(ads_t *ads, char **av)
{
	int i = 0;

	ads->fname = av[0];
	if (ads->arg)
	{
		ads->argv = strtow(ads->arg, " \t");
		if (!ads->argv)
		{

			ads->arg = malloc(sizeof(char *) * 2);
			if (ads->argv)
			{
				ads->argv[0] = _strdup(ads->arg);
				ads->argv[1] = NULL;
			}
		}
		for (i = 0; ads->argv && ads->argv[i]; i++)
			;
		ads->argc = i;

		replace_alias(ads);
		replace_vars(ads);
	}
}

/**
 * free_ads - frees ads_t struct fields.
 * @ads: The struct address.
 * @all: is true if freeing fields.
 */
void free_ads(ads_t *ads, int all)
{
	ffree(ads->argv);
	ads->argv = NULL;
	ads->path = NULL;
	if (all)
	{
		if (!ads->cmd_buf)
			free(ads->arg);
		if (ads->env)
			free_list(&(ads->env));
		if (ads->history)
			free_list(&(ads->history));
		if (ads->alias)
			free_list(&(ads->alias));
		ffree(ads->envir);
			ads->envir = NULL;
		bfree((void **)ads->cmd_buf);
		if (ads->readfd > 2)
			close(ads->readfd);
		_putchar(BUF_FLUSH);
	}
}
