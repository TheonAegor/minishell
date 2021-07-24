#include "minishell.h"

static char	*look_in_env(char **env, char *to_find)
{
	char	**tmp;
	char	*res;
	int		check;
	int		k;

	k = -1;
    if (ft_strlen(to_find) == 0)
    {
	    res = ft_strdup("$");
        return (res);
    }
	res = ft_strdup("");
	while (env[++k])
	{
		if (ft_strnstr(env[k], to_find, ft_strlen(to_find)))
		{
			tmp = ft_split(env[k], '=');
			check = ft_strncmp(tmp[0], to_find, ft_strlen(to_find)); 
			if (check == 0)
			{
				free(res);
				res = ft_strdup(tmp[1]);
				free_array(tmp);
				break;
			}
		}
	}
	return (res);
}

void	ft_dollar(t_token **token, char **env, t_support_token **sup)
{
	char	*tmp;
	char	*res;
	int		j;

	j = (*sup)->i;
	while((*sup)->str[++((*sup)->i)])
		if ((*sup)->str[(*sup)->i] != '_' && !ft_isalnum((*sup)->str[(*sup)->i]) \
        && (*sup)->str[(*sup)->i] != '?')
			break;
	((*sup)->i) = (*sup)->i - 1;
	tmp = ft_substr((*sup)->str, j + 1, (*sup)->i - j);	
	res = look_in_env(env, tmp);

	free_del_str(tmp);
	tmp = ft_strdup((*token)->data);
	free((*token)->data);
	(*token)->data = ft_strjoin(tmp, res); 
	(*token)->type = DOLLAR;
	(*sup)->j = (*sup)->j + ft_strlen(res) - 1;
	if ((*sup)->j == -1)
		(*sup)->j = 0;
	free_del_str(res);
	free_del_str(tmp);
}
