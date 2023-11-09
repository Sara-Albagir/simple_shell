#include "main.h"

/**
 * len_strg - tell the strings length.
 * @c: string in question.
 * Return: an int.
 */
int len_strg(char *c)
{
	int j = 0;

	if (!c)
		return (0);

	while (*c++)
		j++;
	return (j);
}

/**
 * cmp_strg - compares 2 strings.
 * @c1: pre string.
 * @c2: post string.
 * Return: - or +.
 */
int cmp_strg(char *c1, char *c2)
{
	while (*c1 && *c2)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	if (*c1 == *c2)
		return (0);
	else
		return (*c1 < *c2 ? -1 : 1);
}

/**
 * _haystarts - test for the haystack.
 * @strstack: in question string.
 * @ndl: in questin sub string
 * Return: null or an address.
 */
char *_haystarts(const char *strstack, const char *ndl)
{
	while (*ndl)
		if (*ndl++ != *strstack++)
			return (NULL);
	return ((char *)strstack);
}

/**
 * cat_strg - string concatenator.
 * @dbuf: final buffer.
 * @sbuf: original buffer.
 * Return: final buffer pointer.
 */
char *cat_strg(char *dbuf, char *sbuf)
{
	char *fin = dbuf;

	while (*dbuf)
		dbuf++;
	while (*sbuf)
		*dbuf++ = *sbuf++;
	*dbuf = *sbuf;
	return (fin);
}
