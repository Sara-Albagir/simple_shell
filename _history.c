#include "main.h"
/**
 * history_file - The history file
 * @ads: parameter struct.
 * Return: allocated str containg history of file
 */
char *history_file(ads_t *ads)
{
	char *buff, *dir;

	dir = get_env(ads, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	str_cpy(buff, dir);
	_strconcat(buff, "/");
	_strconcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history_file - creates file, or appends existing file
 * @ads: Parameter struct.
 * Return: success 1, else -1
 */
int write_history_file(ads_t *ads)
{
	ssize_t fd;
	char *filename = get_history_file(ads);
	list_t *section = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (section = ads->history; section; section = section->next)
	{
		_putsfd(section->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _readhistory - reads history from the file.
 * @ads: Parameter struct
 * Return: histcount on success, otherwise 0
 */
int _readhistory(ads_t *ads)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history_file(ads);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_history_list(ads, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(ads, buff + last, linecount++);
	free(buff);
	ads->histcount = linecount;
	while (ads->histcount-- >= HIST_MAX)
		delete_node_at_index(&(ads->history), 0);
	renumber_history(ads);
	return (ads->histcount);
}

/**
 * history_list - adds entry to history linkd list.
 * @ads: Struct containing potential args.
 * @buff: buffer.
 * @line_count: History linecount.
 * Return: 0 Always
 */
int history_list(ads_t *ads, char *buff, int line_count)
{
	list_t *section = NULL;

	if (ads->history)
		section = ads->history;
	add_node_end(&section, buff, line_count);

	if (!ads->history)
		ads->history = section;
	return (0);
}

/**
 * re_num_history - renumbers the history.
 * @ads: Struct containing potential args.
 * Return: new count
 */
int re_num_history(ads_t *ads)
{
	list_t *section = ads->history;
	int i = 0;

	while (section)
	{
		section->num = i++;
		section = section->next;
	}
	return (ads->histcount = i);
}
