#include "minishell.h"

int pipe_case(t_tree_node *head, t_simple_command **com)
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

int redir_cases(t_tree_node *head, t_simple_command **com)
{
    char 	*tmp_arg;
    char 	*tmp_cmd;
	int		num_redirs;

    init_simple_command(com, head->left);
    tmp_arg = ft_strdup((*com)->arguments[0]);
    tmp_cmd = ft_strdup((*com)->command_name);
	num_redirs = find_num_redir_in(head);
    while (head->right->type == GREATER || head->right->type == DGREATER || head->right->type == LOWER || head->right->type == DLOWER)
    {
		redir_middle(&head, com, num_redirs);
    }
	(*com)->arguments[0] = tmp_arg; 
	(*com)->command_name = tmp_cmd;
	if (head->type == LOWER || head->type == DLOWER)
	{
		fill_redirect_out_info(com, head->right);
		if (head->right->type == LOWER)
			(*com)->save = LOWER;
		if (head->right->type == DLOWER)
			(*com)->save = DLOWER;
	}
	else
	{
		fill_redirect_in_info(com, head->right);
    	if (head->type == DGREATER)
        	(*com)->save = 1;
	}

	if (head->right->type == PIPE && num_redirs == 0)
		pipe_case_no_init(head, com);
	else
	{
		execute_command(com);
	}

	if ((*com)->redirect_in)
 	   free((*com)->redirect_in);

	if ((*com)->redirect_out)
 	   free((*com)->redirect_out);

    (*com)->redirect_in = NULL;
    (*com)->redirect_out = NULL;

    (*com)->save = NO_VAL;
    move_to_next_command(&head);
    if (head->right)
        execute(head->right, com);
}

int dgreater_case(t_tree_node *head, t_simple_command **com)
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

int lower_case(t_tree_node *head, t_simple_command **com)
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

int dlower_case(t_tree_node *head, t_simple_command **com)
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

int semicolon_case(t_tree_node *head, t_simple_command **com)
{
	init_simple_command(com, head->left);
	execute_command(com);
	clear_simple_command(com);
	execute(head->right, com);
}

int null_case(t_tree_node *head, t_simple_command **com)
{
	init_simple_command(com, head->left);
	execute_command(com);
}