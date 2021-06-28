#include "libft.h"
#include "minishell.h"

extern t_signal signal_flags;

int get_path(t_all *all)
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

char **form_array(t_all *all, char *first_arg)
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

void sigint_ex(int sig)
{
	(void)sig;
	printf("123 ");
}

int exec_blt(t_all *all, char *first_arg)
{
	pid_t pid;
	char *fullpath;
	int i;
	int flag;
	int status;

	i = 0;
	flag = 0;
	all->argv = form_array(all, first_arg);
	pid = fork();
	get_path(all);
//	signal_flags.exec_flag = 1;
	if (pid == 0)
	{
		while (all->path[i] != NULL)
		{
			fullpath = ft_strjoin(all->path[i], all->name);
			if (execve(fullpath, all->argv, all->envp) != -1)
			{
				flag = 1;
				free(fullpath);
				break;
			}
			free(fullpath);
			i++;
		}
		if (flag == 0 && execve(all->name, all->argv, all->envp) == -1)
			exit(127);
		//		exit(0);
	}
	else
	{
	//	signal_flags.pid = pid;
		wait(&status);
		if (WIFEXITED(status) != 0)
		{
			if (WEXITSTATUS(status) != 0)
				all->error_flag = 1;
			all->exit_status = WEXITSTATUS(status);
		}
		if (all->exit_status == 127)
			result_error(all, "команда не найдена\n", NULL, 127);
	}
	if (arraylen(all->argv) == 1)
		change_env(all, "_", all->name);
	else
		change_env(all, "_", all->argv[arraylen(all->argv) - 1]);
	return(0);
}
