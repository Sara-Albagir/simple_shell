#include "main.h"

/**
 * _shellloop - fundumental shell loop.
 * @ads: parameter of type struct.
 * @arv: a parameter hold the argument vector.
 * Return: 1 or 0.
 */
int _shellloop(ads_t *ads, char **arv)
{
	ssize_t u = 0;
	int fin_built = 0;

	while (u != -1 && fin_built != -2)
	{
		clear_info(ads);
		if (interactive(ads))
			inp_strg("$ ");
		_eputchar(BUFF_FLUSH);
		u = get_input(ads);
		if (u != -1)
		{
			set_ads(ads, arv);
			fin_built = _command_builtfounder(ads);
			if (fin_built == -1)
				_cmdfounder(ads);
		}
		else if (interactive(ads))
			_printchar('\n');
		_adsfree(ads, 0);
	}
	write_history(ads);
	_adsfree(ads, 1);
	if (!interactive(ads) && ads->statuss)
		exit(ads->statuss);
	if (fin_built == -2)
	{
		if (ads->err_num == -1)
			exit(ads->statuss);
		exit(ads->err_num);
	}
	return (fin_built);
}

/**
 * _command_builtfounder - a function that check for command.
 * @ads: of type struct.
 * Return: 0 or 1 or -1 or -2.
 */
int _command_builtfounder(ads_t *ads)
{
	int j, fin_builtin = -1;
	tbl_built tblbuilt[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (j = 0; tblbuilt[j].type; j++)
		if (cmp_strg(ads->argo[0], tblbuilt[j].type) == 0)
		{
			ads->count_lin++;
			fin_builtin = tblbuilt[j].func(ads);
			break;
		}
	return (fin_builtin);
}

/**
 * _cmdfounder - function that search for a command.
 * @ads: of type struct.
 * Return: nune.
 */
void _cmdfounder(ads_t *ads)
{
	char *roat = NULL;
	int j, x;

	ads->roat = ads->argo[0];
	if (ads->line_count_flag == 1)
	{
		ads->count_lin++;
		ads->line_count_flag = 0;
	}
	for (j = 0, x = 0; ads->arr[j]; j++)
		if (!is_delim(ads->arr[j], " \t\n"))
			x++;
	if (!x)
		return;

	roat = _pathfounder(ads, env_getter(ads, "PATH="), ads->argo[0]);
	if (roat)
	{
		ads->roat = roat;
		_cmdfork(ads);
	}
	else
	{
		if ((interactive(ads) || env_getter(ads, "PATH=")
			|| ads->argo[0][0] == '/') && is_cmd(ads, ads->argo[0]))
			_cmdfork(ads);
		else if (*(ads->arr) != '\n')
		{
			ads->statuss = 127;
			_errormsg(ads, "not found\n");
		}
	}
}

/**
 * _cmdfork - function that runs cmd.
 * @ads: of type syruct.
 * Return: none.
 */
void _cmdfork(ads_t *ads)
{
	pid_t son_pid;

	son_pid = fork();
	if (son_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (son_pid == 0)
	{
		if (execve(ads->roat, ads->argo, environ_getter(ads)) == -1)
		{
			_adsfree(ads, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(ads->statuss));
		if (WIFEXITED(ads->statuss))
		{
			ads->statuss = WEXITSTATUS(ads->statuss);
			if (ads->statuss == 126)
				_errormsg(ads, "Permission denied\n");
		}
	}
}
