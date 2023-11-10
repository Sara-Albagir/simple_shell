#include "main.h"

/**
 * _get_input - buffs chained commands.
 * @ads: The parameter struct.
 * @buf: The address of buffer.
 * @len: The address of alen var.
 *
 * Return: bytes read.
 */
ssize_t _get_input(ads_t *ads, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*alen) /* if nothn left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(ads, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			ads->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(ads, *buf, ads->histcount++);
			/* if (_strchr(*buf, ';')) is this command chain? */
			{
				*len = r;
				ads->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - Gets a line minus the newline.
 * @ads: The parameter structure.
 *
 * Return: The bytes read.
 */
ssize_t get_input(ads_t *ads)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, o, alen;
	ssize_t r = 0;
	char **buf_p = &(ads->arg), *p;

	_putchar(BUF_FLUSH);
	r = _inputbuf(ads, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		o = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(ads, buf, &o, i, len);
		while (o < len)
		{
			if (is_chain(ads, buf, &o))
				break;
			o++;
		}

		i = o + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			ads->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads buffer.
 * @ads: The parameter struct.
 * @buf: buffer.
 * @i: size.
 *
 * Return: r
 */
ssize_t read_buf(ads_t *ads, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(ads->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _get_line - gets the next line from STDIN.
 * @ads: The parameter struct.
 * @ptr: The address of pointer to buffer, preallocated or NULL.
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _get_line(ads_t *ads, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(ads, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strcha(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		str_cat(new_p, buf + i, k - i);
	else
		str_cpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * _sigintHandler - Blocks ctrl-C.
 * @sig_num: signal number.
 *
 * Return: void
 */
void _sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
