#include "albady_shell.h"

/**
 * albady_eputs - prints an input string to standard error
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void albady_eputs(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        albady_eputchar(str[i]);
        i++;
    }
}

/**
 * albady_eputchar - writes the character c to standard error
 * @c: The character to print
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int albady_eputchar(char c)
{
    static int i;
    static char buf[ALBADY_WRITE_BUF_SIZE];

    if (c == ALBADY_BUF_FLUSH || i >= ALBADY_WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != ALBADY_BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * albady_putfd - writes the character c to a given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int albady_putfd(char c, int fd)
{
    static int i;
    static char buf[ALBADY_WRITE_BUF_SIZE];

    if (c == ALBADY_BUF_FLUSH || i >= ALBADY_WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != ALBADY_BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * albady_putsfd - prints an input string to a given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int albady_putsfd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += albady_putfd(*str++, fd);
    }
    return (i);
}
