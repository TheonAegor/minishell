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

char	*look_in_env(char **env, char *to_find)
{
	char	**tmp;
	char	*res;
	int		k;

	k = -1;
	res = ft_strdup("");
	while (env[++k])
	{
		if (ft_strnstr(env[k], to_find, ft_strlen(to_find)))
		{
			tmp = ft_split(env[k], '=');
			if (ft_strncmp(tmp[0], to_find, ft_strlen(to_find)) == 0)
			{
				free(res);
				res = ft_strdup(tmp[1]);
				break;
			}
		}
	}
	free_array(tmp);
	return (res);
}

void		free_del_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}
