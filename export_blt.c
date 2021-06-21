#include "libft.h"
#include "minishell.h"

int	export_blt(t_all *all)
{
	char *temp;
	char **envp_cpy;
	char *equal;
	int i;

	i = 0;
	envp_cpy = arraycpy(all->envp, arraylen(all->envp));
	all->result = NULL;
	if (arraylen(all->argv) == 1)
		while (envp_cpy[i] != NULL)
		{
			equal = ft_strchr(envp_cpy[i], '=');
			if (equal != NULL)
				*equal = '\0';
			if (all->result == NULL)
				all->result = ft_strdup("declare -x ");
			else
				all->result = ft_strjoin(all->result, "declare -x ");
			temp = ft_strjoin(all->result, envp_cpy[i]);
			free(all->result);
			if (equal != NULL)
			{
				all->result = ft_strjoin(temp, "=\"");
				free(temp);
				temp = ft_strjoin(all->result, equal + 1);
				free(all->result);
				if (envp_cpy[i + 1] != NULL)
					all->result = ft_strjoin(temp, "\"\n");
				else
					all->result = ft_strjoin(temp, "\"");
			}
			else if (envp_cpy[i + 1] != NULL)
				all->result = ft_strjoin(temp, "\n");
			else
				all->result = ft_strdup(temp);
			free(temp);
			i++;
		}
	else
		while (all->argv[i + 1] != NULL)
		{	
			all->envp = arrayadd(all->envp, all->argv[i + 1]);
			i++;
		}
	return(1);
}
