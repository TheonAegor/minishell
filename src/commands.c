#include "minishell.h"

void	init_simple_command(t_simple_command **com, t_tree_node *head, int flag)
{
	int i;

//	printf("start of init_simple_command\n");
	if ((*com)->command_name == NULL)
	{
		if (flag == 1)
		{
			(*com)->pipe_read = NO_VAL;
			(*com)->pipe_write = NO_VAL;
			(*com)->save = NO_VAL;
			(*com)->redirect_in = NULL;
			(*com)->redirect_out = NULL;
		}

		(*com)->command_name = ft_strdup(head->data);
		find_num_of_left_nodes(head->left, &(*com)->num_of_arguments);
		(*com)->arguments = malloc(sizeof(char*)*(*com)->num_of_arguments + 1);
		init_simple_command(com, head->left, 1);
	}
	else if ((*com)->arguments != NULL && flag == 0)
	{
		del_comm_name_args(com);
		init_simple_command(com, head, 2);
	}
	else
	{
		i = 0;
		while (i < (*com)->num_of_arguments)
		{
			((*com)->arguments)[i++] = strdup(head->data);	
			head = head->left;
		}
	}
//	printf("end of init_simple_command\n");
}

void		del_comm_name_args(t_simple_command **com)
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
}

void		fill_redirect_in_info(t_simple_command **com, t_tree_node *head)
{
	(*com)->redirect_in = strdup(head->left->data);
}

void		fill_redirect_out_info(t_simple_command **com, t_tree_node *head)
{
	(*com)->redirect_out = strdup(head->left->data);
}

void		execute_command(t_simple_command **command)
{
	t_simple_command *com;

	com = *command;
//	printf("-----------inside execute command----------\n");
	print_simple_command_info(com);
	if (com->pipe_read != NO_VAL)
	{
		read_from_pipe(&com);
	}
	else if (com->redirect_out != NULL)
	{
		read_from_redirect(com);
	}
	else if (com->pipe_write != NO_VAL)
	{
		write_in_pipe(&com);
	}
	else
		do_func(com);
//	print_simple_command_info(com);
//	printf("-----------end of execute command----------\n");
}
