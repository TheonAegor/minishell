#include "minishell.h"

void		clear_simple_command(t_simple_command **com)
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

void		move_to_next_command(t_tree_node **node)
{
	(*node) = (*node)->right;
}
