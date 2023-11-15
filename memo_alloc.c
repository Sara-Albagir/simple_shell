#include "albady_shell.h"

/**
 * albady_memset - insert the memo with bytes.
 * @s: points to thw memory.
 * @b: the mentioned bytes.
 * @n: number of bytes.
 * Return: an address.
 */
char *albady_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	s[i] = b;
	return (s);
}

/**
 * albady_ffree - string free.
 * @pp:in question strings.
 */
void albady_ffree(char **pp)
{
	char **a = pp;

	if (!pp)
	return;
	while (*pp)
	free(*pp++);
	free(a);
}

/**
 * albady_realloc - memorey reallocator.
 * @ptr: points to the first block.
 * @old_size: size of the first block.
 * @new_size: size if the final block.
 * Return: an address.
 */
void *albady_realloc(void *ptr, unsigned int old_size,
unsigned int new_size)
{
	char *p;

	if (!ptr)
	return (malloc(new_size));
	if (!new_size)
	return (albady_ffree(ptr), NULL);
	if (new_size == old_size)
	return (ptr);

	p = malloc(new_size);
	if (!p)
	return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
