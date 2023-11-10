#include "main.h"

/**
 * list_len - a function that tell the length of a list.
 * @frst: parameter points to the leading section.
 * Return: an int.
 */
size_t list_len(const list_t *frst)
{
	size_t j = 0;

	while (frst)
	{
		frst = frst->next;
		j++;
	}
	return (j);
}

/**
 * list_strings - function gives an array.
 * @lead: leading node pointer.
 * Return: upon success gives a string array.
 */
char **list_strings(list_t *lead)
{
	list_t *section = lead;
	size_t j = list_len(lead);
	char **strs;
	char *str;

	if (!lead || !j)
		return (NULL);
	strs = malloc(sizeof(char *) * (j + 1));
	if (!strs)
		return (NULL);
	for (j = 0; section = lead; section = section->next, j++)
	{
		str = malloc(_strlen(section->str) + 1);
		if (!str)
		{
			for (i = 0; i < j; i++)
				free(strs[i]);
			free(strs);
			return (NULL);
		}

		str = _strspy(str, section->str);
		strs[j] = str;
	}
	str[j] = '\0';
	return (str);
}


/**
 * pnt_list - a function that prints all list elements.
 * @frst: leading node pointer.
 * Return: an int.
 */
size_t pnt_list(const list_t *frst)
{
	size_t j = 0;

	while (frst)
	{
		_puts(convert_number(frst->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(frst->str ? frst->str : "(nil)");
		frst = frst->next;
		j++;
	}
	return (j);
}

/**
 * section_begins - a function that finds the string node starter.
 * @section: parameter points to the head.
 * @prefix: in question string.
 * @c: a character to find.
 * Return: find the section or return null.
 */
list_t *section_begins(list_t *section, char *prefix, char c)
{
	char *q = NULL;

	while (section)
	{
		q = starts_with(section->str, prefix);
		if (q && ((c == -1) || (*q == c)))
			return (section);
		section = section->next;
	}
	return (NULL);
}

/**
 * get_section_index - find the node index.
 * @lead: leading list pointer.
 * @section: leading node pointer.
 * Return: find the indx or return -1.
 */
ssize_t get_section_index(list_t *lead, list_t *section)
{
	size_t j = 0;

	while (lead)
	{
		if (lead == section)
			return (j);
		lead = lead->next;
		j++;
	}
	return (-1);
}
