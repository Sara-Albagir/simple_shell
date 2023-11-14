#include "albady_shell.h"

/**
 * albady_list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t albady_list_len(const albady_list_t *h)
{
    size_t i = 0;

    while (h)
    {
        h = h->next;
        i++;
    }
    return (i);
}

/**
 * albady_list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **albady_list_to_strings(albady_list_t *head)
{
    albady_list_t *node = head;
    size_t i = albady_list_len(head), j;
    char **strs;
    char *str;

    if (!head || !i)
        return (NULL);
    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (NULL);
    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(albady_strlen(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (NULL);
        }

        str = albady_strcpy(str, node->str);
        strs[i] = str;
    }
    strs[i] = NULL;
    return (strs);
}

/**
 * albady_print_list - prints all elements of an albady_list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t albady_print_list(const albady_list_t *h)
{
    size_t i = 0;

    while (h)
    {
        albady_puts(albady_convert_number(h->num, 10, 0));
        albady_putchar(':');
        albady_putchar(' ');
        albady_puts(h->str ? h->str : "(nil)");
        albady_puts("\n");
        h = h->next;
        i++;
    }
    return (i);
}

/**
 * albady_node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
albady_list_t *albady_node_starts_with(albady_list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = albady_starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return (node);
        node = node->next;
    }
    return (NULL);
}

/**
 * albady_get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t albady_get_node_index(albady_list_t *head, albady_list_t *node)
{
    size_t i = 0;

    while (head)
    {
        if (head == node)
            return (i);
        head = head->next;
        i++;
    }
    return (-1);
}
