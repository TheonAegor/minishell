#include "minishell.h"

void	dquote_state_processor(t_support_token **sup, char **env)
{
	t_token *tmp;

	tmp = first_token((*sup)->token);
	if ((*sup)->chtype == DQUOTE)
	{
		add_token_front(&(*sup)->token, init_token((*sup)->len - (*sup)->i));
		(*sup)->state = GENERAL_S;	
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

	tmp = first_token((*sup)->token);
	if (((*sup)->chtype) == QUOTE)
	{
		((*sup)->state) = GENERAL_S;
		add_token_front(&tmp, init_token(((*sup)->len) - (*sup)->i));
		((*sup)->j) = 0;
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
	if (((*sup)->chtype) == CHAR_GENERAL)
	{
		tmp->data[((*sup)->j)++] = (*sup)->str[(*sup)->i];
		tmp->type = TOKEN;
	}
	else if (((*sup)->chtype) == WHITESPACE)
	{	
//		printf("j = %d\n", j);
		if (((*sup)->j) > 0)
		{
			tmp->data[((*sup)->j)] = 0;
			add_token_front(&(*sup)->token, init_token(((*sup)->len) - (*sup)->i));
			((*sup)->j) = 0;
	//		printf("str in whitespace = %s\n", tmp->data);
		}
//		printf("here");
	}
	else if (((*sup)->chtype) == DOLLAR)
	{
		ft_dollar(&tmp, &(*sup)->i, (*sup)->str, env, &((*sup)->j));
		((*sup)->j)++;
	}
	else if (((*sup)->chtype) == QUOTE)
	{
		if (((*sup)->j) > 0)
		{
			tmp->data[((*sup)->j)] = 0;
			add_token_front(&tmp, init_token(((*sup)->len) - (*sup)->i));
			((*sup)->j) = 0;
		}
		((*sup)->state) = QUOTE_S;
	}
	else if (((*sup)->chtype) == DQUOTE)
	{
		if (((*sup)->j) > 0)
		{
			tmp->data[((*sup)->j)] = 0;
			((*sup)->j) = 0;
			add_token_front(&tmp, init_token(((*sup)->len) - (*sup)->i));
		}
		((*sup)->state) = DQUOTE_S;
	}
	else if (((*sup)->chtype) == ESCAPE)
	{
		((*sup)->state) = ESCAPE_S;
	}
	else if (((*sup)->chtype) == PIPE || ((*sup)->chtype) == SEMICOLON || ((*sup)->chtype) == GREATER || ((*sup)->chtype) == LOWER)
	{
		if (((*sup)->j) > 0)
			tmp->data[((*sup)->j)] = 0;
		add_token_front(&tmp, init_token(((*sup)->len) - (*sup)->i));
		tmp->data[0] = ((*sup)->chtype);
		tmp->data[1] = '\0';
		tmp->type = ((*sup)->chtype);
		((*sup)->j) = 0;
	}
	else if (((*sup)->chtype) == CHAR_NULL)
	{
//		printf("inside char_null\n");
		if (((*sup)->j) > 0)
		{
			tmp->data[((*sup)->j)] = 0;
			add_token_front(&tmp, init_token(1));
			((*sup)->j) = 0;
		}
//		(*sup)->token = first_token(tmp);
	}
	else
	{
		tmp->data[((*sup)->j)++] = ((*sup)->chtype);	
		tmp->type = TOKEN;
	}
}

void		escape_state_processor(t_support_token **sup)
{
	(*sup)->token->data[((*sup)->j)++] = (*sup)->str[(*sup)->i];
	((*sup)->state) = GENERAL_S;
}
