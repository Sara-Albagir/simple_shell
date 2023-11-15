#include "albady_shell.h"

/**
 * albady_bfree - function that frees and null.
 * @ptr: point points to free.
 * Return: 1 or 0.
 */
int albady_bfree(void **ptr)
{
	if (ptr && *ptr)
	{
	free(*ptr);
	*ptr = NULL;
	return (1);
	}
	return (0);
}
