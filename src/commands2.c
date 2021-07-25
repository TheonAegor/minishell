#include "minishell.h"

void	clear_simple_command(t_simple_command **com)
{
	del_comm_name_args(com);
	(*com)->pipe_read = NO_VAL;
	(*com)->pipe_write = NO_VAL;
	(*com)->save = NO_VAL;
	if ((*com)->redirect_in != NULL)
	{
		free((*com)->redirect_in);
		(*com)->redirect_in = NULL;
	}
	if ((*com)->redirect_out != NULL)
	{
		free((*com)->redirect_in);
		(*com)->redirect_in = NULL;
	}
}

void	move_to_next_command(t_tree_node **node)
{
	if ((*node)->right)
		(*node) = (*node)->right;
}

void	fill_redirect_in_info(t_simple_command **com, t_tree_node *head)
{
	char	*tmp;

	tmp = NULL;
	if (!head || !head->left)
		return ;
	if ((*com)->redirect_in)
		tmp = (*com)->redirect_in;
	(*com)->redirect_in = ft_strdup(head->left->data);
	if (tmp)
		free(tmp);
}

void	fill_redirect_out_info(t_simple_command **com, t_tree_node *head)
{
	char	*tmp;

	tmp = NULL;
	if (!head || !head->left)
		return ;
	if ((*com)->redirect_out)
		tmp = (*com)->redirect_out;
	(*com)->redirect_out = ft_strdup(head->left->data);
	if (tmp)
		free(tmp);
}
