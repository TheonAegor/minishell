#include "minishell.h"

void	execute(t_tree_node *head, t_simple_command **com)
{
	if (head->type == PIPE)
	{
		int	fd[2];

		pipe(fd);
		init_simple_command(com, head->left);
		(*com)->pipe_write = fd[1];

		execute_command(com);

		(*com)->pipe_read = fd[0];
		(*com)->pipe_write = NO_VAL;

		execute(head->right, com);
	}
	else if (head->type == GREATER)
	{
		init_simple_command(com, head->left);
		fill_redirect_in_info(com, head->right);
		execute_command(com);
		free((*com)->redirect_in);
		(*com)->redirect_in = NULL;
		move_to_next_command(&head);
		if (head->right)
			execute(head->right, com);
	}
	else if (head->type == DGREATER)
	{
		fill_redirect_in_info(com, head->right);
		init_simple_command(com, head->left);
		(*com)->save = 1;

		execute_command(com);

		free((*com)->redirect_in);
		(*com)->redirect_in = NULL;
		move_to_next_command(&head);
		if (head->right)
			execute(head->right, com);
	}
	else if (head->type == LOWER)
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
	else if (head->type == DLOWER)
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
	else if (head->type == SEMICOLON)
	{
		init_simple_command(com, head->left);
		execute_command(com);
		clear_simple_command(com);
		execute(head->right, com);
	}
	else if (head->type == CHAR_NULL)
	{
		init_simple_command(com, head->left);
		execute_command(com);
	}
}

void	print_simple_command_info(t_simple_command *com)
{
	int i;

	i = -1;
	printf("===============START_SIMPLE_COMMAND_INFO=============\n");
	printf("command name = %s\n", com->command_name);
	printf("num of args = %d\n", com->num_of_arguments);
	printf("save = %d\n", com->save);
	printf("pipe read = %d\n", com->pipe_read);
	printf("pipe write = %d\n", com->pipe_write);
	printf("redirect_in = %s\n", com->redirect_in);
	printf("redirect_out = %s\n", com->redirect_out);
	while (++i < com->num_of_arguments)
	{
		printf("%d argument = %s\n", i, com->arguments[i]);
	}
	printf("================END_SIMPLE_COMMAND_INFO==============\n");
}
