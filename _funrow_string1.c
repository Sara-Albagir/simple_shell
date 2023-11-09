#include "main.h"

/**
 * _cpy_strg - function that copy a string.
 * @dbuf: final buff.
 * @sbuf: origional buff.
 * Return: a pointer.
 */
char *_cpy_strg(char *dbuf, char *sbuf)
{
	int j = 0;

	if (dbuf == sbuf || sbuf == 0)
		return (dbuf);
	while (sbuf[j])
	{
		dbuf[j] = sbuf[j];
		j++;
	}
	dbuf[j] = 0;
	return (dbuf);
}

/**
 * dup_strg - a function that dubble a string.
 * @strg: a given string in question.
 * Return: points to the given string.
 */
char *dup_strg(const char *strg)
{
	int lnth = 0;
	char *fin;

	if (strg == NULL)
		return (NULL);
	while (*strg++)
		lnth++;
	fin = malloc(sizeof(char) * (lnth + 1));
	if (!fin)
		return (NULL);
	for (lnth++; lnth--;)
		fin[lnth] = *--strg;
	return (fin);
}

/**
 *inp_strg - take a given string and prints it.
 *@strg: a given string.
 * Return: none.
 */
void inp_strg(char *strg)
{
	int j = 0;

	if (!strg)
		return;
	while (strg[j] != '\0')
	{
		_printchar(strg[j]);
		j++;
	}
}

/**
 * _printchar - prints out ch.
 * @ch: a char to print.
 * Return: 1 or -1.
 */
int _printchar(char ch)
{
	static int j;
	static char buff[WRITE_BUFF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUFF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (ch != BUFF_FLUSH)
		buff[j++] = ch;
	return (1);
}
