#include "main.h"
/**
 *_aputs - prints an input string
 * @cha: string printed
 *
 * Return: Nothing
 */
void _aputs(char *cha)
{
	int i = 0;

	if (!cha)
		return;
	while (cha[i] != '\0')
	{
		_aputchar(cha[i]);
		i++;
	}
}

/**
 * _bputchar - writes character x to stderr
 * @x: chara to print
 * Return: 1 on success.
 * On error, -1 is returned, and errno is set.
 */
int _bputchar(char x)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (x != BUF_FLUSH)
		buf[i++] = x;
	return (1);
}

/**
 * put_sd - writes the char c to given sd
 * @c: chara to print
 * @sd: file descriptor to write to
 *
 * Return: 1 On success.
 * On error, returns -1, and errno is set appropriately.
 */
int put_sd(char c, int sd)
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
 * put_ssd - prints an input str
 * @str: string printed
 * @sd: file descriptor to write to
 *
 * Return: Number of chars put.
 */
int put_ssd(char *str, int sd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_sd(*str++, sd);
	}
	return (i);
}
