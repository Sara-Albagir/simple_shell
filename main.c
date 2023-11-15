#include "albady_shell.h"

/**
 * main - main shell function.
 * @ac: number of args.
 * @av: vector of args.
 * Return: 0 or 1.
 */
int main(int ac, char **av)
{
	albady_info_t info = ALBADY_INFO_INIT;
	int fd = 2;

	asm ("mov %1, %0\n\t"
	"add $3, %0"
	: "=r" (fd)
	: "r" (fd));

	if (ac == 2)
	{
	fd = open(av[1], O_RDONLY);
		if (fd == -1)
	{
		if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
	{
		albady_eputs(av[0]);
		albady_eputs(": 0: Can't open ");
		albady_eputs(av[1]);
		albady_eputchar('\n');
		albady_eputchar(ALBADY_BUF_FLUSH);
		exit(127);
	}
	return (EXIT_FAILURE);
	}
	info.readfd = fd;
	}

	albady_populate_env_list(&info);
	albady_read_history(&info);
	albady_hsh(&info, av);
	return (EXIT_SUCCESS);
}
