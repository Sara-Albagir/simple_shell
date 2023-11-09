#include "main.h"
/**
 * _toi - converts a string to int
 * @s: string converted
 * Return: if no numbers in string 0, converted num otherwise
 * -1 on error
 */

int _toi(char *s)
{
	int i = 0;
	unsigned long int output = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			output *= 10;
			output += (s[i] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * _error - prints error message
 * @ads: para and returns ads struct
 * @astr: string containing spec error type
 * Return: if no numbers in string 0, converted number otherwise
 * -1 on error
 */

void _error(ads_t *ads, char *astr)
{
	_eputs(ads->fname);
	_eputs(": ");
	print_d(ads->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(ads->argv[0]);
	_eputs(": ");
	_eputs(astr);
}

/**
 * print_e - Prints a decimal (int) num (base 10)
 * @input: The input.
 * @fde: File descriptor to write to
 * Return: The num of chara printed.
 */
int print_e(int input, int fde)
{
	int (*__putchar)(char) = _putchar;
	int i, total = 0;
	unsigned int _abs_, current;

	if (fde == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		total++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			total++;
		}
		current %= i;
	}
	__putchar('0' + current);
	total++;

	return (total);
}

/**
 * _convertnum - function convertor, clone.
 * @num: numb
 * @base: base.
 * @flags: The arg flags.
 *
 * Return: A strin.g
 */
char *_convertnum(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * removes_comments - ftn replaces first instance of '#' with '\0'.
 * @mod: THe address of  string to modify.
 *
 * Return: 0 Always;
 */
void removes_comments(char *mod)
{
	int i;

	for (i = 0; mod[i] != '\0'; i++)
		if (mod[i] == '#' && (!i || mod[i - 1] == ' '))
		{
			mod[i] = '\0';
			break;
		}
}
