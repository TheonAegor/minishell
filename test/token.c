#include "minishell.h"

t_token	*init_token(char *data)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	token->data = data;
	token->next = NULL;
	return (token);
}

void	add_token_front(t_token **last_token, t_token *new_token)
{
	t_token *tmp;

	tmp = *last_token;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new_token;
}

void	implement_f_to_all_tokens(t_token **last_token,void (*f)()) 
{
	t_token		*tmp;

	tmp = *last_token;
	while (tmp)
	{
		f(tmp);
		tmp = tmp->next;
	}
}
