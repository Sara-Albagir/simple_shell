#include "shell.h"

/**
* _stringfreeing - function that free the memory.
* @ary: an array points to a string.
* Return: void.
*/

void _stringfreeing(char **ary)
{
	int h;

	if (!ary)
		return;

	for (h = 0; ary[h]; h++)
	{
		free(ary[h]);
		ary[h] = NULL;
	}

	free(ary), ary = NULL;
}
