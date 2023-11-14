#include "albady_shell.h"

/**
 * albady_get_input - buffers chained commands
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t albady_get_input(albady_info_t *info)
{
    static char *buf; /* the ';' command chain buffer */
    static size_t i, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    albady_putchar(ALBADY_BUF_FLUSH);
    r = albady_getline(info, &buf, &len);
    if (r == -1) /* EOF */
        return (-1);
    if (len)    /* we have commands left in the chain buffer */
    {
        j = i; /* init new iterator to current buf position */
        p = buf + i; /* get pointer for return */

        albady_check_chain(info, buf, &j, i, len);
        while (j < len) /* iterate to semicolon or end */
        {
            if (albady_is_chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1; /* increment past nulled ';'' */
        if (i >= len) /* reached end of buffer? */
        {
            i = len = 0; /* reset position and length */
            info->cmd_buf_type = ALBADY_CMD_NORM;
        }

        *buf_p = p; /* pass back pointer to current command position */
        return (albady_strlen(p)); /* return length of current command */
    }

    *buf_p = buf; /* else not a chain, pass back buffer from albady_getline() */
    return (r); /* return length of buffer from albady_getline() */
}

/**
 * albady_read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t albady_read_buf(albady_info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return (0);
    r = read(info->readfd, buf, ALBADY_READ_BUF_SIZE);
    if (r >= 0)
        *i = r;
    return (r);
}

/**
 * albady_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int albady_getline(albady_info_t *info, char **ptr, size_t *length)
{
    static char buf[ALBADY_READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = albady_read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return (-1);

    c = albady_strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = albady_realloc(p, s, s ? s + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);

    if (s)
        albady_strncat(new_p, buf + i, k - i);
    else
        albady_strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return (s);
}

/**
 * albady_sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void albady_sigintHandler(__attribute__((unused))int sig_num)
{
    albady_puts("\n");
    albady_puts("$ ");
    albady_putchar(ALBADY_BUF_FLUSH);
}
