#include "albady_shell.h"

/**
 * albady_myhistory - track the history of cmd.
 * @info: sustain a prototype.
 * Return: 0.
 */
int albady_myhistory(albady_info_t *info)
{
	albady_print_list_str(info->history);
	return (0);
}

/**
 * albady_unset_alias - alias modifier.
 * @info: parameter struct.
 * @str: the string alias.
 * Return: 0 or 1.
 */
int albady_unset_alias(albady_info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = albady_strchr(str, '=');
	if (!p)
	return (1);
	c = *p;
	*p = 0;
	ret = albady_delete_node_at_index(&(info->alias),
			albady_get_node_index(info->alias,
				albady_node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * albady_set_alias - alias modifier.
 * @info: parameter struct.
 * @str: the string alias.
 * Return: 0 or 1.
 */
int albady_set_alias(albady_info_t *info, char *str)
{
	char *p;

	p = albady_strchr(str, '=');
	if (!p)
	return (1);
	if (!*++p)
	return (albady_unset_alias(info, str));

	albady_unset_alias(info, str);
	return (albady_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * albady_print_alias - a string printer to an alias.
 * @node: node in question.
 * Return: 0 or 1.
 */
int albady_print_alias(albady_list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
	p = albady_strchr(node->str, '=');
	for (a = node->str; a <= p; a++)
	albady_putchar(*a);
	albady_putchar('\'');
	albady_puts(p + 1);
	albady_puts("'\n");
	return (0);
	}
	return (1);
}

/**
 * albady_myalias - similerise alias string.
 * @info: parameter struct.
 * Return: 0.
 */
int albady_myalias(albady_info_t *info)
{
	int i = 0;
	char *p = NULL;
	albady_list_t *node = NULL;

	if (info->argc == 1)
	{
	node = info->alias;
	while (node)
	{
		albady_print_alias(node);
		node = node->next;
	}
	return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
	p = albady_strchr(info->argv[i], '=');
	if (p)
		albady_set_alias(info, info->argv[i]);
	else
		albady_print_alias(albady_node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
