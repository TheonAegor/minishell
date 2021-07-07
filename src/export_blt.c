#include "minishell.h"

int check_arg(char *str)
{
	int i;

	i = 0;
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '\0')
		return (1);
	while (str[i] != 0 && str[i] != '=')
	{
		if (str[i] < '0'  || (str[i] > '9' && str[i] < 'A') || (str[i] > 'Z' && str[i] != '_' && str[i] < 'a') || str[i] > 'z')
			return (1);
		i++;
	}
	return (0);
}

char **envp_sort(char **src)
{
	int i;
	int j;
	char **envp;
	char *temp;

	i = 0;
	envp = arraycpy(src, arraylen(src));
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[j + 1] != NULL)
		{
			if (ft_strncmp(envp[j], envp[j + 1], 1000) > 0)
			{
				temp = ft_strdup(envp[j]);
				free(envp[j]);
				envp[j] = ft_strdup(envp[j + 1]);
				free(envp[j + 1]);
				envp[j + 1] = ft_strdup(temp);
				free(temp);
			}
			j++;
		}
		i++;
	}
	return(envp);
}

void	export_blt(t_all *all)
{
	char **envp_cpy;
	char *equal;
	int check;
	int i;

	i = 0;
	envp_cpy = envp_sort(all->envp);
	all->result = NULL;
	if (arraylen(all->argv) == 0)
		while (envp_cpy[i] != NULL)
		{
			if (ft_strncmp(envp_cpy[i], "_=", 2) == 0)
			{
				i++;
				continue;
			}
			equal = ft_strchr(envp_cpy[i], '=');
			if (equal != NULL)
				*equal = '\0';
			all->result = stradd(all->result, "declare -x ");
			all->result = stradd(all->result, envp_cpy[i]);
			if (equal != NULL)
			{

				all->result = stradd(all->result, "=\"");
				all->result = stradd(all->result, equal + 1);
				all->result = stradd(all->result, "\"");
			}
			all->result = stradd(all->result, "\n");
			i++;
		}
	else
		while (all->argv[i] != NULL)
		{
			check = check_arg(all->argv[i]);
			if (check == 1)
				result_error(all, "это недопустимый идентификатор\n", all->argv[i], 1);
			else
				envadd(all, all->argv[i]);
			i++;
		}
	change_last_arg(all);
}
