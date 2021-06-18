#include "minishell.h"

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

int ifstop(char c)
{
	if (c == ';' || c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

//1)понять сколько будет комманд (;  | )
//2)выделить под это память
//3)спарсить команду	
int		find_stop(char *str)
{
	int	i;

	i = -1;
	while(str[++i])
		if (ifstop(str[i]))
			return (i);	
	return (-1);
}

void	take_simple_command(char *str)
{
	int start;
	int end;
	char *full_command;

	start = 0;	
	full_command = ft_substr(str, start, find_stop(str) - 1);
	printf("full_command = %s\n", full_command);
}

void	ft_parser(char *str, char **env)
{
	int		i;
//	t_func_args *funcs_args;
	
	i = -1;
	str = ft_strtrim(str, " \t");
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
	printf("END: str = %s\n", str);
	take_simple_command(str);

// "", '', \, $, ;, >, >>, <
}
/*
int preparser(char *str)
{
	while(*str)
		if (|,; first || |,; double)
}
 */
