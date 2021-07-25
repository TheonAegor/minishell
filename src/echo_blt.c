#include "minishell.h"

extern t_all	*g_all;

static int	find_pos(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_all->argv[i] != NULL)
	{
		j = 1;
		if (g_all->argv[i][0] != '-' || g_all->argv[i][1] != 'n')
			return (i);
		while (g_all->argv[i][j] != 0)
		{
			if (g_all->argv[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

static int	check_n(void)
{
	int	i;

	i = 1;
	if (g_all->argv != NULL)
	{
		if (g_all->argv[0][0] != '-' && g_all->argv[0][1] != 'n')
			return (0);
		while (g_all->argv[0][i] != 0)
		{
			if (g_all->argv[0][i] != 'n')
				return (0);
			i++;
		}
	}
	if (i == 1)
		return (0);
	return (1);
}

void	echo_blt(void)
{
	int	i;

	i = 0;
	if (g_all->argv != NULL)
	{
		if (check_n() == 1)
			i = find_pos();
		while (g_all->argv[i] != NULL)
		{
			g_all->result = stradd(g_all->result, g_all->argv[i]);
			if (g_all->argv[i + 1] != NULL)
				g_all->result = stradd(g_all->result, " ");
			i++;
		}
		if (check_n() == 0)
			g_all->result = stradd(g_all->result, "\n");
	}
	else
		g_all->result = stradd(g_all->result, "\n");
	change_last_arg();
	change_env_error(0);
}
