#include "albady_shell.h"

/**
 * albady_hsh - main shell loop
 * @info: the parameter & return albady_info_t struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int albady_hsh(albady_info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
	albady_clear_info(info);
	if (albady_interactive(info))
	albady_puts("$ ");
	albady_putchar(BUF_FLUSH);
	r = albady_get_input(info);
	if (r != -1)
	{
		albady_set_info(info, av);
		builtin_ret = albady_find_builtin(info);
		if (builtin_ret == -1)
		albady_find_cmd(info);
	}
	else if (albady_interactive(info))
	albady_putchar('\n');
	albady_free_info(info, 0);
	}
	albady_write_history(info);
	albady_free_info(info, 1);
	if (!albady_interactive(info) && info->status)
	exit(info->status);
	if (builtin_ret == -2)
	{
	if (info->err_num == -1)
	exit(info->status);
	exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * albady_find_builtin - finds a builtin command
 * @info: the parameter & return albady_info_t struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int albady_find_builtin(albady_info_t *info)
{
	int i, built_in_ret = -1;
	albady_builtin_table builtintbl[] = {
	{"exit", albady_myexit},
	{"env", albady_myenv},
	{"help", albady_myhelp},
	{"history", albady_myhistory},
	{"setenv", albady_mysetenv},
	{"unsetenv", albady_myunsetenv},
	{"cd", albady_mycd},
	{"alias", albady_myalias},
	{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
	if (albady_strcmp(info->argv[0], builtintbl[i].type) == 0)
	{
	info->line_count++;
	built_in_ret = builtintbl[i].func(info);
	break;
	}
	return (built_in_ret);
}

/**
 * albady_find_cmd - finds a command in PATH
 * @info: the parameter & return albady_info_t struct
 *
 * Return: void
 */
void albady_find_cmd(albady_info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
	info->line_count++;
	info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
	if (!albady_is_delim(info->arg[i], " \t\n"))
	k++;
	if (!k)
	return;

	path = albady_find_path(info, albady_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
	info->path = path;
	albady_fork_cmd(info);
	}
	else
	{
	if ((albady_interactive(info) || albady_getenv(info, "PATH=")
	|| info->argv[0][0] == '/') && albady_is_cmd(info, info->argv[0]))
	albady_fork_cmd(info);
	else if (*(info->arg) != '\n')
	{
		info->status = 127;
		albady_print_error(info, "not found\n");
	}
	}
}

/**
 * albady_fork_cmd - forks an exec thread to run cmd
 * @info: the parameter & return albady_info_t struct
 *
 * Return: void
 */
void albady_fork_cmd(albady_info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
	/* TODO: PUT ERROR FUNCTION */
	perror("Error:");
	return;
	}
	if (child_pid == 0)
	{
	if (execve(info->path, info->argv, albady_get_environ(info)) == -1)
	{
	albady_free_info(info, 1);
	if (errno == EACCES)
		exit(126);
		exit(1);
	}
	/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
	wait(&(info->status));
	if (WIFEXITED(info->status))
	{
		info->status = WEXITSTATUS(info->status);
		if (info->status == 126)
		albady_print_error(info, "Permission denied\n");
	}
	}
}
