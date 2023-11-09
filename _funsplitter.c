#include "main.h"

/**
 * **spltstr - dvides a given string into words.
 * @strg: a given string.
 * @dlm: a string delemeter.
 * Return: null or points to array.
 */

char **spltstr(char *strg, char *dlm)
{
	int j, y, x, z, wdsnumb = 0;
	char **c;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	if (!dlm)
		dlm = " ";
	for (j = 0; strg[j] != '\0'; j++)
		if (!_isdlm(strg[j], dlm) && (_isdlm(strg[j + 1], dlm) || !strg[j + 1]))
			wdsnumb++;

	if (wdsnumb == 0)
		return (NULL);
	c = malloc((1 + wdsnumb) * sizeof(char *));
	if (!c)
		return (NULL);
	for (j = 0, y = 0; y < wdsnumb; y++)
	{
		while (_isdlm(strg[j], dlm))
			j++;
		x = 0;
		while (!_isdlm(strg[j + x], dlm) && strg[j + x])
			x++;
		c[y] = malloc((x + 1) * sizeof(char));
		if (!c[y])
		{
			for (x = 0; x < y; x++)
				free(c[x]);
			free(c);
			return (NULL);
		}
		for (z = 0; z < x; z++)
			c[y][z] = strg[j++];
		c[y][z] = 0;
	}
	c[y] = NULL;
	return (c);
}

/**
 * **spltstr1 - dvides a given string into words
 * @strg: a given string.
 * @dlm: a string delemeter
 * Return: null or points to array.
 */
char **spltstr1(char *strg, char dlm)
{
	int j, y, x, z, wdsnumb = 0;
	char **c;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	for (j = 0; strg[j] != '\0'; j++)
		if ((strg[j] != dlm && strg[j + 1] == dlm) ||
		    (strg[j] != dlm && !strg[j + 1]) || strg[j + 1] == dlm)
			wdsnumb++;
	if (wdsnumb == 0)
		return (NULL);
	c = malloc((1 + wdsnumb) * sizeof(char *));
	if (!c)
		return (NULL);
	for (j = 0, y = 0; y < wdsnumb; y++)
	{
		while (strg[j] == dlm && strg[j] != dlm)
			j++;
		x = 0;
		while (strg[j + x] != dlm && strg[j + x] && strg[j + x] != dlm)
			x++;
		c[y] = malloc((x + 1) * sizeof(char));
		if (!c[y])
		{
			for (x = 0; x < y; x++)
				free(c[x]);
			free(c);
			return (NULL);
		}
		for (z = 0; z < x; z++)
			c[y][z] = strg[j++];
		c[y][z] = 0;
	}
	c[y] = NULL;
	return (c);
