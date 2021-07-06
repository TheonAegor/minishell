#include "minishell.h"

void unset_blt(t_all *all)
{
	int i;
	int j;
	int flag;
	char **new_envp;

	new_envp = NULL;
	i = 0;
	while (all->envp[i] != NULL)
	{
		j = 0;
		flag = 0;
		if (all->argv != 0)
			while (all->argv[j] != NULL)
			{
				if (ft_strncmp(all->envp[i], all->argv[j], ft_strlen(all->argv[j])) == 0)
				{
					flag = 1;
					break;
				}
				j++;
			}
		if (flag != 1)
			new_envp = arrayadd(new_envp, all->envp[i]);
		i++;
	}
	arrayfree(all->envp);
	all->envp = new_envp;
	change_last_arg(all);
}
