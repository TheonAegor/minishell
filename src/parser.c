#include "minishell.h"
void    print_token_data(t_token *token)
{
		printf("(");
		printf("%s", token->data);
//		printf("%d", token->type);
		printf(")");
}

int		define_token_type(char c)
{
	if (c == ESCAPE)
		return (ESCAPE);
	else if (c == QUOTE)
		return (QUOTE);
	else if (c == DQUOTE)
		return (DQUOTE);
	else if (c == DOLLAR)
		return (DOLLAR);
	else if (c == SEMICOLON)
		return (SEMICOLON);
	else if (c == PIPE)
		return (PIPE);
	else if (c == GREATER)
		return (GREATER);
	else if (c == LOWER)
		return (LOWER);
	else if (c == WHITESPACE)
		return (WHITESPACE);
	else if (c == TAB)
		return (TAB);
	else if (c == NEWLINE)
		return (NEWLINE);
	else if (c == CHAR_NULL)
		return (CHAR_NULL);
	else 
		return (CHAR_GENERAL);
}

void	ft_dollar(t_token **token, int *i, char *str, char **env, int *n)
{
	char	*tmp;
	char	*res;
	int		j;

	j = *i;
	while(str[++(*i)])
		if (str[*i] != '_' && !ft_isalnum(str[*i]))
			break;
	(*i) = *i - 1;
	tmp = ft_substr(str, j + 1, *i - j);	
	res = look_in_env(env, tmp);
	free_del_str(tmp);

	tmp = ft_strdup((*token)->data);
	free((*token)->data);
	(*token)->data = ft_strjoin(tmp, res); 
	(*token)->type = DOLLAR;
	*n = *n + ft_strlen(res) - 1;
	free_del_str(res);
	free_del_str(tmp);
}

static void	init_sup_struct(char *str,t_support_token **sup)
{
	(*sup)->i = -1;
	(*sup)->j = 0;
	(*sup)->str = ft_strdup(str);
	(*sup)->len = ft_strlen(str);
	(*sup)->token = init_token((*sup)->len);	
	(*sup)->state = GENERAL_S;
	(*sup)->error = -1;
}

t_token		*ft_parser(char *str, char **env)
{
	t_token *tmp;
	t_support_token *sup;

	sup = malloc(sizeof(t_support_token));
	init_sup_struct(str, &sup);
	tmp = sup->token;
	while (1)
	{
		sup->i++;
		(sup->chtype) = define_token_type(str[sup->i]);
		if ((sup->state) == GENERAL_S)
			general_state_processor(&sup, env);
		else if ((sup->state) == QUOTE_S)
			quote_state_processor(&sup);
		else if ((sup->state) == DQUOTE_S)
			dquote_state_processor(&sup, env);
		else if ((sup->state) == ESCAPE_S)
			escape_state_processor(&sup);
		if (sup->chtype == CHAR_NULL)
			break;
	}
	implement_f_to_all_tokens(&(sup->token), print_token_data);
	
	tmp = sup->token;
	free_support_token(&sup);
	return (tmp);
}
