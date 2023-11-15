#include "shell.h"

/**
* _lnreader - function that reads a string input by the user.
* Return: the length of that string.
*/

char *_lnreader(void)
{
	char *length = NULL;
	size_t line = 0;
	ssize_t q;

	write(STDOUT_FILENO, "$ ", 2);
	q = getline(&length, &line, stdin);
	if (q == -1)
	{
	free(length);
		return (NULL);
	}

	return (length);
}
