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
	static char buff[1024];
	int j = 0, x = 0;

	for (x = 0, j = srt; j < stp; j++)
		if (strgpath[j] != ':')
			buff[x++] = strgpath[j];
	buff[x] = 0;
	return (buff);
}

/**
 * _pathfinder - finds this cmd in the PATH string
 * @ads: parameter of type struct.
 * @strgpath: a string path.
 * @cmd: in question cmd.
 * Return: cmd or null.
 */
char *_pathfinder(ads_t *ads, char *strgpath, char *cmd)
{
	int j = 0, ong_psn = 0;
	char *filepath;

	if (!strgpath)
		return (NULL);
	if ((strg_len(cmd) > 2) && _haystarts(cmd, "./"))
	{
		if (_iscmd(ads, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!strgpath[j] || strgpath[j] == ':')
		{
			filepath = _chardup(strgpath, ong_psn, j);
			if (!*filepath)
				cat_strg(filepath, cmd);
			else
			{
				cat_strg(filepath, "/");
				cat_strg(filepath, cmd);
			}
			if (_iscmd(ads, filepath))
				return (filepath);
			if (!strgpath[j])
				break;
			ong_psn = j;
		}
		j++;
	}
	return (NULL);
}
