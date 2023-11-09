#include "main.h"
/**
 * _getenvir - Returns string array copy of our envir.
 * @ads: The Structure contains potential args. To maintain
 * const function prototype.
 * Return: 0 Always
 */
char **_getenvir(ads_t *ads)
{
	if (!ads->envir || ads->_changedenv)
	{
		ads->envir = list_to_strings(ads->env);
		ads->_changedenv = 0;
	}

	return (ads->envir);
}

/**
 * unset_env - removes an environment var.
 * @ads: Struct containing potential args. Used to maintain
 * const funct prototype.
 * Return: 1 on delete, otherwise 0
 * @var: string env var property
 */
int unset_env(ads_t *ads, char *var)
{
	_list_t *section = ads->env;
	size_t i = 0;
	char *p;

	if (!section || !var)
		return (0);

	while (section)
	{
		p = begins_with(section->str, var);
		if (p && *p == '=')
		{
			ads->_changedenv = delete_section_at_index(&(ads->env), i);
			i = 0;
			section = ads->env;
			continue;
		}
		section = section->next;
		i++;
	}
	return (ads->_changedenv);
}

/**
 * _set_env - Initialize a new envir var
 * or modify an existing one
 * @ads: Struct containing potential args. To maintain
 * const function prototype
 * @var: String env variable property.
 * @val: String env var value.
 *  Return: 0 Always
 */
int _set_env(ads_t *ads, char *var, char *val)
{
	char *buff = NULL;
	_list_t *section;
	char *p;

	if (!var || !val)
		return (0);

	buff = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buff)
		return (1);
	str_cpy(buff, var);
	_strconcat(buff, "=");
	_strconcat(buff, val);
	section = ads->env;
	while (section)
	{
		p = begins_with(section->str, var);
		if (p && *p == '=')
		{
			free(section->str);
			section->str = buff;
			ads->_changedenv = 1;
			return (0);
		}
		section = section->next;
	}
	add_node_end(&(ads->env), buff, 0);
	free(buff);
	ads->_changedenv = 1;
	return (0);
}
