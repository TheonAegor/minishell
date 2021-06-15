#include "libft.h"
#include <stdio.h>

char	*ft_quot_single(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while(str[++(*i)])
		if (str[*i] == '\'')
			break;	
	tmp = ft_substr(str, j + 1, *i - j - 1);
	tmp2 = ft_substr(str, 0, j);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp2, tmp);
	tmp = ft_strjoin(tmp, tmp3);
	printf("%s\n", tmp);
	return (tmp);
}

char *ft_slash(char *str, int *i)
{
	char *tmp;
	char *tmp2;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + 1);	
	tmp = ft_strjoin(tmp, tmp2);
	++(*i);
	return(tmp);
}

char *ft_qout_double(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while(str[++(*i)])
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\'' || str[*i + 1] == '\\' || str[*i + 1] == '$'))
			str = ft_slash(str, i);
		if (str[*i] == '\"')
			break;	
	}
	tmp = ft_substr(str, j + 1, *i - j - 1);
	tmp2 = ft_substr(str, 0, j);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp2, tmp);
	tmp = ft_strjoin(tmp, tmp3);
	printf("%s\n", tmp);
	return (tmp);
}

char *ft_dollar(char *str, int *i, char **env)
{
	int j;
	int k;
	char *tmp;
	char *tmp2;
	char *tmp3;

	j = *i;
	while (str[++(*i)])
		if (str[*i] != '_' && !ft_isalnum(str[*i]))
			break;
	tmp = ft_substr(str, j + 1, *i - j - 1);	
	k = -1;
	while (env[++k])
	{
		if (ft_strnstr(env[k], tmp, ft_strlen(tmp)))
		{
			tmp2 = ft_split(env[k], '=')[0];
			if (ft_strncmp(tmp2, tmp, ft_strlen(tmp2)) == 0) 
			{
				tmp = ft_strdup(ft_split(env[k], '=')[1]);
				break;
			}
		}
	}
	tmp2 = ft_substr(str, 0, j);
	tmp3 = ft_strdup(str + *i);
	tmp = ft_strjoin(tmp2, tmp);
	tmp = ft_strjoin(tmp, tmp3);
	printf("tmp = %s\n", tmp);
	return (tmp);
}

void	ft_parser(char *str, char **env)
{
	int		i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			str = ft_quot_single(str, &i);
		if (str[i] == '\\')
			str = ft_slash(str, &i);
		if (str[i] == '\"')
			str = ft_qout_double(str, &i);
		if (str[i] == '$')
			str = ft_dollar(str, &i, env);
	}

// "", '', \, $, ;, >, >>, <
}
/*
int preparser(char *str)
{
	while(*str)
		if (|,; first || |,; double)
}
 */

int main(int argc, char **argv, char **env)
{
	char *str = strdup("co$USER mma'n\\n'\"dkj");
	int	i = -1;
/*
	while(env[++i])
		printf("%s\n", env[i]);
*/
	printf("Original str = %s\n", str);
	ft_parser(str, env);
	
	return (1);
}
