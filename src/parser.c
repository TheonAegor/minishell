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

void	ft_dollar(t_token **token, int *i, char *str, char **env)
{
	t_token *tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;
	int		k;

	j = *i;
	while(str[++(*i)])
		if (str[*i] != '_' && !ft_isalnum(str[*i]))
			break;
	tmp2 = ft_substr(str, j + 1, *i - j - 1);	
	k = -1;
	while (env[++k])
	{
		if (ft_strnstr(env[k], tmp2, ft_strlen(tmp2)))
		{
			tmp3 = ft_split(env[k], '=')[0];
			if (ft_strncmp(tmp3, tmp2, ft_strlen(tmp2)) == 0) 
			{
				tmp2 = ft_strdup(ft_split(env[k], '=')[1]);
				break;
			}
		}
	}
	printf("env = %s\n", tmp2);
	add_token_front(token, init_token(ft_strlen(tmp2)));
	tmp = first_token(*token);
	tmp->data = tmp2;
	tmp->data[ft_strlen(tmp2)] = 0;
	tmp->type = DOLLAR;
	printf("tmp->data = %s\n", tmp->data);
}

t_token		*ft_parser(char *str, char **env)
{
	int		i;
	t_token *token;
	t_token *tmp;
	int		chtype;
	int		state;
	int		len;
	int		j;
	
	i = -1;
	j = 0;
	len = ft_strlen(str);
	state = GENERAL_S;
	token = init_token(len);
	tmp = token;
	while (1)
	{
		i++;
		chtype = define_token_type(str[i]);
		tmp = first_token(tmp);
		if (state == GENERAL_S)
		{
			if (chtype == CHAR_GENERAL)
			{
				tmp->data[j++] = str[i];	
				tmp->type = TOKEN;
			}
			else if (chtype == WHITESPACE)
			{
				if (j > 0)
				{
					tmp->data[j] = 0;
					add_token_front(&token, init_token(len - i));
					j = 0;
				}
//				printf("here");
			}
			else if (chtype == DOLLAR)
			{
				if (j > 0)
					tmp->data[j] = 0;
				ft_dollar(&token, &i, str, env);
				add_token_front(&token, init_token(len - i));
				j = 0;
			}
			else if (chtype == QUOTE)
			{
				if (j > 0)
					tmp->data[j] = 0;
				j = 0;
				add_token_front(&token, init_token(len - i));
				state = QUOTE_S;
			}
			else if (chtype == DQUOTE)
			{
				if (j > 0)
					tmp->data[j] = 0;
				j = 0;
				add_token_front(&token, init_token(len - i));
				state = DQUOTE_S;
			}
			else if (chtype == PIPE || chtype == SEMICOLON || chtype == GREATER || chtype == LOWER)
			{
				if (j > 0)
					tmp->data[j] = 0;
				add_token_front(&token, init_token(len - i));
				tmp->data[0] = chtype;
				tmp->data[1] = '\0';
				tmp->type = chtype;
				j = 0;
			}
			else if (chtype == ESCAPE)
			{
				if (j > 0)
					tmp->data[j] = 0;
				j = 0;
				add_token_front(&token, init_token(len - i));
				state = ESCAPE_S;
			}
			else if (chtype == CHAR_NULL)
			{
				printf("inside char_null\n");
				if (j > 0)
					tmp->data[j] = 0;
				j = 0;
				add_token_front(&token, init_token(1));
//				tmp = first_token(tmp);
				break;
			}
			else
			{
				tmp->data[j++] = chtype;	
				tmp->type = TOKEN;
			}
		}
		else if (state == QUOTE_S)
		{
			if (chtype == QUOTE)
			{
				state = GENERAL_S;
				add_token_front(&token, init_token(len - i));
				j = 0;
			}
			else
			{
				tmp->data[j++] = str[i]; 
				tmp->type = QUOTE;
			}
		}
		else if (state == DQUOTE_S)
		{
			tmp->data[j++] = str[i]; 
			if (chtype == DQUOTE)
			{
				add_token_front(&token, init_token(len - i));
				state = GENERAL_S;	
				j = 0;
			}
		}
	}
	implement_f_to_all_tokens(&token, print_token_data);

	return (token);
// "", '', \, $, ;, >, >>, <
}
/*
int preparser(char *str)
{
	while(*str)
		if (|,; first || |,; double)
}
 */
