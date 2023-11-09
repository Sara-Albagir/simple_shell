#include "main.h"
/**
 * _inter_active - returns true if shell is interactive.
 * @ads: struct address
 * Return: interactive mode 1, 0 otherwise.
 */
int _inter_active(ads_t *ads)
{
	return (isatty(STDIN_FILENO) && ads->readfd <= 2);
}

/**
 * delim - checks if char is a delimeter
 * @a: char to check
 * @_deli: delimeter string
 * Return: if true 1, if false 0
 */
int delim(char a, char *_deli)
{
	while (*_deli)
		if (*_deli++ == a)
			return (1);
	return (0);
}

/**
 * alpha - checks for alpha char
 * @b: char to input
 * Return: if b is alphabetic 1, otherwise 0
 */

int alpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * str_to_int - converts a string to an int.
 * @c: string converted.
 * Return: if no numbers in string 0, converted num otherwise.
 */

int str_to_int(char *c)
{
	int w, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (w = 0;  c[w] != '\0' && flag != 2; w++)
	{
		if (c[w] == '-')
			sign *= -1;

		if (c[w] >= '0' && c[w] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (c[w] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
