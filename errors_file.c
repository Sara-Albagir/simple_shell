#include "main.h"

/**
 * ef_puts - prints an input string
 * @str: string printed
 *
 * Return: Nothing
 */
void ef_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		ef_putchar(str[i]);
		i++;
	}
}

/**
 * ef_putchar - writes character c to stderr
 * @c: chara to print
 * Return: 1 on success.
 * On error, -1 is returned, and errno is set.
 */
int ef_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (x != BUF_FLUSH)
		buf[i++] = x;
	return (1);
}

/**
 * fd_put - writes the char c to given fd
 * @c: chara to print
 * @fd: file descriptor to write to
 *
 * Return: 1 On success.
 * On error, returns -1, and errno is set appropriately.
 */
int fd_put(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(sd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * fd_puts - prints an input str
 * @str: string printed
 * @fd: file descriptor to write to
 *
 * Return: Number of chars put.
 */
int fd_puts(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += fd_put(*str++, fd);
	}
	return (i);
}
