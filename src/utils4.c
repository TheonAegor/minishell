#include "minishell.h"

extern t_all	*g_all;

void	change_last_arg(void)
{
	if (arraylen(g_all->argv) == 0)
		change_env("_", g_all->name);
	else
		change_env("_", g_all->argv[arraylen(g_all->argv) - 1]);
}

void	was_error(void)
{
	if (g_all->error_flag == 1)
		g_all->error_flag = 0;
	else
		g_all->exit_status = 0;
}

void	free_and_exit(char *msg)
{
	if (g_all->name != NULL)
		free(g_all->name);
	if (g_all->argv != NULL)
		arrayfree(g_all->argv);
	if (g_all->envp != NULL)
		arrayfree(g_all->envp);
	if (g_all->result != NULL)
		free(g_all->result);
	if (g_all->error != NULL)
		free(g_all->error);
	if (g_all->path != NULL)
		arrayfree(g_all->path);
	if (msg != NULL)
		printf("%s", msg);
	free(g_all);
	exit(g_all->exit_status);
}

void	swap(char ***envp, int j)
{
	char	*temp;

	temp = ft_strdup((*envp)[j]);
	free((*envp)[j]);
	(*envp)[j] = ft_strdup((*envp)[j + 1]);
	free((*envp)[j + 1]);
	(*envp)[j + 1] = ft_strdup(temp);
	free(temp);
}
