#include "libft.h"
#include "minishell.h"

int check_pos(t_all *all)
{
	int i;
	int j;
	int pos;

	i = 0;
	pos = -1;
	while (all->argv[i] != 0)
	{
		if (pos != -1)
			return (pos);
		j = 0;
		while (all->argv[i][j] != 0)
		{
			if (!(j == 0 && all->argv[i][j] == '-') || !(j != 0 && all->argv[i][j] == 'n'))
				pos = j;
			j++;
		}
		i++;
	}
	return (pos);
}

/* int check_n(t_all *all) */
/* { */
/* 	int i; */
/* 	int flag; */
/*  */
/* 	i = 0; */
/* 	flag = 0; */
/* 	if (all->argv != null) */
/* 		while (all->argv[0][i] != 0) */
/* 		{ */
/*  */
/* 			i++; */
/* 		} */
/* } */

void echo_blt(t_all *all)
{
	int i;

	i = 0;
	if (all->argv != NULL)
	{
		if (ft_strncmp(all->argv[0], "-n", 3) == 0)
			i++;
		while (all->argv[i] != NULL)
		{
			all->result = stradd(all->result, all->argv[i]);
			if (all->argv[i + 1] != NULL)
				all->result = stradd(all->result, " ");
			i++;
		}
	}
	else
		all->result = stradd(all->result, "\n");
	if (all->argv != NULL && ft_strncmp(all->argv[0], "-n", 3) != 0)
		all->result = stradd(all->result, "\n");
	change_last_arg(all);
	all->exit_status = 0;
}
