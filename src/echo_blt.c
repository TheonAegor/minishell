#include "libft.h"
#include "minishell.h"

int find_pos(t_all *all)
{
	int i;
	int j;

	i = 0;
	while (all->argv[i] != NULL)
	{
		j = 1;
		if (all->argv[i][0] != '-' || all->argv[i][1] != 'n')
			return (i);
		while (all->argv[i][j] != 0)
		{
			if (all->argv[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int check_n(t_all *all)
{
	int i;

	i = 1;
	if (all->argv != NULL)
	{
		if (all->argv[0][0] != '-' && all->argv[0][1] != 'n')
			return (0);
		while (all->argv[0][i] != 0)
		{
			if (all->argv[0][i] != 'n')
				return (0);
			i++;
		}
	}
	if (i == 1)
		return (0);
	return (1);
}

void echo_blt(t_all *all)
{
	int i;

	i = 0;
	if (all->argv != NULL)
	{
		if (check_n(all) == 1)
			i = find_pos(all);
		while (all->argv[i] != NULL)
		{
			all->result = stradd(all->result, all->argv[i]);
			if (all->argv[i + 1] != NULL)
				all->result = stradd(all->result, " ");
			i++;
		}
		if (check_n(all) == 0)
			all->result = stradd(all->result, "\n");
	}
	else
		all->result = stradd(all->result, "\n");
	change_last_arg(all);
	all->exit_status = 0;
}