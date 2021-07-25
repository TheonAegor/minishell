#include "minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
}

void	free_del_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}
