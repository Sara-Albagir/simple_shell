#include "main.h"

/**
 * main - our main function.
 * @arc: the count of arguments.
 * @arv: the vector of arguments.
 * Return: 0 or 1.
 */
int main(int arc, char **arv)
{
	ads_t ads[] = { ADS_INIT };
	int vp = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (vp)
		: "r" (vp));

	if (arc == 2)
	{
		vp = open(arv[1], O_RDONLY);
		if (vp == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(arv[0]);
				_eputs(": 0: Can't open ");
				_eputs(arv[1]);
				_eputchar('\n');
				_eputchar(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		ads->readvp = vp;
	}
	populate_env_list(ads);
	read_history(ads);
	hsh(ads, arv);
	return (EXIT_SUCCESS);
}
