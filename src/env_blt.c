#include "minishell.h"

extern t_all *all;

void env_blt()
{
	int i;

	i = 0;
	all->result = NULL;
	change_last_arg();
	while (all->envp[i] != NULL)
	{
		all->result = stradd(all->result, all->envp[i]);
		all->result = stradd(all->result, "\n");
		i++;
	}
}
