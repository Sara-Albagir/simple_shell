#include "main.h"

/**
 * _add_sectin - a function that adds a _add_section_end.
 * @lead: points to the leading _add_section_end.
 * @strg: string in question.
 * @ind_num: the indx of the _add_section_end.
 * Return: an int.
 */
list_t *_add_sectin(list_t **lead, const char *strg, int ind_num)
{
	list_t *new_lead;

	if (!lead)
		return (NULL);
	new_lead = malloc(sizeof(list_t));
	if (!new_lead)
		return (NULL);
	_memset((void *)new_lead, 0, sizeof(list_t));
	new_lead->ind_num = ind_num;
	if (strg)
	{
		new_lead->strg = _strdup(strg);
		if (!new_lead->strg)
		{
			free(new_lead);
			return (NULL);
		}
	}
	new_lead->next = *lead;
	*lead = new_lead;
	return (new_lead);
}

/**
 * _add_section_end - a function that adds a _add_section_end at the end.
 * @lead: points to the leading _add_section_end.
 * @strg: string in question.
 * @ind_num: the indx of the _add_section_end.
 * Return: an int.
 */
list_t *add_node_end(list_t **lead, const char *strg, int ind_num)
{
	list_t *new_section, *section;

	if (!lead)
		return (NULL);

	section = *lead;
	new_section = malloc(sizeof(list_t));
	if (!new_section)
		return (NULL);
	_memset((void *)new_section, 0, sizeof(list_t));
	new_section->ind_num = ind_num;
	if (strg)
	{
		new_section->strg = _strdup(strg);
		if (!new_section->strg)
		{
			free(new_section);
			return (NULL);
		}
	}
	if (section)
	{
		while (section->next)
			section = section->next;
		section->next = new_section;
	}
	else
		*lead = new_section;
	return (new_section);
}

/**
 * strg_listprint - a function that only prints string element.
 * @frst: 1st section pointer.
 * Return: an int.
 */
size_t strg_listprint(const list_t *frst)
{
	size_t j = 0;

	while (frst)
	{
		_puts(frst->strg ? frst->strg : "(nil)");
		_puts("\n");
		frst = frst->next;
		j++;
	}
	return (j);
}

/**
 * _section_delete - a function that delete a node.
 * @lead: points to the leading _add_section_end.
 * @indx: nodes to delete.
 * Return: 0 or 1.
 */
int _section_delete(list_t **lead, unsigned int indx)
{
	list_t *section, *pre_section;
	unsigned int j = 0;

	if (!lead || !*lead)
		return (0);

	if (!indx)
	{
		section = *lead;
		*lead = (*lead)->next;
		free(section->strg);
		free(section);
		return (1);
	}
	section = *lead;
	while (section)
	{
		if (j == indx)
		{
			pre_section->next = section->next;
			free(section->strg);
			free(section);
			return (1);
		}
		j++;
		pre_section = section;
		section = section->next;
	}
	return (0);
}

/**
 * _listfree - function that free all nodes.
 * @lead_poinads: points to the leading node.
 * Return: none.
 */
void _listfree(list_t **lead_poinads)
{
	list_t *section, *next_section, *lead;

	if (!lead_poinads || !*lead_poinads)
		return;
	lead = *lead_poinads;
	section = lead;
	while (section)
	{
		next_section = section->next;
		free(section->strg);
		free(section);
		section = next_section;
	}
	*lead_poinads = NULL;
}
