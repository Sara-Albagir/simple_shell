#include "main.h"

/**
 * _lenlist - a function that tell the length of a list.
 * @frst: parameter points to the leading section.
 * Return: an int.
 */
size_t _lenlist(const list_t *frst)
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
 * _strgs_list - function gives an array.
 * @lead: leading node pointer.
 * Return: upon success gives a string array.
 */
char **_strgs_list(list_t *lead)
{
	list_t *section = lead;
	size_t j = _lenlist(lead), j;
	char **strgs;
	char *strg;

	if (!lead || !j)
		return (NULL);
	strgs = malloc(sizeof(char *) * (j + 1));
	if (!strgs)
		return (NULL);
	for (j = 0; section; section = section->next, j++)
	{
		strg = malloc(_strlen(section->strg) + 1);
		if (!strg)
		{
			for (j = 0; j < j; j++)
				free(strgs[j]);
			free(strgs);
			return (NULL);
		}

		strg = _cpy_strg(strg, section->strg);
		strgs[j] = strg;
	}
	strgs[j] = NULL;
	return (strgs);
}


/**
 * _listprint - a function that prints all list elements.
 * @frst: leading node pointer.
 * Return: an int.
 */
size_t _listprint(const list_t *frst)
{
	size_t j = 0;

	while (frst)
	{
		inp_strg(convert_number(frst->num, 10, 0));
		_printchar(':');
		_printchar(' ');
		inp_strg(frst->strg ? frst->strg : "(nil)");
		inp_strg("\n");
		frst = frst->next;
		j++;
	}
	return (j);
}

/**
 * section_starter - a function that finds the string node starter.
 * @section: parameter points to the head.
 * @pref: in question string.
 * @ch: a character to find.
 * Return: find the section or return null.
 */
list_t *section_starter(list_t *section, char *pref, char ch)
{
	char *q = NULL;

	while (section)
	{
		q = starts_with(section->strg, pref);
		if (q && ((ch == -1) || (*q == ch)))
			return (section);
		section = section->next;
	}
	return (NULL);
}

/**
 * section_indx - find the node index.
 * @lead: leading list pointer.
 * @section: leading node pointer.
 * Return: find the indx or return -1.
 */
ssize_t section_indx(list_t *lead, list_t *section)
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
