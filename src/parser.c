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
	t_token *tmp;
	char	*tmp2;
	char	*tmp3;
	int		flag;
	int		j;
	int		k;

	j = *i;
	flag = 0;
	while(str[++(*i)])
		if (str[*i] != '_' && !ft_isalnum(str[*i]))
			break;
	(*i) = *i - 1;
//	printf("j = %d, *i = %d\n", j, *i);
	tmp2 = ft_substr(str, j + 1, *i - j);	
	k = -1;
	while (env[++k])
	{
		if (ft_strnstr(env[k], tmp2, ft_strlen(tmp2)))
		{
			tmp3 = ft_split(env[k], '=')[0];
			if (ft_strncmp(tmp3, tmp2, ft_strlen(tmp2)) == 0) 
			{
				tmp2 = ft_strdup(ft_split(env[k], '=')[1]);
				flag++;
				break;
			}
		}
	}
	if (flag == 0)
		tmp2 = ft_strdup("");
//	printf("tmp->data=%s\n", (*token)->data);
	(*token)->data = ft_strjoin((*token)->data, tmp2); 
	(*token)->type = DOLLAR;
	*n = *n + ft_strlen(tmp2) - 1;
//	printf("tmp->data=%s\n", (*token)->data);
//	printf("end\n");
//	printf("tmp->data = %s\n", tmp->data);
}

void		init_sup_struct(char *str,t_support_token **sup)
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
//		printf("sup->chtype = %d\n", sup->chtype);
		if ((sup->state) == GENERAL_S)
			general_state_processor(&sup, env);
		else if ((sup->state) == QUOTE_S)
			quote_state_processor(&sup);
		else if ((sup->state) == DQUOTE_S)
			dquote_state_processor(&sup, env);
		else if ((sup->state) == ESCAPE_S)
			escape_state_processor(&sup);
		if (sup->chtype == CHAR_NULL)
		{
//			printf("char_null break\n");
			break;
		}
//		printf("here\n");
	}
	printf("before implement print_token\n");
	implement_f_to_all_tokens(&(sup->token), print_token_data);

	return (sup->token);
// "", '', \, $, ;, >, >>, <
}
/*
int preparser(char *str)
{
	while(*str)
		if (|,; first || |,; double)
}
 */
