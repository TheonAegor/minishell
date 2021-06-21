#include "libft.h"
#include "minishell.h"

int env_blt(t_all *all)
{
	int i;
	char *newline;
	char *oldresult;

	i = 0;
	all->result = NULL;
	while (all->envp[i] != NULL)
	{
		if (all->envp[i + 1] != NULL)
			newline = ft_strjoin(all->envp[i], "\n");
		else
			newline = ft_strdup(all->envp[i]);
		oldresult = ft_strjoin(all->result, newline);
		if (all->result != NULL)
		{
			free(all->result);
			all->result = ft_strdup(oldresult);
		}
		else
			all->result = ft_strdup(newline);
		free(newline);
		free(oldresult);
		i++;
	}
	return(1);
}
