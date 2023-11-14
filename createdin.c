#include "albady_shell.h"
/**
 * albady_myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: exits with a given exit status
 * (0) if info->argv[0] != "exit"
 */
int albady_myexit(albady_info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit argument */
	{
	exitcheck = albady_erratoi(info->argv[1]);
	if (exitcheck == -1)
	{
	info->status = 2;
	albady_print_error(info, "Illegal number: ");
	albady_eputs(info->argv[1]);
	albady_eputchar('\n');
	return (1);
	}
	info->err_num = albady_erratoi(info->argv[1]);
	return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * albady_mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int albady_mycd(albady_info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
	albady_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
	dir = albady_getenv(info, "HOME=");
	if (!dir)
	chdir_ret = /* TODO: what should this be? */
	chdir((dir = albady_getenv(info, "PWD=")) ? dir : "/");
	else
	chdir_ret = chdir(dir);
	}
	else if (albady_strcmp(info->argv[1], "-") == 0)
	{
	if (!albady_getenv(info, "OLDPWD="))
	{
	albady_puts(s);
	albady_putchar('\n');
	return (1);
	}
	albady_puts(albady_getenv(info, "OLDPWD=")), albady_putchar('\n');
	chdir_ret = /* TODO: what should this be? */
	chdir((dir = albady_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
	chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1)
	{
	albady_print_error(info, "can't cd to ");
	albady_eputs(info->argv[1]);
	albady_eputchar('\n');
	}
	else
	{
	albady_setenv(info, "OLDPWD", albady_getenv(info, "PWD="));
	albady_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 * albady_myhelp - displays help information
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int albady_myhelp(albady_info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	albady_puts("help call works. Function not yet implemented \n");
	if (0)
	albady_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
