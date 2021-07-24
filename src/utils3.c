#include "minishell.h"

extern t_all *g_all;

char *stradd(char *dst, char *str)
{
	int i;
	int j;
	char *new;

	i = 0;
	j = 0;
	new = malloc((ft_strlen(dst) + ft_strlen(str) + 1) * sizeof(char));
	if (dst != NULL)
		while (dst[i] != 0)
		{
			new[i] = dst[i];
			i++;
		}
	if (str != NULL)
		while (str[j] != 0)
		{
			new[i] = str[j];
			i++;
			j++;
		}
	new[i] = '\0';
	if (dst != NULL)
		free(dst);
	return (new);
}

int change_env_error(int exit_status)
{
	char *str_error;

	g_all->exit_status = exit_status;
	str_error = ft_itoa(exit_status);
	change_env("?", str_error);
	free(str_error);
	g_all->error_flag = 1;
	return (0);
}

void result_error(char *error, char *arg, int exit_status)
{
	g_all->error = stradd(g_all->error, "minishell: ");
	g_all->error = stradd(g_all->error, g_all->name);
	g_all->error = stradd(g_all->error, ": ");
	if (arg != NULL)
	{
		g_all->error = stradd(g_all->error, arg);
		g_all->error = stradd(g_all->error, ": ");
	}
	g_all->error = stradd(g_all->error, error);
	change_env_error(exit_status);
}

void change_env(char *key, char *data)
{
	char *complete;

	complete = NULL;
	complete = stradd(complete, key);
	complete = stradd(complete, "=");
	complete = stradd(complete, data);
	envadd(complete);
	free(complete);
}

