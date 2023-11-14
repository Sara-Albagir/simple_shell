#include "albady_shell.h"

/**
 * albady_strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *albady_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
	return (dest);

	while (src[i])
	{
	dest[i] = src[i];
	i++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * albady_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *albady_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
	return (NULL);

	while (*str++)
	length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
	return (NULL);

	for (length++; length--;)
	ret[length] = *--str;

	return (ret);
}

/**
 * albady_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void albady_puts(char *str)
{
	int i = 0;

	if (!str)
	return;

	while (str[i] != '\0')
	{
	albady_putchar(str[i]);
	i++;
	}
}

/**
 * albady_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int albady_putchar(char c)
{
	static int i;
	static char buf[ALBADY_WRITE_BUF_SIZE];

	if (c == ALBADY_BUF_FLUSH || i >= ALBADY_WRITE_BUF_SIZE)
	{
	write(1, buf, i);
	i = 0;
	}

	if (c != ALBADY_BUF_FLUSH)
	buf[i++] = c;

	return (1);
}
