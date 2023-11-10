#include "main.h"

/**
 * my_env - Display current enviroment
 * @ads: Structure of potential args. Used to maintain
 * const function prototype.
 * Return: 0 Always
 */
int my_env(ads_t *ads)
{
	print_list_str(ads->env);
	return (0);
}

/**
 * get_env - gets value of an envir var
 * @ads: Structure contains potential args. To maintain
 * @label: The env variable name
 *
 * Return: value
 */
char *get_env(ads_t *ads, const char *label)
{
	list_t *section = ads->env;
	char *p;

	while (section)
	{
		p = starts_with(section->str, label);
		if (p && *p)
			return (p);
		section = section->next;
	}
	return (NULL);
}

/**
 * my_set_env - Initialize a new envir var,
 * or modify existing one
 * @ads: Struct containing potential args. maintains
 * const function prototype.
 * Return: 0 Always
 */
int my_set_env(ads_t *ads)
{
	if (ads->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(ads, ads->argv[1], ads->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unset_env - Remove envir var
 * @ads: Struct containing potential args. to maintain
 * const function prototype.
 * Return: 0 Always
 */
int my_unset_env(ads_t *ads)
{
	int i;

	if (ads->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i < ads->argc; i++)
		_unsetenv(ads, ads->argv[i]);

	return (0);
}

/**
 * populate_envlist - Program populates env linked list
 * @ads: The Struct containing potential args. Used to maintain
 * const function prototype.
 * Return: 0 Always
 */
int populate_envlist(ads_t *ads)
{
	list_t *section = NULL;
	size_t i;

	for (i = 0; envi[i]; i++)
		add_section_end(&section, envi[i], 0);
	ads->env = section;
	return (0);
}
