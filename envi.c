#include "main.h"
/**
 * _envi - Display current enviroment
 * @ads: Structure of potential args. Used to maintain
 * const function prototype.
 * Return: 0 Always
 */
int _envi(ads_t *ads)
{
	print_list_str(ads->env);
	return (0);
}

/**
 * _genvi - gets value of an envir var
 * @ads: Structure contains potential args. To maintain
 * @label: The env variable name
 *
 * Return: value
 */
char *_genvi(ads_t *ads, const char *label)
{
	list_t *section = ads->env;
	char *p;

	while (section)
	{
		p = begins_with(section->cha, label);
		if (p && *p)
			return (p);
		section = section->next;
	}
	return (NULL);
}

/**
 * _mysenv - Initialize a new envir var,
 * or modify existing one
 * @ads: Struct containing potential args. maintains
 * const function prototype.
 * Return: 0 Always
 */
int _mysenv(ads_t *ads)
{
	if (ads->argc != 3)
	{
		_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_envset(ads, ads->argv[1], ads->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsenv - Remove envir var
 * @ads: Struct containing potential args. to maintain
 * const function prototype.
 * Return: 0 Always
 */
int _myunsenv(ads_t *ads)
{
	int i;

	if (ads->argc == 1)
	{
		_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i < ads->argc; i++)
		_unsenv(ads, ads->argv[i]);

	return (0);
}

/**
 * pop_env_list - Program populates env linked list
 * @ads: The Struct containing potential args. Used to maintain
 * const function prototype.
 * Return: 0 Always
 */
int pop_env_list(ads_t *ads)
{
	list_t *section = NULL;
	size_t i;

	for (i = 0; envi[i]; i++)
		add_node_end(&section, envi[i], 0);
	ads->env = section;
	return (0);
}
