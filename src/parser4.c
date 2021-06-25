#include "minishell.h"

void		case_separator(t_support_token **sup, t_token **tmp)
{
	t_token *tmp2;

	tmp2 = first_token(*tmp);
	if (((*sup)->j) > 0)
	{
		tmp2->data[((*sup)->j)] = 0;
		add_token_front(tmp, init_token(2));
		tmp2 = tmp2->next;
	}
	tmp2->data[0] = ((*sup)->chtype);
	tmp2->data[1] = '\0';
	tmp2->type = ((*sup)->chtype);
	((*sup)->j) = 0;
	add_token_front(tmp, init_token((*sup)->len - (*sup)->i));
}

void		case_charnull_in_general(t_support_token **sup, t_token **tmp)
{
	if (((*sup)->j) > 0)
	{
		(*tmp)->data[((*sup)->j)] = 0;
		add_token_front(tmp, init_token(1));
		((*sup)->j) = 0;
	}
}

void		case_general_char(t_support_token **sup, t_token **tmp)
{
	(*tmp)->data[((*sup)->j)++] = (*sup)->str[(*sup)->i];
	(*tmp)->type = TOKEN;
}
