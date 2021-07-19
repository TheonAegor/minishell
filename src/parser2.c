#include "minishell.h"

void	dquote_state_processor(t_support_token **sup, char **env)
{
	t_token *tmp;

	tmp = first_token((*sup)->token);
	if ((*sup)->chtype == DQUOTE)
	{
//		add_token_front(&(*sup)->token, init_token((*sup)->len - (*sup)->i));
//		(*sup)->state = GENERAL_S;	
		(*sup)->j = 0;
	}
	else if ((*sup)->chtype == ESCAPE)
	{
		if ((*sup)->str[(*sup)->i + 1] == DOLLAR || (*sup)->str[(*sup)->i + 1] == ESCAPE || (*sup)->str[(*sup)->i + 1] == DQUOTE)
			tmp->data[(*sup)->j++] = (*sup)->str[++(*sup)->i];
		else
			tmp->data[(*sup)->j++] = (*sup)->str[(*sup)->i];
	}
	else if ((*sup)->chtype == DOLLAR)
	{
		ft_dollar(&tmp, &(*sup)->i, (*sup)->str, env, &(*sup)->j);
		(*sup)->j++;
	}
	else if ((*sup)->chtype == CHAR_NULL)
	{
		printf("dquote\n");
		(*sup)->error = 1;
	}
	else
	{
		tmp->data[(*sup)->j++] = (*sup)->str[(*sup)->i]; 
		tmp->type = DQUOTE;
	}
}

void		quote_state_processor(t_support_token **sup)
{
	t_token *tmp;

//	printf("in quote state proc, j = %d\n", (*sup)->j);
	tmp = first_token((*sup)->token);
	if (((*sup)->chtype) == QUOTE)
	{
		((*sup)->state) = GENERAL_S;
//		add_token_front(&tmp, init_token(((*sup)->len) - (*sup)->i));
//		((*sup)->j) = 0;
	}
	else if (((*sup)->chtype) == CHAR_NULL)
	{
		printf("quote\n");
		(*sup)->error = 1;
	}
	else
	{
		tmp->data[((*sup)->j)++] = (*sup)->str[(*sup)->i]; 
		tmp->type = QUOTE;
	}
}

void		general_state_processor(t_support_token **sup, char **env)
{
	t_token *tmp;

	tmp = first_token((*sup)->token);
	if (((*sup)->chtype) == WHITESPACE)
		case_whitespace(sup, &tmp);
	else if (((*sup)->chtype) == DOLLAR)
		case_dollar(sup, env, &tmp);
	else if (((*sup)->chtype) == QUOTE)
		case_quote(sup, &tmp);
	else if (((*sup)->chtype) == DQUOTE)
		case_dquote(sup, &tmp);
	else if (((*sup)->chtype) == ESCAPE)
		((*sup)->state) = ESCAPE_S;
	else if (is_separator((*sup)->chtype))
		case_separator(sup, &tmp);
	else if (((*sup)->chtype) == CHAR_NULL)
		case_charnull_in_general(sup, &tmp);
	else
		case_general_char(sup, &tmp);
}

void		escape_state_processor(t_support_token **sup)
{
	t_token *tmp;

//	printf("j = %d, i = %d, str[i] = %c\n", (*sup)->j, (*sup)->i, (*sup)->str[(*sup)->i]); 
	tmp = first_token((*sup)->token);
	tmp->data[((*sup)->j)++] = (*sup)->str[(*sup)->i];
	((*sup)->state) = GENERAL_S;
}
