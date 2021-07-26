#include "minishell.h"

void	general_state_processor(t_support_token **sup, char **env)
{
	t_token	*tmp;

	tmp = first_token((*sup)->token);
	if (((*sup)->chtype) == WHITESPACE)
		case_whitespace(sup, &tmp);
	else if (((*sup)->chtype) == DOLLAR)
		case_dollar(sup, env, &tmp);
	else if (((*sup)->chtype) == QUOTE)
		case_quote(sup);
	else if (((*sup)->chtype) == DQUOTE)
		case_dquote(sup);
	else if (((*sup)->chtype) == ESCAPE)
		((*sup)->state) = ESCAPE_S;
	else if (is_separator((*sup)->chtype))
		case_separator(sup, &tmp);
	else if (((*sup)->chtype) == CHAR_NULL)
		case_charnull_in_general(sup, &tmp);
	else
		case_general_char(sup, &tmp);
}

static void	dqoute2(t_token **tmp, t_support_token **sup, char **env)
{
	if ((*sup)->chtype == DOLLAR)
	{
		ft_dollar(tmp, env, sup);
		(*sup)->j++;
	}
	else if ((*sup)->chtype == CHAR_NULL)
		(*sup)->error = 1;
	else
	{
		(*tmp)->data[(*sup)->j++] = (*sup)->str[(*sup)->i];
		(*tmp)->type = DQUOTE;
	}
}

void	dquote_state_processor(t_support_token **sup, char **env)
{
	t_token	*tmp;

	tmp = first_token((*sup)->token);
	if ((*sup)->chtype == DQUOTE)
	{
		if ((*sup)->j == 0)
		{
			tmp->data[(*sup)->j++] = '\0';
			tmp->type = DQUOTE;
		}
		(*sup)->state = GENERAL_S;
	}
	else if ((*sup)->chtype == ESCAPE)
	{
		if ((*sup)->str[(*sup)->i + 1] == DOLLAR || \
				(*sup)->str[(*sup)->i + 1] == ESCAPE \
				|| (*sup)->str[(*sup)->i + 1] == DQUOTE)
			tmp->data[(*sup)->j++] = (*sup)->str[++(*sup)->i];
		else
			tmp->data[(*sup)->j++] = (*sup)->str[(*sup)->i];
	}
	else
		dqoute2(&tmp, sup, env);
}

void	quote_state_processor(t_support_token **sup)
{
	t_token	*tmp;

	tmp = first_token((*sup)->token);
	if (((*sup)->chtype) == QUOTE)
		((*sup)->state) = GENERAL_S;
	else if (((*sup)->chtype) == CHAR_NULL)
		(*sup)->error = 1;
	else
	{
		tmp->data[((*sup)->j)++] = (*sup)->str[(*sup)->i];
		tmp->type = QUOTE;
	}
}

void	escape_state_processor(t_support_token **sup)
{
	t_token	*tmp;

	tmp = first_token((*sup)->token);
	tmp->data[((*sup)->j)++] = (*sup)->str[(*sup)->i];
	((*sup)->state) = GENERAL_S;
}
