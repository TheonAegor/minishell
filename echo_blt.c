#include "libft.h"
#include "minishell.h"

int echo_blt(t_all *all)
{
	int i;
	char *temp;

	i = 1;
	if (arraylen(all->argv) == 1)
	{
		all->result = ft_strdup("");
		return(1);
	}
	all->result = ft_strdup("");
	while (all->argv[i] != NULL)
	{
		temp = ft_strjoin(all->result, all->argv[i]);
		free(all->result);
		all->result = ft_strdup(temp);
		free(temp);
		i++;
	}
	return (1);
}
