#include "minishell.h"

extern t_all *g_all;

void arrayfree(char **array)
{
	int i;

	i = 0;
	if (array == 0)
		return;
	while (array[i] != 0)
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}

int arraylen(char **array)
{
	int i;

	i = 0;
	if (array == 0)
		return (0);
	while (array[i] != 0)
		i++;
	return (i);
}

char **arraycpy(char **src, int len)
{
	int i;
	char **array;

	i = 0;
	if (len == NO_VAL)
		array = malloc(1 * sizeof(char *));
	else
		array = malloc((len + 1) * sizeof(char *));
	while (i < len)
	{
		array[i] = ft_strdup(src[i]);
		i++;
	}
	array[i] = 0;
	return(array);
}

char **arrayadd(char **src, char *str)
{
	int i;
	int len;
	char **array;

	len = arraylen(src);
	i = 0;
	array = malloc((len + 2) * sizeof(char *));
	if (src != NULL)
		while (src[i] != 0)
		{
			array[i] = ft_strdup(src[i]);
			i++;
		}
	array[i] = ft_strdup(str);
	array[i + 1] = 0;
	arrayfree(src);
	return(array);
}

void envadd(char *new_str)
{
	int i;
	char *equal;
	char *temp;

	i = 0;
	temp = ft_strdup(new_str);
	equal = ft_strchr(temp, '=');
	if (equal != NULL)
		*equal = '\0';
	while (equal != NULL && g_all->envp[i] != NULL)
	{
		if (ft_strncmp(g_all->envp[i], temp, ft_strlen(temp)) == 0)
		{
			free(g_all->envp[i]);
			g_all->envp[i] = ft_strdup(new_str);
			break;
		}
		i++;
	}
	if (equal != NULL)
		*equal = '=';
	free(temp);
	if (g_all->envp[i] == NULL)
		g_all->envp = arrayadd(g_all->envp, new_str);
}
