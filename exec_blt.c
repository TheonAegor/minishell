#include "libft.h"
#include "minishell.h"

int get_path(t_all *all)
{
	int i;

	i = 0;
	while (all->envp[i] != NULL)
	{
		if (ft_strncmp(all->envp[i], "PATH=", 5) == 0)
			all->path = ft_split(ft_strchr(all->envp[i], '=') + 1, ':');
		i++;
	}
	return(1);
}

int exec_blt(t_all *all)
{
	pid_t pid;
	char *exec_slash;
	char *exec_full;
	get_path(all);
	int i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (all->path[i] != NULL)
		{
			exec_slash = ft_strjoin(all->path[i], "/");
			exec_full = ft_strjoin(exec_slash, all->name);
			if (execve(exec_full, all->argv, all->envp) != -1)
			{
				free(exec_slash);
				free(exec_full);
				break;
			}
			free(exec_slash);
			free(exec_full);
			i++;
		}
		if (execve(all->name, all->argv, all->envp) == -1)
			printf("Команда не найдена\n");
		exit(0);
	}
	else
		wait(0);
	return(0);
}
