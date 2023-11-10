#include "main.h"

/**
 * freeforever - a function that frees the pointer.
 * @poinads: in question pointer address.
 * Return: 0 or 1.
 */
int freeforever(void **poinads)
{
	if (poinads && *poinads)
	{
		free(*poinads);
		*poinads = NULL;
		return (1);
	}
	return (0);
}
