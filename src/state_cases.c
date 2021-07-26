#include "minishell.h"

void	case_whitespace(t_support_token **sup, t_token **tmp)
{
	if (((*sup)->j) > 0)
	{
		(*tmp)->data[((*sup)->j)] = 0;
		add_token_front(tmp, init_token(((*sup)->len) - (*sup)->i));
		((*sup)->j) = 0;
	}
}

void	case_dollar(t_support_token **sup, char **env, t_token **tmp)
{
	ft_dollar(tmp, env, sup);
	((*sup)->j)++;
}

void	case_quote(t_support_token **sup, t_token **tmp)
{
	((*sup)->state) = QUOTE_S;
}

void	case_dquote(t_support_token **sup, t_token **tmp)
{
	((*sup)->state) = DQUOTE_S;
}

int	is_separator(int chtype)
{
	if (chtype == PIPE || chtype == SEMICOLON \
			|| chtype == GREATER || chtype == LOWER)
		return (1);
	return (0);
}
