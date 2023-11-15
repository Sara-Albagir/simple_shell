#include "albady_shell.h"

/**
 * albady_is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int albady_is_chain(albady_info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * albady_check_chain - checks we should continue
 * chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void albady_check_chain(albady_info_t *info, char *buf,
size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * albady_replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int albady_replace_alias(albady_info_t *info)
{
	int i;
	albady_list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = albady_node_starts_with(albady_info_t->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = albady_strchr(node->str, '=');
		if (!p)
			return (0);
		p = albady_strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * albady_replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int albady_replace_vars(albady_info_t *info)
{
	int i = 0;
	albady_list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!albady_strcmp(info->argv[i], "$?"))
		{
			albady_replace_string(&(info->argv[i]),
				albady_strdup(albady_convert_number(info->status, 10, 0)));
			continue;
		}
		if (!albady_strcmp(info->argv[i], "$$"))
		{
			albady_replace_string(&(info->argv[i]),
				albady_strdup(albady_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = albady_node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			albady_replace_string(&(info->argv[i]),
				albady_strdup(albady_strchr(node->str, '=') + 1));
			continue;
		}
		albady_replace_string(&info->argv[i], albady_strdup(""));

	}
	return (0);
}

/**
 * albady_replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int albady_replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
