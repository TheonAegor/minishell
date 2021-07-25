#include "minishell.h"

extern t_all	*g_all;

static int	included_or_not(int i)
{
	int	j;

	j = 0;
	if (g_all->argv != 0)
	{
		while (g_all->argv[j] != NULL)
		{
			if (ft_strchr(g_all->argv[j], '=') != NULL)
			{
				j++;
				continue ;
			}
			if (ft_strncmp(g_all->envp[i], g_all->argv[j],
					ft_strlen(g_all->argv[j])) == 0)
				return (1);
			j++;
		}
	}
	return (0);
}

void	unset_blt(void)
{
	int		i;
	int		flag;
	char	**new_envp;

	new_envp = NULL;
	i = 0;
	while (g_all->envp[i] != NULL)
	{
		flag = 0;
		if (included_or_not(i) == 0)
			new_envp = arrayadd(new_envp, g_all->envp[i]);
		i++;
	}
	arrayfree(g_all->envp);
	g_all->envp = new_envp;
	change_last_arg();
}
