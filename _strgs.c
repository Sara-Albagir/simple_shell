#include "shell.h"

/**
 * dup_strg - a function that duplicate 2 strings.
 * @srg: the string in question.
 * Return: a pointer.
 */

char *dup_strg(const char *srg)
{
	char *poin;
	int h, line = 0;

	if (srg == NULL)
		return (NULL);
	while (*srg != '\0')
	{
		line++;
		srg++;
	}
	srg = srg - line;
	poin = malloc(sizeof(char) * (line + 1));
	if (poin == NULL)
		return (NULL);
	for (h = 0; h <= line; h++)
		poin[h] = srg[h];
	return (poin);
}

/**
 * cmp_strg - a function that takes 2 strings and compare.
 * @a1: first one in question.
 * @a2: seconed one in question.
 * Return: the result.
 */

int cmp_strg(char *a1, char *a2)
{
	int prm;

	prm = (int)*a1 - (int)*a2;
	while (*a1)
	{
		if (*a1 != *a2)
		break;
	a1++;
	a2++;
	prm = (int)*a1 - (int)*a2;
			break;
		a1++;
		a2++;
		prm = (int)*a1 - (int)*a2;
	}
	return (prm);
}

/**
 * len_strg - hold the length of a given string.
 * @a: string in question.
 * Return: the length.
 */

int len_strg(char *a)
{
	int line = 0;

	while (a[line])
		line++;
	return (line);
}

/**
 * cat_strg - a concat function.
 * @fbuf: final destination.
 * @sbuf: source buffer.
 * Return: destination.
 */

char *cat_strg(char *fbuf, char *sbuf)
{
	char *u = fbuf;

	while (*u)
		u++;

	while (*sbuf)
	{
		*u = *sbuf;
		u++;
		sbuf++;
	}
	*u = *sbuf;
	return (fbuf);
		*u = *sbuf;
		return (fbuf);
}

/**
 * cpy_strg - function that copy 2 given strings.
 * @fbuf: final destination.
 * @sbuf: source buffer.
 * Return: destination.
 */

char *cpy_strg(char *fbuf, char *sbuf)
{
	int h = 0;

	while (sbuf[h])
	{
		fbuf[h] = sbuf[h];
		h++;
	}
	fbuf[h] = '\0';
	return (fbuf);
}
