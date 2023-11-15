#include "shell.h"

/**
 * main - is the main program`s function.
 * @vecar: the arguments.
 * @cuntar: the arguments count.
 * Return: 0.
 */

int main(int cuntar, char **vecar)
{
	char *length = NULL;
	char **cmd = NULL;
	int posit;
	(void) cuntar;

		while (1)
		{
			length = _lnreader();

			if (length == NULL)
			{
				if (isatty(STDIN_FILENO))
					write(STDOUT_FILENO, "\n", 1);
				return (posit);
			}

			cmd = splitter(length);
			if (!cmd)
				continue;

			posit = exe(cmd, vecar);
		}
}
