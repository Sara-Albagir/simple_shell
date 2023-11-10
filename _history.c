#include "main.h"

/**
 * history_file - The history file
 * @ads: parameter struct.
 *
 * Return: allocated str containg history of file
 */
char *history_file(ads_t *ads)
{
	char *buf, *dir;

	dir = _getenv(ads, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	str_cpy(buf, dir);
	str_cat(buf, "/");
	str_cat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history_file - creates file, or appends existing file
 * @ads: Parameter struct.
 *
 * Return: success 1, else -1
 */
int write_history_file(ads_t *ads)
{
	ssize_t fd;
	char *filename = history_file(ads);
	list_t *section = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (section = ads->history; section; section = section->next)
	{
		fd_puts(section->str, fd);
		fd_put('\n', fd);
	}
	fd_put(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from the file.
 * @ads: Parameter struct
 *
 * Return: histcount on success, otherwise 0
 */
int read_history(ads_t *ads)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = history_file(ads);

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
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			buildhistory_list(ads, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildhistory_list(ads, buf + last, linecount++);
	free(buf);
	ads->histcount = linecount;
	while (ads->histcount-- >= HIST_MAX)
		delete_section_at_index(&(ads->history), 0);
	renumber_history(ads);
	return (ads->histcount);
}

/**
 * buildhistory_list - adds entry to history linkd list.
 * @ads: Struct containing potential args.
 * @buf: buffer.
 * @linecount: History linecount.
 * Return: 0 Always
 */
int buildhistory_list(ads_t *ads, char *buf, int linecount)
{
	list_t *section = NULL;

	if (ads->history)
		section = ads->history;
	add_section_end(&section, buf, linecount);

	if (!ads->history)
		ads->history = section;
	return (0);
}

/**
 * renum_history - renumbers the history.
 * @ads: Struct containing potential args.
 *
 * Return: new count
 */
int renum_history(ads_t *ads)
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
