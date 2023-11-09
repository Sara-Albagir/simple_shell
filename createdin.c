#include "main.h"
/**
 * my_exit - exits shell
 * @ads: Structure contains potential args. maintains
 * const funct prototype.
 * Return: With a given exit status, exits
 * (0) if info.argv[0] != "exit"
 */
int my_exit(ads_t *ads)
{
	int customExitCheck;

	if (ads->argv[1])  /* Checkes If there is an exit arguement */
	{
		customExitCheck = _erratoi(ads->argv[1]);
		if (customExitCheck == -1)
		{
			ads->status = 2;
			_error(ads, "Illegal number: ");
			_puts(ads->argv[1]);
			_aputchar('\n');
			return (1);
		}
		ads->err_num = _erratoi(ads->argv[1]);
		return (-2);
	}
	ads->err_num = -1;
	return (-2);
}

/**
 * my_cd - cd the current directory process
 * @ads: Structure containing potential args. maintains
 * const function prototype.
 * Return: 0 Always
 */

int my_cd(ads_t *ads)
{
	char *a, *dir, buffer[1024];
	int dirch_ret;

	a = _getcwd(buffer, 1024);
	if (!a)
		puts("TODO: >>_getcwd failure emsg here<<\n");
	if (!ads->argv[1])
	{
		dir = gtenv(ads, "HOME=");
		if (!dir)
			dirch_ret = /* TODO: what should this be? */
				dirch((dir = gtenv(ads, "PWD=")) ? dir : "/");
		else
			dirch_ret = dirch(dir);
	}
	else if (_cmpstr(ads->argv[1], "-") == 0)
	{
		if (!gtenv(ads, "OLDPWD="))
		{
			_puts(a);
			_aputchar('\n');
			return (1);
		}
		_puts(gtenv(ads, "OLDPWD=")), _aputchar('\n');
		dirch_ret = /* TODO: what should this be? */
			dirch((dir = gtenv(ads, "OLDPWD=")) ? dir : "/");
	}
	else
		dirch_ret = dirch(ads->argv[1]);
	if (dirch_ret == -1)
	{
		_error(ads, "can't cd to ");
		_puts(ads->argv[1]), _aputchar('\n');
	}
	else
	{
		_envset(ads, "OLDPWD", gtenv(ads, "PWD="));
		_envset(ads, "PWD", _getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - cd the current dir of the process
 * @ads: The Struct contains potential arguments. To maintain
 * const function prototype.
 * Return: 0 Always
 */
int my_help(ads_t *ads)
{
	puts("help call works. Function not yet implemented \n");
	return (0);
}
