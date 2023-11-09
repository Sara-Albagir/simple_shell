#include "main.h"

/**
 * _ischain - a function that check wether the char is a delometer one
 * @ads: a parameter of type struct
 * @buff: character buf
 * @q: a buf address
 * Return: 1 or 0
 */
int _ischain(ads_t *ads, char *buff, size_t *q)
{
	size_t y = *q;

	if (buff[y] == '|' && buff[y + 1] == '|')
	{
		buff[y] = 0;
		y++;
		ads->cmd_buff_type = CMD_OR;
	}
	else if (buff[y] == '&' && buff[y + 1] == '&')
	{
		buff[y] = 0;
		y++;
		ads->cmd_buff_type = CMD_AND;
	}
	else if (buff[y] == ';')
	{
		buff[y] = 0;
		ads->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = y;
	return (1);
}

/**
 * _checkchain - reach status to confirm continuing.
 * @ads: a parameter of type struct.
 * @buff: character buf.
 * @q: a buf address.
 * @j: starting point.
 * @ln: represent the buf length.
 * Return: none.
 */
void _checkchain(ads_t *ads, char *buff, size_t *q, size_t j, size_t ln)
{
	size_t y = *q;

	if (ads->cmd_buff_type == CMD_AND)
	{
		if (ads->status)
		{
			buff[j] = 0;
			y = ln;
		}
	}
	if (ads->cmd_buff_type == CMD_OR)
	{
		if (!ads->status)
		{
			buff[j] = 0;
			y = ln;
		}
	}

	*q = y;
}

/**
 * _alias_rep - reach to the string and change alias
 * @ads: a parameter of type struct
 * Return: 1 or 0.
 */
int _alias_rep(info_t *ads)
{
	int j;
	list_t *section;
	char *q;

	for (j = 0; j < 10; j++)
	{
		section = section_starts_with(ads->alias, ads->argo[0], '=');
		if (!section)
			return (0);
		free(ads->argo[0]);
		q = _strchr(section->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		ads->argo[0] = q;
	}
	return (1);
}

/**
 * _vars_rep - reach to the string and replace vars.
 * @ads: a parameter of type struct
 * Return: 1 or 0.
 */
int _vars_rep(ads_t *ads)
{
	int j = 0;
	list_t *section;

	for (j = 0; ads->argo[j]; j++)
	{
		if (ads->argo[j][0] != '$' || !ads->argo[j][1])
			continue;

		if (!_strcmp(ads->argo[j], "$?"))
		{
			_string_rep(&(ads->argo[j]),
				_strdup(convert_number(ads->status, 10, 0)));
			continue;
		}
		if (!_strcmp(ads->argo[j], "$$"))
		{
			_string_rep(&(ads->argo[j]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		section = node_starts_with(ads->env, &ads->argo[j][1], '=');
		if (section)
		{
			_string_rep(&(ads->argo[j]),
				_strdup(_strchr(section->str, '=') + 1));
			continue;
		}
		_string_rep(&ads->argo[j], _strdup(""));

	}
	return (0);
}

/**
 * _string_rep - change the string.
 * @pre: first string address.
 * @post: modefied string.
 * Return: 0 or 1.
 */
int _string_rep(char **pre, char *post)
{
	free(*pre);
	*pre = post;
	return (1);
}
