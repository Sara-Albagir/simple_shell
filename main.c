#include "main.h"

/**
 * main - our main function.
 * @ac: the count of arguments.
 * @av: the vector of arguments.
 * Return: 0 or 1.
 */
int main(int ac, char **av)
{
	ads_t ads[] = { ADS_INIT };
	int vp = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (vp)
		: "r" (vp));

	if (ac == 2)
	{
		vp = open(av[1], O_RDONLY);
		if (vp == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				ef_puts(av[0]);
				ef_puts(": 0: Can't open ");
				ef_puts(arv[1]);
				ef_putchar('\n');
				ef_putchar(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		ads->readvp = vp;
	}
	populate_env_list(ads);
	read_history(ads);
	hsh(ads, av);
	return (EXIT_SUCCESS);
}
