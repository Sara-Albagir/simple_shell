#include "main.h"

/**
 * _my_exit - exits shell
 * @ads: Structure contains potential args. maintains
 * const funct prototype.
 * Return: With a given exit status, exits
 * (0) if info.argv[0] != "exit"
 */
int _my_exit(ads_t *ads)
{
	int customExitCheck;

	if (ads->argv[1])  /* Checkes If there is an exit arguement */
	{
		customExitCheck = _erratoi(ads->argv[1]);
		if (customExitCheck == -1)
		{
			ads->status = 2;
			error_print(ads, "Illegal number: ");
			ef_puts(ads->argv[1]);
			ef_putchar('\n');
			return (1);
		}
		ads->err_num = _erratoi(ads->argv[1]);
		return (-2);
	}
	ads->err_num = -1;
	return (-2);
}

/**
 * _my_cds - cd the current directory process
 * @ads: Structure containing potential args. maintains
 * const function prototype.
 * Return: 0 Always
 */
int _my_cds(ads_t *ads)
{
	char *a, *dir, buffer[1024];
	int chdir_ret;

	a = getcwd(buffer, 1024);
	if (!a)
		puts("TODO: >>_getcwd failure emsg here<<\n");
	if (!ads->argv[1])
	{
		dir = _getenv(ads, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(ads, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(ads->argv[1], "-") == 0)
	{
		if (!_getenv(ads, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(ads, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(ads, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(ads->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(ads, "can't cd to ");
		ef_puts(ads->argv[1]), ef_putchar('\n');
	}
	else
	{
		_setenv(ads, "OLDPWD", _getenv(ads, "PWD="));
		_setenv(ads, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _my_help - cd the current dir of the process
 * @ads: The Struct contains potential arguments. To maintain
 * const function prototype.
 * Return: 0 Always
 */
int _my_help(ads_t *ads)
{
	char **arg_array;

	arg_array = ads->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* workaround temp unused_att */
	return (0);
}
