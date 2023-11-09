#include "main.h"
/**
 * clear_ads - initializes ads_t struct.
 * @ads: The struct address.
 */
void clear_ads(ads_t *ads)
{
	ads->arg = NULL;
	ads->argo = NULL;
	ads->path = NULL;
	ads->args = 0;
}

/**
 * _setads - initializes ads_t struct.
 * @ads: The struct address.
 * @avs: The argument vectors.
 */
void _setads(ads_t *ads, char **avs)
{
	int i = 0;

	ads->fname = avs[0];
	if (ads->arg)
	{
		ads->argo = strtow(ads->arg, " \t");
		if (!ads->argo)
		{

			ads->argo = malloc(sizeof(char *) * 2);
			if (ads->argo)
			{
				ads->argo[0] = _strdup(ads->arg);
				ads->argo[1] = NULL;
			}
		}
		for (i = 0; ads->argo && ads->argo[i]; i++)
			;
		ads->args = i;

		replace_alias(ads);
		replace_vars(ads);
	}
}

/**
 * _freeads - frees ads_t struct fields.
 * @ads: The struct address.
 * @all_f: is true if freeing fields.
 */
void _freeads(ads_t *ads, int all_f)
{
	ffree(ads->argo);
	ads->argo = NULL;
	ads->path = NULL;
	if (all_f)
	{
		if (!ads->cmd_buff)
			free(ads->arg);
		if (ads->env)
			free_list(&(ads->env));
		if (ads->history)
			free_list(&(ads->history));
		if (ads->alias)
			free_list(&(ads->alias));
		ffree(ads->envir);
			ads->envir = NULL;
		bfree((void **)ads->cmd_buff);
		if (ads->readfd > 2)
			close(ads->readfd);
		_putchar(BUF_FLUSH);
	}
}
