#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/**
 * showPrompt - initializes the command prompt
 * return: void has no return value
 */
int showPrompt(void)
{
	char *cmds[100], buffer[100], *tmp;
	int num_cmds = 0, i = 0, flag, rc = 0, endingWithPlus = 0;

	int breakString(void), numCmndsToFork = num_cmds, j = i - 2;

	while (!rc)
	{
		printf("\n./command_line_interpreter%% ");
		fgets(buffer, 512, stdin);

		for (i = 0; buffer[i] != '\0'; i++)
			if (buffer[i] == '+')
				flag++;
		for (; j >= 0; j--)
		{
			if (buffer[j] == ' ')
				continue;
			else if (buffer[j] == '+')
			{
				endingWithPlus = 1;
				break;
			}
			else
				break;
		}
		tmp = strtok(buffer, "+");
		while (tmp)
		{
			cmds[num_cmds] = tmp;
			num_cmds++;
			tmp = strtok(NULL, "+");
		}
		if (flag == 0)
		{
			if ((rc = breakString(buffer)) == 101)
			{
				break;
				exit(1);
			}
		}
		else
		{
			if (endingWithPlus == 0)
			{
				numCmndsToFork = num_cmds - 1;
				if ((rc = breakString(cmds[num_cmds - 1])) == 101)
				{
					break;
					exit(1);
				}
			}
			for (i = 0; i < numCmndsToFork; i++)
			{
				int ret;

				if ((ret = fork()) > 0)
				{
				}
				else if (ret == 0)
				{
					if (breakString(cmds[i]) == 101)
					{
						exit(0);
					}
					break;
				}
				else
				{
					char error_message[30] = "An error has occurred\n";

					write(STDERR_FILENO, error_message, strlen(error_message));
				}
			}
		}
	}
	return (0);
}
/**
 * BreakCommand - loop control statement used to
 * terminate the loop.
 *
 * @str: array of characters
 * Return:int
 */
int breakCommand(char *str)
{
	char *tmp, *subcmds[1000], buffer[1000], *subnew[1000];
	int num_subcmds = 0, out, flag1 = 0, j = 0, loc = 0, i, savedJ, flag2 = 0;

	strcpy(buffer, str);
	tmp = strtok(buffer, " \n\t");

	while (tmp)
	{
		subcmds[num_subcmds] = tmp;
		num_subcmds++;
		tmp = strtok(NULL, " \n\t");
	}
	subcmds[j] = NULL;

	if (num_subcmds > 1)
	{
		for (j = 0; j < num_subcmds; j++)
		{
			if (strcmp(subcmds[j], ">") == 0)
			{
				loc = j;
				flag1 = 1;
				break;
			}
		}
		if (flag1 == 1)
		{
			for (j = 0; j < loc; j++)
			{
				subnew[j] = subcmds[j];
			}
		}
		subnew[loc] = NULL;
	}
	if (flag1 != 1)
		for (j = 0; j < num_subcmds; j++)
		{
			i = strlen(subcmds[j]) - 1;

			if (subcmds[j][i] == '>')
			{
				subcmds[j][i] = '\0';
				flag2 = 1;
				savedJ = j;
			}
		}
	if (flag2 == 1)
	{
		for (j = 0; j <= savedJ; j++)
		{
			subnew[j] = subcmds[j];
		}
		subnew[savedJ + 1] = NULL;
	}
	if (flag1 == 1)
	{
		close(STDOUT_FILENO);
		out = open(subcmds[loc + 1], O_RDWR | O_CREAT, 0666);
		if (out < 0)
		{
			char error_message[30] = "An error has occurred\n";

			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(0);
		}
		dup2(out, STDOUT_FILENO);
		if (execvp(subnew[0], subnew) < 0)
		{
			char error_message[30] = "An error has occurred\n";

			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(101);
		}
		close(out);
		return (101);
	}
	else if (flag2 == 1)
	{
		close(STDERR_FILENO);
		out = open(subcmds[savedJ + 1], O_RDWR | O_CREAT, 0666);

		if (out < 0)
		{
			char error_message[30] = "An error has occurred\n";

			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(0);
		}
		dup2(out, STDOUT_FILENO);
		if (execvp(subnew[0], subnew) < 0)
		{
			char error_message[30] = "An error has occurred\n";

			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(101);
		}
		close(out);
		return (101);
	}
	else if (strcmp(subcmds[0], "cd") == 0)
	{
		int res;

		if (subcmds[1] != NULL)
			res = chdir(subcmds[1]);
		else
			res = chdir(getenv("HOME"));
		if (res == -1)
		{
			char error_message[30] = "An error has occurred\n";

			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(101);
		}
	}
	else if (strcmp(subcmds[0], "exit") == 0)
		exit(0);
	else if (strcmp(subcmds[0], "pwd") == 0)
	{
		if (subcmds[1] != NULL)
		{
			char error_message[30] = "An error has occurred\n";

			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(0);
		}
		else if (execvp(subcmds[0], subcmds) < 0)
		{
			char error_message[30] = "An error has occurred\n";

			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(101);
		}
	}
	else if (execvp(subcmds[0], subcmds) < 0)
	{
		char error_message[30] = "An error has occurred\n";

		write(STDERR_FILENO, error_message, strlen(error_message));
		return (1);
	}
	return (1);
}
int breakString(char *str)
{
	char *tmp, *subcmds[1000], buffer[1000];
	int num_subcmds = 0, waitpid(), j, status, x = WEXITSTATUS(status);

	strcpy(buffer, str);
	tmp = strtok(buffer, ";");

	while (tmp)
	{
		subcmds[num_subcmds] = tmp;
		num_subcmds++;
		tmp = strtok(NULL, ";");
	}
	for (j = 0; j < num_subcmds; j++)
	{
		int ret;

		if ((subcmds[j][0] == 'c' && subcmds[j][1] == 'd') == 1)
			breakCommand(subcmds[j]);
		else if (strcmp(subcmds[j], "exit") == 0)
			breakCommand(subcmds[j]);
		else
		{
			if ((ret = fork()) > 0)
			{
				waitpid(ret, &status, WUNTRACED);
				if (x == 101)
					return (101);
			}
			else if (ret == 0)
			{
				if (breakCommand(subcmds[j]) == 1)
				{
					exit(1);
					return (101);
				}
				else
					return (0);
				break;
			}
			else
			{
				char error_message[30] = "An error has occurred\n";

				write(STDERR_FILENO, error_message, strlen(error_message));
				exit(101);
			}
		}
	} return (0);
}
int main(int argc, char *argv[])
{
	char *cmds[1000], buffer[1000] = "test", *tmp, *fileToRead = "/no/such/file";
	int num_cmds = 0, i, flag, rc = 0, waitpid(), j;
	int endingWithPlus = 0, numCmndsToFork = num_cmds, batchMode = 0;
	FILE *new;
	FILE *fp;

	if (argc > 2)
	{
		char error_message[30] = "An error has occurred\n";

		write(STDERR_FILENO, error_message, strlen(error_message));
		exit(1);
	}
	else if (argc == 2)
	{
		batchMode = 1;
		fileToRead = argv[1];
	}

	if (batchMode == 1)
	{
		fp = fopen(fileToRead, "r");
		if (fp == NULL)
		{
			char error_message[30] = "An error has occurred\n";

			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(1);
		}
		new = fp;
	}
	else
		new = stdin;
	while (!feof(new))
	{
		num_cmds = 0;
		if (batchMode == 0)
			write(STDOUT_FILENO, "command_line_interpreter%", strlen("command_line_interpreter% "));
		if (batchMode == 1)
			fgets(buffer, 1000, fp);
		else
			fgets(buffer, 1000, stdin);

		strtok(buffer, "\n\r");

		if (batchMode == 1 && strcmp(buffer, "xyz") != 0)
		{
			write(STDOUT_FILENO, buffer, strlen(buffer));
			write(STDOUT_FILENO, "n", strlen("\n"));
			if (strcmp(buffer, "+") == 0)
				exit(0);
		}
		if (strcmp(buffer, "xyz") == 0)
			exit(0);
		for (i = 0; buffer[i] != '\0'; i++)
		{
			if (buffer[i] == '+')
				flag++;
		}
		if (strlen(buffer) == 0)
		{
			char error_message[30] = "An error has occurred\n";

			write(STDERR_FILENO, error_message, strlen(error_message));
		}
		j = i - 2;
		for (; j >= 0; j--)
		{
			if (buffer[j] == ' ')
				continue;
			else if (buffer[j] == '+')
			{
				endingWithPlus = 1;
				break;
			}
			else
				break;
		}
		tmp = strtok(buffer, "+");

		while (tmp)
		{
			cmds[num_cmds] = tmp;
			num_cmds++;
			tmp = strtok(NULL, "+");
		}

		if (flag == 0)
		{
			if ((rc = breakString(buffer)) == 101)
			{
				break;
				exit(0);
			}
		}
		else
		{
			if (endingWithPlus == 0)
			{
				numCmndsToFork = num_cmds - 1;
				if ((rc = breakString(cmds[num_cmds - 1])) == 101)
				{
					break;
					exit(0);
				}
			}
			for (i = numCmndsToFork - 1; i >= 0; i--)
			{
				int ret;

				if ((ret = fork()) > 0)
				{
					while (1)
					{
						int status;
						pid_t done = waitpid(ret, &status, WUNTRACED);

						if (done == -1)
						{
							if (errno == ECHILD)
								break;
						}
						else
						{
							int x = WEXITSTATUS(status);

							if (!WIFEXITED(x) || WEXITSTATUS(x) != 101)
								exit(0);
						}
					}
				}
				else if (ret == 0)
				{
					if (breakString(cmds[i]) == 101)
						exit(0);
				}
				else
				{
					char error_message[30] = "An error has occurred\n";

					write(STDERR_FILENO, error_message, strlen(error_message));

					exit(0);
				}
			}
		}
		strcpy(buffer, "xyz");
	}
	return (0);
}
