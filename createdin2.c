#include "main.h"
/**
 * myhistory - Displays history list, a command by line, preceded
 * with line nums, starting at 0.
 * @ads: Structure contains potential arguments. Used to maintain
 * const function prototype.
 * Return: 0 Always
 */
int myhistory(ads_t *ads)
{
	pnt_list(ads->history);
	return (0);
}

/**
 * _alias - sets alias
 * @ads: parameter struct
 * @cha: string alias
 *
 * Return: 0 Always on success, 1 on error
 */
int _alias(ads_t *ads, char *cha)
{
	char *p, a;
	int ret;

	p = _chrstr(cha, '=');
	if (!p)
		return (1);
	a = *p;
	*p = 0;
	ret = delete_node_at_index(&(ads->alias),
		get_node_index(ads->alias, node_starts_with(ads->alias, str, -1)));
	*p = a;
	return (ret);
}

/**
 * _salias - sets the alias to string
 * @ads: The parameter struct
 * @cha: string alias
 *
 * Return: 0 Always on success, 1 on error
 */
int _salias(ads_t *ads, char *cha)
{
	char *p;

	p = _chrstr(cha, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_alias(ads, cha));

	_alias(ads, cha);
	return (add_node_end(&(ads->alias), str, 0) == NULL);
}

/**
 * _palias - displays history of list, a command by line,
 * prints alias string
 * @section: alias node
 *
 * Return: 0 Always on success, 1 on error
 */
int _palias(list_t *section)
{
	char *p = NULL, *a = NULL;

	if (section)
	{
		p = _chrstr(section->cha, '=');
		for (a = section->cha; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _aliass - mimics the alias createdin (man alias)
 * @ads: Structure contains potential args. To maintain
 * const function prototype.
 * Return: 0 Always
 */
int _aliass(ads_t *ads)
{
	int i = 0;
	char *p = NULL;
	lists *section = NULL;

	if (ads->argc == 1)
	{
		section = ads->alias;
		while (section)
		{
			_palias(section);
			section = section->next;
		}
		return (0);
	}
	for (i = 1; ads->argv[i]; i++)
	{
		p = _chrstr(ads->argv[i], '=');
		if (p)
			_salias(ads, ads->argv[i]);
		else
			_palias(section_starts_with(ads->alias, ads->argv[i], '='));
	}

	return (0);
}
