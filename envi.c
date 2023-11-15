#include "albady_shell.h"
/**
 * albady_myenv - working env printer.
 * @info: parameter struct.
 * Return: 0.
 */
int albady_myenv(albady_info_t *info)
{
	albady_print_list_str(info->env);
	return (0);
}

/**
 * albady_getenv - fineds a variable value.
 * @info: parameter struct.
 * @name: env var name
 * Return: var value.
 */
char *albady_getenv(albady_info_t *info, const char *name)
{
	albady_list_t *node = info->env;
	char *p;

	while (node)
	{
	p = albady_starts_with(node->str, name);
	if (p && *p)
	return (p);
	node = node->next;
	}
	return (NULL);
}

/**
 * albady_mysetenv - start a new env.
 * @info: parameter struct.
 * Return: 0.
 */
int albady_mysetenv(albady_info_t *info)
{
	if (info->argc != 3)
	{
	albady_eputs("Incorrect number of arguments\n");
	return (1);
	}
	if (albady_setenv(info, info->argv[1], info->argv[2]))
	return (0);
	return (1);
}

/**
 * albady_myunsetenv - delete the variable.
 * @info: parameter struct.
 * Return: 0.
 */
int albady_myunsetenv(albady_info_t *info)
{
	int i;

	if (info->argc == 1)
	{
	albady_eputs("Too few arguments.\n");
	return (1);
	}
	for (i = 1; i <= info->argc; i++)
	albady_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * albady_populate_env_list - modify linked list.
 * @info: a parameter struct.
 * Return: 0.
 */
int albady_populate_env_list(albady_info_t *info)
{
	albady_list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	albady_add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
