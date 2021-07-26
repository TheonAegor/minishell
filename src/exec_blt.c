#include "minishell.h"

extern t_all	*g_all;

static int	get_path(void)
{
	int	i;

	i = 0;
	while (g_all->envp[i] != NULL)
	{
		if (ft_strncmp(g_all->envp[i], "PATH=", 5) == 0)
			g_all->path = ft_split(ft_strchr(g_all->envp[i], '=') + 1, ':');
		i++;
	}
	i = 0;
	if (g_all->path != NULL)
	{
		while (g_all->path[i] != NULL)
		{
			g_all->path[i] = stradd(g_all->path[i], "/");
			g_all->path[i] = stradd(g_all->path[i], g_all->name);
			i++;
		}
	}
	return (1);
}

static char	**prepare_array(void)
{
	int		i;
	char	**array;

	i = 0;
	array = NULL;
	array = arrayadd(array, g_all->name);
	if (g_all->argv != NULL)
	{
		while (g_all->argv[i] != 0)
		{
			array = arrayadd(array, g_all->argv[i]);
			i++;
		}
		arrayfree(g_all->argv);
	}
	get_path();
	g_all->exec_flag = 1;
	return (array);
}

static void	parent(int *status)
{
	wait(status);
	if (mywifexited(*status) != 0)
	{
		if (mywexitstatus(*status) != 0)
			g_all->error_flag = 1;
		change_env_error(mywexitstatus(*status));
	}
	if (mywifsignaled(*status) != 0)
	{
		g_all->error_flag = 1;
		change_env_error(128 + mywtermsig(*status));
		if (mywtermsig(*status) == 3)
			printf(QUIT);
		printf("\n");
	}
	if (mywexitstatus(*status) == 127)
		result_error(COMMAND_NOT_FOUND, NULL, 127);
}

int	exec_blt(void)
{
	pid_t	pid;
	int		i;
	int		status;

	i = 0;
	g_all->argv = prepare_array();
	pid = fork();
	if (pid == 0)
	{
		if (g_all->path != NULL)
		{
			while (g_all->path[i] != NULL)
			{
				execve(g_all->path[i], g_all->argv, g_all->envp);
				i++;
			}
		}
		execve(g_all->name, g_all->argv, g_all->envp);
		exit(127);
	}
	else
		parent(&status);
	change_last_arg();
	return (0);
}
