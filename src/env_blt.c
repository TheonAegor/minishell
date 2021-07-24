#include "minishell.h"

extern t_all *g_all;

void env_blt()
{
	int i;

	i = 0;
	g_all->result = NULL;
	change_last_arg();
	while (g_all->envp[i] != NULL)
	{
		if (ft_strncmp(g_all->envp[i], "?=", 2) == 0)
		{
			i++;
			continue ;
		}
		g_all->result = stradd(g_all->result, g_all->envp[i]);
		g_all->result = stradd(g_all->result, "\n");
		i++;
	}
}
