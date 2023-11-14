#include "albady_shell.h"

/**
 * albady_get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *albady_get_history_file(albady_info_t *info)
{
    char *buf, *dir;

    dir = albady_getenv(info, "HOME=");
    if (!dir)
        return (NULL);
    buf = albady_malloc(sizeof(char) * (albady_strlen(dir) + albady_strlen(ALBADY_HIST_FILE) + 2));
    if (!buf)
        return (NULL);
    buf[0] = 0;
    albady_strcpy(buf, dir);
    albady_strcat(buf, "/");
    albady_strcat(buf, ALBADY_HIST_FILE);
    return (buf);
}

/**
 * albady_write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int albady_write_history(albady_info_t *info)
{
    ssize_t fd;
    char *filename = albady_get_history_file(info);
    albady_list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    albady_free(filename);
    if (fd == -1)
        return (-1);
    for (node = info->history; node; node = node->next)
    {
        albady_putsfd(node->str, fd);
        albady_putfd('\n', fd);
    }
    albady_putfd(ALBADY_BUF_FLUSH, fd);
    close(fd);
    return (1);
}

/**
 * albady_read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int albady_read_history(albady_info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = albady_get_history_file(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    albady_free(filename);
    if (fd == -1)
        return (0);
    if (!fstat(fd, &st))
        fsize = st.st_size;
    if (fsize < 2)
        return (0);
    buf = albady_malloc(sizeof(char) * (fsize + 1));
    if (!buf)
        return (0);
    rdlen = read(fd, buf, fsize);
    buf[fsize] = 0;
    if (rdlen <= 0)
        return (albady_free(buf), 0);
    close(fd);
    for (i = 0; i < fsize; i++)
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            albady_build_history_list(info, buf + last, linecount++);
            last = i + 1;
        }
    if (last != i)
        albady_build_history_list(info, buf + last, linecount++);
    albady_free(buf);
    info->histcount = linecount;
    while (info->histcount-- >= ALBADY_HIST_MAX)
        albady_delete_node_at_index(&(info->history), 0);
    albady_renumber_history(info);
    return (info->histcount);
}

/**
 * albady_build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int albady_build_history_list(albady_info_t *info, char *buf, int linecount)
{
    albady_list_t *node = NULL;

    if (info->history)
        node = info->history;
    albady_add_node_end(&node, buf, linecount);

    if (!info->history)
        info->history = node;
    return (0);
}

/**
 * albady_renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int albady_renumber_history(albady_info_t *info)
{
    albady_list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }
    return (info->histcount = i);
}
