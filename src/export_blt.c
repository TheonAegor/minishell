#include "minishell.h"

extern t_all *g_all;

static int check_arg(char *str)
{
	int i;

	i = 0;
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '\0' || str[0] == '=')
		return (1);
	while (str[i] != 0 && str[i] != '=')
	{
		if (str[i] < '0'  || (str[i] > '9' && str[i] < 'A') || (str[i] > 'Z' && str[i] != '_' && str[i] < 'a') || str[i] > 'z')
			return (1);
		i++;
	}
	return (0);
}

static char **envp_sort(char **src)
{
	int i;
	int j;
	char **envp;

	i = 0;
	envp = arraycpy(src, arraylen(src));
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[j + 1] != NULL)
		{
			if (ft_strncmp(envp[j], envp[j + 1], 1000) > 0)
				swap(&envp, j);
			j++;
		}
		i++;
	}
	return(envp);
}

static void add_args_to_envp(int i)
{
	while (g_all->argv[i] != NULL)
	{
		if (check_arg(g_all->argv[i]) == 1)
			result_error(INVALID_IDENT, g_all->argv[i], 1);
		else
			envadd(g_all->argv[i]);
		i++;
	}
}

static void add_env_to_result(char **envp_cpy, char *equal, int i)
{
	g_all->result = stradd(g_all->result, "declare -x ");
	g_all->result = stradd(g_all->result, envp_cpy[i]);
	if (equal != NULL)
	{

		g_all->result = stradd(g_all->result, "=\"");
		g_all->result = stradd(g_all->result, equal + 1);
		g_all->result = stradd(g_all->result, "\"");
	}
	g_all->result = stradd(g_all->result, "\n");
}

void	export_blt()
{
	char **envp_cpy;
	char *equal;
	int i;

	i = 0;
	envp_cpy = envp_sort(g_all->envp);
	g_all->result = NULL;
	if (arraylen(g_all->argv) == 0)
		while (envp_cpy[i] != NULL)
		{
			if (ft_strncmp(envp_cpy[i], "_=", 2) == 0 || ft_strncmp(envp_cpy[i], "?=", 2) == 0)
			{
				i++;
				continue;
			}
			equal = ft_strchr(envp_cpy[i], '=');
			if (equal != NULL)
				*equal = '\0';
			add_env_to_result(envp_cpy, equal, i);
			i++;
		}
	else
		add_args_to_envp(i);
	arrayfree(envp_cpy);
	change_last_arg();
}
