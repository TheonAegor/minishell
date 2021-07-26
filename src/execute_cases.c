#include "minishell.h"

int	dgreater_case(t_tree_node *head, t_simple_command **com)
{
	(*com)->redirect_out = strdup(head->left->data);
	init_simple_command(com, head->left);
	(*com)->save = 1;
	execute_command(com);
	free((*com)->redirect_in);
	(*com)->redirect_in = NULL;
	move_to_next_command(&head);
	if (head->right)
		execute(head->right, com);
}

int	lower_case(t_tree_node *head, t_simple_command **com)
{
	fill_redirect_out_info(com, head->right);
	init_simple_command(com, head->left);
	(*com)->save = LOWER;
	execute_command(com);
	free((*com)->redirect_out);
	(*com)->redirect_out = NULL;
	move_to_next_command(&head);
	if (head->right)
		execute(head->right, com);
}

int	dlower_case(t_tree_node *head, t_simple_command **com)
{
	fill_redirect_out_info(com, head->right);
	init_simple_command(com, head->left);
	(*com)->save = DLOWER;
	execute_command(com);
	(*com)->save = NO_VAL;
	free((*com)->redirect_out);
	(*com)->redirect_out = NULL;
	move_to_next_command(&head);
	execute(head->right, com);
}

int	semicolon_case(t_tree_node *head, t_simple_command **com)
{
	init_simple_command(com, head->left);
	execute_command(com);
	clear_simple_command(com);
	execute(head->right, com);
}

int	null_case(t_tree_node *head, t_simple_command **com)
{
	init_simple_command(com, head->left);
	execute_command(com);
	free_simple_command(com);
}
