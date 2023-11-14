#include "albady_shell.h"

/**
 * albady_get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
char **albady_get_environ(albady_info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        albady_bfree((void **)&info->environ);
        info->environ = albady_list_to_strings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * albady_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int albady_unsetenv(albady_info_t *info, char *var)
{
    albady_list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = albady_starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = albady_delete_node_at_index(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return (info->env_changed);
}

/**
 * albady_setenv - Initialize a new environment variable,
 *                  or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int albady_setenv(albady_info_t *info, char *var, char *value)
{
    char *buf = NULL;
    albady_list_t *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = albady_malloc(albady_strlen(var) + albady_strlen(value) + 2);
    if (!buf)
        return (1);
    albady_strcpy(buf, var);
    albady_strcat(buf, "=");
    albady_strcat(buf, value);
    node = info->env;
    while (node)
    {
        p = albady_starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    albady_add_node_end(&(info->env), buf, 0);
    albady_free(buf);
    info->env_changed = 1;
    return (0);
}
