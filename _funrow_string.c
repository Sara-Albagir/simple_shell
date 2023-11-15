#include "albady_shell.h"

/**
 * albady_strlen - impliment the strlen function.
 * @s: string in question.
 * Return: an int.
 */
int albady_strlen(char *s)
{
	int i = 0;

	if (!s)
	return (0);

	while (*s++)
	i++;
	return (i);
}

/**
 * albady_strcmp - impliment the strcpy function.
 * @s1: pre string in question.
 * @s2: post string in question.
 * Return: + or -.
 */
int albady_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
	if (*s1 != *s2)
	return (*s1 - *s2);
	s1++;
	s2++;
	}
	if (*s1 == *s2)
	return (0);
	else
	return (*s1 < *s2 ? -1 : 1);
}

/**
 * albady_starts_with - checks if the needle starts with the haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next char of haystack or NULL
 */
char *albady_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	if (*needle++ != *haystack++)
	return (NULL);
	return ((char *)haystack);
}

/**
 * albady_strcat - impliment the strcat function.
 * @dest: final buf.
 * @src: origional buf.
 * Return: an address.
 */
char *albady_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
	dest++;
	while (*src)
	*dest++ = *src++;
	*dest = *src;
	return (ret);
}
