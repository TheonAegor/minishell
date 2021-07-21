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

int greater_case(t_tree_node *head, t_simple_command **com)
{
    char *tmp_arg;
    char *tmp_cmd;

    init_simple_command(com, head->left);
    tmp_arg = ft_strdup((*com)->arguments[0]);
    tmp_cmd = ft_strdup((*com)->command_name);
    while (head->right->type == GREATER || head->right->type == DGREATER)
    {
        (*com)->arguments[0] = ft_strdup("");
        (*com)->command_name = ft_strdup("echo");

        (*com)->redirect_in = ft_strdup(head->right->left->data);
    	execute_command(com);
    	free((*com)->redirect_in);
    	(*com)->redirect_in = NULL;
//    	move_to_next_command(&head);
        head = head->right;
        printf("\t\theraaaaaaaae\n");
    }
    if (head->type == DGREATER)
        (*com)->save = 1;
    printf("\t\therrrrre\n");
    (*com)->redirect_in = ft_strdup(head->right->left->data);
    (*com)->arguments[0] = tmp_arg;
    (*com)->command_name = tmp_cmd;
    execute_command(com);
    free((*com)->redirect_in);
    (*com)->redirect_in = NULL;
    move_to_next_command(&head);
    (*com)->save = NO_VAL;
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