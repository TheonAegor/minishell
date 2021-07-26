#include "minishell.h"

void	free_simple_command(t_simple_command **com)
{
	if (*com)
	{
		del_comm_name_args(com);
		if ((*com)->redirect_in)
			free((*com)->redirect_in);
		if ((*com)->redirect_out)
			free((*com)->redirect_out);
		(*com)->redirect_in = NULL;
		(*com)->redirect_out = NULL;
		(*com)->save = NO_VAL;
		/*
		free(*com);
		*/
	}
}

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
