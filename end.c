#include "main.h"
/**
 * str_cpy - copies a string.
 * @destin: Destination of astring to be copied to.
 * @sc: The source of string.
 * @c: amt of chara to be copied.
 * Return: concatenated string.
 */
char *str_cpy(char *destin, char *sc, int c)
{
	int i, o;
	char *s = destin;

	i = 0;
	while (sc[i] != '\0' && i < c - 1)
	{
		destin[i] = sc[i];
		i++;
	}
	if (i < c)
	{
		o = i;
		while (o < c)
		{
			dest[o] = '\0';
			o++;
		}
	}
	return (s);
}

/**
 * _strconcat - Concatenates two strings.
 * @destin: The first string.
 * @sc: The second string.
 * @c: The amt of bytes to be maximally used.
 * Return: concatenated string.
 */
char *_strconcat(char *destin, char *sc, int c)
{
	int i, o;
	char *s = destin;

	i = 0;
	o = 0;
	while (destin[i] != '\0')
		i++;
	while (sc[o] != '\0' && o < n)
	{
		destin[i] = sc[o];
		i++;
		o++;
	}
	if (o < c)
		destin[i] = '\0';
	return (s);
}

/**
 * _chrstr - locates chara in a str.
 * @p: The string to be parsed.
 * @ch: Character to look for
 * Return: (s) pointer to the memory area s.
 */
char *_chrstr(char *p, char ch)
{
	do {
		if (*p == ch)
			return (p);
	} while (*p++ != '\0');

	return (NULL);
}
