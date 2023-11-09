#include "main.h"
/**
 * _inputbuf - buffs chained commands.
 * @ads: The parameter struct.
 * @buff: The address of buff.
 * @alen: The address of alen var.
 * Return: bytes read.
 */
ssize_t _inputbuf(ads_t *ads, char **buff, size_t *alen)
{
	ssize_t r = 0;
	size_t alen_p = 0;

	if (!*alen) /* if nothn left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buff, &alen_p, stdin);
#else
		r = _getline(ads, buff, &alen_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			ads->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(ads, *buff, ads->histcount++);
			/* if (_strchr(*buf, ';')) is this command chain? */
			{
				*alen = r;
				ads->cmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * _getinput - Gets a line minus the newline.
 * @ads: The parameter structure.
 *
 * Return: The bytes read.
 */
ssize_t _getinput(ads_t *ads)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t i, o, alen;
	ssize_t r = 0;
	char **buff_p = &(ads->arg), *p;

	_putchar(BUF_FLUSH);
	r = _inputbuff(ads, &buff, &alen);
	if (r == -1) /* EOF */
		return (-1);
	if (alen)	/* we have commands left in the chain buffer */
	{
		o = i; /* init new iterator to current buf position */
		p = buff + i; /* get pointer for return */

		check_chain(ads, buff, &o, i, alen);
		while (o < len)
		{
			if (is_chain(ads, buff, &o))
				break;
			o++;
		}

		i = o + 1; /* increment past nulled ';'' */
		if (i >= alen) /* reached end of buffer? */
		{
			i = alen = 0; /* reset position and length */
			ads->cmd_buff_type = CMD_NORM;
		}

		*buff_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buff_p = buff; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buff - reads buffer.
 * @ads: The parameter struct.
 * @buff: buffer.
 * @n: size.
 *
 * Return: h
 */
ssize_t read_buff(ads_t *ads, char *buff, size_t *n)
{
	ssize_t h = 0;

	if (*n)
		return (0);
	h = read(ads->readfd, buff, READ_BUF_SIZE);
	if (h >= 0)
		*i = h;
	return (h);
}

/**
 * get_line - gets the next line from STDIN.
 * @ads: The parameter struct.
 * @ptb: The address of pointer to buffer, preallocated or NULL.
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: v
 */
int get_line(ads_t *ads, char **ptb, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, alen;
	size_t k;
	ssize_t r = 0, v = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptb;
	if (p && length)
		s = *length;
	if (i == alen)
		i = alen = 0;

	r = read_buf(ads, buf, &alen);
	if (r == -1 || (r == 0 && alen == 0))
		return (-1);

	c = _chrstr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : alen;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (v)
		_strconcat(new_p, buff + i, k - i);
	else
		str_cpy(new_p, buff + i, k - i + 1);

	v += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (v);
}

/**
 * sigint_Handler - Blocks ctrl-C.
 * @_signum: signal number.
 *
 * Return: void
 */
void sigint_Handler(__attribute__((unused))int _signum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
