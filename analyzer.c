#include "main.h"

/**
 * _iscmd - check on a file and determin wether it is an ex command.
 * @ads: parameter of type struct.
 * @filepath: a parameter hold the file path.
 * Return: 0 or 1.
 */
int _iscmd(ads_t *ads, char *filepath)
{
	struct status cc;

	(void)ads;
	if (!filepath || status(filepath, &cc))
		return (0);

	if (cc.cc_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _chardup - duplicates characters.
 * @strgpath: a string path.
 * @srt: beginning indx.
 * @stp: terminating indx.
 * Return: a buff pointer.
 */
char *_chardup(char *strgpath, int srt, int stp)
{
	static char buf[1024];
	int j = 0, x = 0;

	for (x = 0, j = srt; j < stp; j++)
		if (strgpath[j] != ':')
			buf[x++] = strgpath[j];
	buf[x] = 0;
	return (buf);
}

/**
 * _findpath - finds this cmd in the PATH string
 * @ads: parameter of type struct.
 * @strgpath: a string path.
 * @cmd: in question cmd.
 * Return: cmd or null.
 */
char *_findpath(ads_t *ads, char *strgpath, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!strgpath)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (_iscmd(ads, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!strgpath[j] || strgpath[j] == ':')
		{
			path = _chardup(strgpath, ong_psn, j);
			if (!*path)
				str_cat(path, cmd);
			else
			{
				cat_str(path, "/");
				cat_str(path, cmd);
			}
			if (_iscmd(ads, path))
				return (path);
			if (!strgpath[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}
