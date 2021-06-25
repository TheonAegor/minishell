#include "minishell.h"

void	init_simple_command(t_simple_command **com, t_tree_node *head, int flag)
{
	int i;

//	printf("start of init_simple_command\n");
	if ((*com)->command_name == NULL)
	{
//		printf("com_name is null\n");
		(*com)->command_name = ft_strdup(head->data);
		find_num_of_left_nodes(head->left, &(*com)->num_of_arguments);
		(*com)->arguments = malloc(sizeof(char*)*(*com)->num_of_arguments + 1);
		init_simple_command(com, head->left, 1); 
	}
	else if ((*com)->arguments != NULL && flag == 0)
	{
//		printf("there are args\n");
		del_comm_name_args(com);
		init_simple_command(com, head, 0); 
	}
	else
	{
//		printf("else\n");
		i = 0;
		while (i < (*com)->num_of_arguments)
		{
			((*com)->arguments)[i] = strdup(head->data);	
			i++;
		}
//		print_simple_command_info(*com);
	}
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

void		execute_command(t_simple_command **com)
{
	printf("-----------inside execute command----------\n");
	print_simple_command_info(*com);
	printf("-----------end of execute command----------\n");
}
