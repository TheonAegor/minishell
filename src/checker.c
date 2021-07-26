#include "minishell.h"

int	check_tokens(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	if (is_end_of_command(tmp->type))
		return (-1);
	while (tmp->next)
	{
		if (is_end_of_command(tmp->type) && tmp->type != CHAR_NULL)
		{
			if (tmp->next->type == CHAR_NULL)
				return (-1);
		}
		if (is_end_of_command(tmp->type) && is_end_of_command(tmp->next->type))
			return (-1);
		if (tmp->type == SEMICOLON && tmp->next->type == CHAR_NULL)
			return (-1);
		tmp = tmp->next;
	}
	return (1);
}
