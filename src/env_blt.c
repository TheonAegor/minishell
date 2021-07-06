#include "minishell.h"

void env_blt(t_all *all)
{
	int i;

	i = 0;
	all->result = NULL;
	change_last_arg(all);
	while (all->envp[i] != NULL)
	{
		all->result = stradd(all->result, all->envp[i]);
		all->result = stradd(all->result, "\n");
		i++;
	}
}
