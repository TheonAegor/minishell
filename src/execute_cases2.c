#include "minishell.h"

int	pipe_case(t_tree_node *head, t_simple_command **com)
{
	int	fd[2];

	pipe(fd);
	init_simple_command(com, head->left);
	(*com)->pipe_write = fd[1];
	execute_command(com);
	(*com)->pipe_read = fd[0];
	(*com)->pipe_write = NO_VAL;
	execute(head->right, com);
	return (1);
}
