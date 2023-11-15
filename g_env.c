#include "albady_shell.h"
/**
 * envir_getter - Returns string array copy of our envir.
 * @ads: The Structure contains potential args. To maintain
 * const function prototype.
 * Return: 0 Always
 */
char **envir_getter(ads_t *ads)
{
	if (!ads->envir || ads->env_changed)
	{
		ads->envir = list_to_strings(ads->env);
		ads->env_changed = 0;
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
	list_t *section = ads->env;
	size_t i = 0;
	char *p;

	if (!section || !var)
		return (0);

	while (section)
	{
		p = starts_with(section->str, var);
		if (p && *p == '=')
		{
			ads->env_changed = delete_section_at_index(&(ads->env), i);
			i = 0;
			section = ads->env;
			continue;
		}
		section = section->next;
		i++;
	}
	return (ads->env_changed);
}

/**
 * set_env - Initialize a new envir var
 * or modify an existing one
 * @ads: Struct containing potential args. To maintain
 * const function prototype
 * @var: String env variable property.
 * @value: String env var value.
 *  Return: 0 Always
 */
int set_env(ads_t *ads, char *var, char *value)
{
	char *buf = NULL;
	list_t *section;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	str_cpy(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	section = ads->env;
	while (section)
	{
		p = starts_with(section->str, var);
		if (p && *p == '=')
		{
			free(section->str);
			section->str = buf;
			ads->env_changed = 1;
			return (0);
		}
		section = section->next;
	}
	add_section_end(&(ads->env), buf, 0);
	free(buf);
	ads->env_changed = 1;
	return (0);
}
