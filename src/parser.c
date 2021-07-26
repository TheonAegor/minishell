#include "minishell.h"

static int	def_token_type2(char c)
{
	if (c == GREATER)
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

static int	define_token_type(char c)
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
	else
		return (def_token_type2(c));
}

static void	init_sup_struct(char *str, t_support_token **sup)
{
	*sup = malloc(sizeof(t_support_token));
	(*sup)->i = -1;
	(*sup)->j = 0;
	(*sup)->str = ft_strdup(str);
	(*sup)->len = ft_strlen(str);
	(*sup)->token = init_token((*sup)->len);
	(*sup)->state = GENERAL_S;
	(*sup)->error = -1;
}

static void	middle_parser(t_support_token *sup, char *str, char **env)
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
}

t_token	*ft_parser(char *str, char **env)
{
	t_token			*tmp;
	t_support_token	*sup;

	init_sup_struct(str, &sup);
	tmp = sup->token;
	while (1)
	{
		middle_parser(sup, str, env);
		if (sup->error == 1)
		{
			free_delete_all_tokens(&sup->token);
			free_support_token(&sup);
			return (NULL);
		}
		if (sup->chtype == CHAR_NULL)
			break ;
	}
#ifdef PRINT
	implement_f_to_all_tokens(&(sup->token), print_token_data);
#endif
	tmp = sup->token;
	if (check_tokens(tmp) == -1)
	{
		free_delete_all_tokens(&sup->token);
		return (NULL);
	}
	free_support_token(&sup);
	return (tmp);
}
