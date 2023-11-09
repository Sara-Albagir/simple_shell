#include "main.h"

/**
 * poin_free - a function that frees the pointer.
 * @poinads: in question pointer address.
 * Return: 0 or 1.
 */
int poin_free(void **poinads)
{
	if (poinads && *poinads)
	{
		free(*poinads);
		*poinads = NULL;
		return (1);
	}
	return (0);
}
