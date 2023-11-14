#include "albady_shell.h"

/**
 * albady_is_cmd - determines file is an executable comd
 * @info: the albady_info_t struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int albady_is_cmd(albady_info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
	return (0);

	if (st.st_mode & S_IFREG)
	{
	return (1);
	}
	return (0);
}

/**
 * albady_dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *albady_dup_chars(char *pathstr, int start, int stop)
{
	static char buf[ALBADY_READ_BUF_SIZE];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
	if (pathstr[i] != ':')
	buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * albady_find_path - finds this cmd in the PATH string
 * @info: the albady_info_t struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *albady_find_path(albady_info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((albady_strlen(cmd) > 2) && albady_starts_with(cmd, "./"))
	{
		if (albady_is_cmd(info, cmd))
		return (cmd);
	}
	while (1)
	{
	if (!pathstr[i] || pathstr[i] == ':')
	{
		path = albady_dup_chars(pathstr, curr_pos, i);
		if (!*path)
		albady_strcat(path, cmd);
		else
		{
		albady_strcat(path, "/");
		albady_strcat(path, cmd);
		}
		if (albady_is_cmd(info, path))
		return (path);
		if (!pathstr[i])
		break;
		curr_pos = i;
	}
	i++;
	}
	return (NULL);
}
