#include "main.h"

/**
 * str_cpy - copies a string.
 * @destin: Destination of astring to be copied to.
 * @src: The source of string.
 * @n: amt of chara to be copied.
 * Return: concatenated string.
 */
char *str_cpy(char *destin, char *src, int n)
{
	int i, o;
	char *s = destin;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		destin[i] = src[i];
		i++;
	}
	if (i < n)
	{
		o = i;
		while (o < n)
		{
			destin[o] = '\0';
			o++;
		}
	}
	return (s);
}

/**
 * str_cat - Concatenates two strings.
 * @destin: The first string.
 * @src: The second string.
 * @n: The amt of bytes to be maximally used.
 * Return: concatenated string.
 */
char *str_cat(char *destin, char *src, int n)
{
	int i, o;
	char *s = destin;

	i = 0;
	o = 0;
	while (destin[i] != '\0')
		i++;
	while (src[o] != '\0' && o < n)
	{
		destin[i] = src[o];
		i++;
		o++;
	}
	if (o < n)
		destin[i] = '\0';
	return (s);
}

/**
 * str_chr - locates chara in a str.
 * @s: The string to be parsed.
 * @c: Character to look for
 * Return: (s) pointer to the memory area s.
 */
char *str_chr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
