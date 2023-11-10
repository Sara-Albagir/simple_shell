#include "main.h"

/**
 * bits_memo - hum function that locate bits to thememory.
 * @c: parameter points to the memory.
 * @cb: parameter byte.
 * @cn: num of byte.
 * Return: um pointer.
 */
char *bits_memo(char *c, char cb, unsigned int cn)
{
	unsigned int j;

	for (j = 0; j < cn; j++)
		c[j] = cb;
	return (c);
}

/**
 * strg_free - function that void hum string.
 * @poinpoin: parameter string.
 */
void strg_free(char **poinpoin)
{
	char **a = poinpoin;

	if (!poinpoin)
		return;
	while (*poinpoin)
		free(*poinpoin++);
	free(a);
}

/**
 * alloc_memo - function reallocate memory.
 * @poinads: parameter points tp the previous block.
 * @presize: size of the memo block.
 * @postsize: size of post memo block.
 * Return: an address.
 */
void *alloc_memo(void *poinads, unsigned int presize, unsigned int postsize)
{
	char *q;

	if (!poinads)
		return (malloc(postsize));
	if (!postsize)
		return (free(poinads), NULL);
	if (postsize == presize)
		return (poinads);

	q = malloc(postsize);
	if (!q)
		return (NULL);

	presize = presize < postsize ? presize : postsize;
	while (presize--)
		q[presize] = ((char *)poinads)[presize];
	free(poinads);
	return (q);
}
