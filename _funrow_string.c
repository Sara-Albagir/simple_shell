#include "albady_shell.h"

/**
 * albady_strlen - custom implementation of strlen function
 * @s: the string whose length to check
 *
 * Return: integer length of the string
 */
int albady_strlen(char *s)
{
    int i = 0;

    if (!s)
        return (0);

    while (*s++)
        i++;
    return (i);
}

/**
 * albady_strcmp - custom implementation of strcmp function
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int albady_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return (0);
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * albady_starts_with - checks if the needle starts with the haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next char of haystack or NULL
 */
char *albady_starts_with(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return (NULL);
    return ((char *)haystack);
}

/**
 * albady_strcat - custom implementation of strcat function
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *albady_strcat(char *dest, char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return ret;
}
