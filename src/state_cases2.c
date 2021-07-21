#include "minishell.h"

void	ft_dollar(t_token **token, char **env, t_support_token **sup)
{
	char	*tmp;
	char	*res;
	int		j;

	j = (*sup)->i;
	while((*sup)->str[++((*sup)->i)])
		if ((*sup)->str[(*sup)->i] != '_' && !ft_isalnum((*sup)->str[(*sup)->i]))
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
	free_del_str(res);
	free_del_str(tmp);
}
