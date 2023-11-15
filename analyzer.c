#include "albady_shell.h"

/**
 * albady_is_cmd - tells if the file is an ex cmd.
 * @info: parameter of type struct.
 * @path: working dir to the file.
 * Return: 0 or 1.
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
 * albady_dup_chars - function that dubble a char.
 * @pathstr: a string.
 * @start: beginning indx.
 * @stop: terminating indx.
 * Return: an address.
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
 * albady_find_path - search for the working path.
 * @info: parameter struct.
 * @pathstr: string working dir.
 * @cmd: in question cmd.
 * Return: the path.
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
