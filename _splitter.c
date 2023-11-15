#include "shell.h"
/*
 * splitter - function acts as atokenizer.
 *
 * @length: parameter.
 *
 * Return: null.
 *
 */

char **splitter(char *length)
{
	char *access = NULL, *trm = NULL;
	char **cmd = NULL;
	int tok = 0, h = 0;

	if (!length)
		return (NULL);
	trm = dup_strg(length);
	access = strtok(trm, DLM);
	while (access)
	{
		tok++;
		access = strtok(NULL, DLM);
	}
	free(trm), trm = NULL;

	cmd = malloc(sizeof(char *) * (tok + 1));
	if (!cmd)
	{
		free(length);
		return (NULL);
	}

	access = strtok(length, DLM);
	while (access)
	{
		cmd[h] = access;
		access = strtok(NULL, DLM);
		h++;
	}
	free(length), length = NULL;
	cmd[h] = NULL;
	return (cmd);
}
