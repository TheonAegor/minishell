#include "minishell.h"

extern t_signal signal_flags;
extern t_all *all;

int get_path()
{
	int i;
	char *temp;

	i = 0;
	while (all->envp[i] != NULL)
	{
		if (ft_strncmp(all->envp[i], "PATH=", 5) == 0)
			all->path = ft_split(ft_strchr(all->envp[i], '=') + 1, ':');
		i++;
	}
	i = 0;
	while (all->path[i] != NULL)
	{
		temp = ft_strjoin(all->path[i], "/");
		free(all->path[i]);
		all->path[i] = temp;
		i++;
	}
	return(1);
}

char **form_array(char *first_arg)
{
	int i;
	char **array;

	i = 0;
	array = NULL;	
	array = arrayadd(array, first_arg);
	if (all->argv != NULL)
		while (all->argv[i] != 0)
		{
			array = arrayadd(array, all->argv[i]);
			i++;
		}
	return(array);
}

int exec_blt(char *first_arg)
{
	pid_t pid;
	char *fullpath;
	int i;
	int status;

	i = 0;
	all->argv = form_array(first_arg);
	get_path();
	signal_flags.exec_flag = 1;
	pid = fork();
	if (pid == 0)
	{
		while (all->path[i] != NULL)
		{
			fullpath = ft_strjoin(all->path[i], all->name);
			if (execve(fullpath, all->argv, all->envp) != -1)
			{
				free(fullpath);
				break;
			}
			free(fullpath);
			i++;
		}
		execve(all->name, all->argv, all->envp);
		exit(127);
	}
	else
	{
		wait(&status);
		signal_flags.pid = pid;
		if (WIFEXITED(status) != 0)
		{
			if (WEXITSTATUS(status) != 0)
				all->error_flag = 1;
			all->exit_status = WEXITSTATUS(status);
		}
		if (WIFSIGNALED(status) != 0)
		{
			all->error_flag = 1;
			all->exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == 3)
				printf("Выход (стек памяти сброшен на диск)");
			printf("\n");
		}
		if (all->exit_status == 127)
			result_error("команда не найдена\n", NULL, 127);
	}
	if (arraylen(all->argv) == 1)
		change_env("_", all->name);
	else
		change_env("_", all->argv[arraylen(all->argv) - 1]);
	return(0);
}
