#include "main.h"

/**
 * add_section - function that adds a node.
 * @lead: points to the leading node.
 * @str: string in question.
 * @num: the section index of the add_section_end.
 * Return: an int.
 */
list_t *add_section(list_t **lead, const char *str, int num)
{
	list_t *new_lead;

	if (!lead)
		return (NULL);
	new_lead = malloc(sizeof(list_t));
	if (!new_lead)
		return (NULL);
	_memset((void *)new_lead, 0, sizeof(list_t));
	new_lead->ind_num = num;
	if (str)
	{
		new_lead->str = _strdup(str);
		if (!new_lead->str)
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
 * add_section_end - a function that adds a _add_section_end at the end.
 * @lead: points to the leading _add_section_end.
 * @str: string in question.
 * @num: the index of the add_section_end.
 * Return: an int.
 */
list_t *add_section_end(list_t **lead, const char *str, int ind_num)
{
	list_t *new_section, *section;

	if (!lead)
		return (NULL);

	section = *lead;
	new_section = malloc(sizeof(list_t));
	if (!new_section)
		return (NULL);
	_memset((void *)new_section, 0, sizeof(list_t));
	new_section->num = num;
	if (str)
	{
		new_section->str = strdup(str);
		if (!new_section->str)
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
 * str_printlist - function that only prints string element.
 * @frst: 1st section pointer.
 * Return: an int.
 */
size_t str_printlist(const list_t *frst)
{
	size_t j = 0;

	while (frst)
	{
		_puts(frst->str ? frst->str : "(nil)");
		_puts("\n");
		frst = frst->next;
		j++;
	}
	return (j);
}

/**
 * section_delete - a function that delete a node.
 * @lead: points to the leading _add_section_end.
 * @index: nodes to delete.
 * Return: 0 or 1.
 */
int section_delete(list_t **lead, unsigned int index)
{
	list_t *section, *pre_section;
	unsigned int j = 0;

	if (!lead || !*lead)
		return (0);

	if (!index)
	{
		section = *lead;
		*lead = (*lead)->next;
		free(section->str);
		free(section);
		return (1);
	}
	section = *lead;
	while (section)
	{
		if (j == index)
		{
			pre_section->next = section->next;
			free(section->str);
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
 * list_free - function that free all nodes.
 * @lead_ptr: points to the leading node.
 * Return: none.
 */
void list_free(list_t **lead_ptr)
{
	list_t *section, *next_section, *lead;

	if (!lead_ptr || !*lead_ptr)
		return;
	lead = *lead_poinads;
	section = lead;
	while (section)
	{
		next_section = section->next;
		free(section->str);
		free(section);
		section = next_section;
	}
	*lead_ptr = NULL;
}
