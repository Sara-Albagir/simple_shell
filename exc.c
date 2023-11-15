#include "shell.h"

/**
* exe - excutive function.
* @cmd: functions command.
* @vecar: the arguments vector.
* Return: an int.
*/

int exe(char **cmd, char **vecar)
{
	pid_t child;
	int posit;

	child = fork();
	if (child == 0)
	{
		if (execve(cmd[0], cmd, environ) == -1)
		{
			perror(vecar[0]);
<<<<<<< HEAD
			_stringfreeing(cmd);
			exit(127);
		}
	}
	else
	{
		waitpid(child, &posit, 0);
		_stringfreeing(cmd);

	}
	return (WEXITSTATUS(posit));
=======
				_stringfreeing(cmd);
			exit(127);
		}
	}
		else
		{
			waitpid(child, &posit, 0);
				_stringfreeing(cmd);

		}
		return (WEXITSTATUS(posit));
>>>>>>> 04a8ff5c299496c09a303dfa5582e929918062ef
}
