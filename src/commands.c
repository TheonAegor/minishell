#include "minishell.h"

int	del_comm_name_args(t_simple_command **com)
{
	int	i;

	i = -1;
	free((*com)->command_name);
	(*com)->command_name = NULL;
	while(++i < (*com)->num_of_arguments)
	{
		free(((*com)->arguments)[i]);	
		((*com)->arguments)[i] = NULL;	
	}
	free((*com)->arguments);
	(*com)->arguments = NULL;
	(*com)->num_of_arguments = 0;
	return (1);
}

static int	name_and_alloc_args(t_simple_command **com, t_tree_node *head)
{
	(*com)->command_name = ft_strdup(head->data);
	find_num_of_left_nodes(head->left, &(*com)->num_of_arguments);
	(*com)->arguments = malloc(sizeof(char*)*(*com)->num_of_arguments + 1);
	return (1);
}

static int	fill_arguments(t_simple_command **com, t_tree_node *head)
{
	int	i;

	i = 0;
	while (i < (*com)->num_of_arguments)
	{
		((*com)->arguments)[i++] = strdup(head->data);	
		head = head->left;
	}
	return (1);
}

void	init_simple_command(t_simple_command **command, t_tree_node *head)
{
	t_simple_command *com;

	com = *command;
	if (com->command_name != NULL)
		del_comm_name_args(&com);
	name_and_alloc_args(&com, head);
	fill_arguments(&com, head->left);
}

void		execute_command(t_simple_command **command)
{
	t_simple_command *com;

	com = *command;
//	printf("-----------inside execute command----------\n");
#ifdef PRINT
	print_simple_command_info(com);
#endif
	if (com->pipe_read != NO_VAL)
		read_from_pipe(&com);
	else if (com->redirect_out != NULL)
		redirect_out(&com);
	else if (com->pipe_write != NO_VAL)
		write_in_pipe(&com);
	else if (com->redirect_in != NULL)
	{
		printf("inside\n");
		redirect_in(&com);	
	}
	else
		do_func(com);
//	print_simple_command_info(com);
//	printf("-----------end of execute command----------\n");
}

void		fill_redirect_in_info(t_simple_command **com, t_tree_node *head)
{
	(*com)->redirect_in = strdup(head->left->data);
}

void		fill_redirect_out_info(t_simple_command **com, t_tree_node *head)
{
	(*com)->redirect_out = strdup(head->left->data);
}
