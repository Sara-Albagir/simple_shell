#include "main.h"

/**
 * _my_history - Displays history list, a command by line, preceded
 * with line nums, starting at 0.
 * @ads: Structure contains potential arguments. Used to maintain
 * const function prototype.
 * Return: 0 Always
 */
int _my_history(ads_t *ads)
{
	pnt_list(ads->history);
	return (0);
}

/**
 * _my_alias - sets alias
 * @ads: parameter struct
 * @str: string alias
 *
 * Return: 0 Always on success, 1 on error
 */
int _my_alias(ads_t *ads, char *str)
{
	char *p, a;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	a = *p;
	*p = 0;
	ret = delete_section_at_index(&(ads->alias),
		get_section_index(ads->alias, section_starts_with(ads->alias, str, -1)));
	*p = a;
	return (ret);
}

/**
 * _my_set_alias - sets the alias to string
 * @ads: The parameter struct
 * @str: string alias
 *
 * Return: 0 Always on success, 1 on error
 */
int _my_set_alias(ads_t *ads, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_my_alias(ads, str));

	_my_alias(ads, str);
	return (add_section_end(&(ads->alias), str, 0) == NULL);
}

/**
 * _my_print_alias - display an alias string
 * @section: alias node
 *
 * Return: 0 Always on success, 1 on error
 */
int _my_print_alias(list_t *section)
{
	char *p = NULL, *a = NULL;

	if (section)
	{
		p = _strchr(section->str, '=');
		for (a = section->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias createdin (man alias)
 * @ads: Structure contains potential args. To maintain
 * const function prototype.
 * Return: 0 Always
 */
int _myalias(ads_t *ads)
{
	int i = 0;
	char *p = NULL;
	lists *section = NULL;

	if (ads->argc == 1)
	{
		section = ads->alias;
		while (section)
		{
			_my_print_palias(section);
			section = section->next;
		}
		return (0);
	}
	for (i = 1; ads->argv[i]; i++)
	{
		p = _strchr(ads->argv[i], '=');
		if (p)
			_my_set_alias(ads, ads->argv[i]);
		else
			_my_print_alias(section_starts_with(ads->alias, ads->argv[i], '='));
	}

	return (0);
}
