#include "minishell.h"

t_token	*init_token(int size)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	token->data = malloc(size+1);
	token->data[0] = 0;
	token->data[size] = 0;
	
	token->type = CHAR_NULL;
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

//	printf("inside implement\n");
	tmp = *last_token;
	while (tmp)
	{
		f(tmp);
		tmp = tmp->next;
	}
//	printf("end of implement\n");
}

t_token	*first_token(t_token *last_token)
{
	t_token		*tmp;

	tmp = last_token;
	while (tmp->next)
		tmp = tmp->next;
	return(tmp);
}

void		free_delete_all_tokens(t_token **last_token)
{
	t_token *tmp;
	t_token *tmp2;

	tmp = *last_token;
	while (tmp)
	{
		free(tmp->data);
		tmp->data = NULL;
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
		tmp2 = NULL;
	}
}
