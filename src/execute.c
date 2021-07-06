#include "minishell.h"

void	execute(t_tree_node *head, t_simple_command **com)
{
	if (head->type == PIPE)
	{
		printf("| pipe\n");
		int	fd[2];

		pipe(fd);
		init_simple_command(com, head->left, 0);
		(*com)->pipe_write = fd[1];
		(*com)->pipe_read = NO_VAL;
		(*com)->save = NO_VAL;
		execute_command(*com);
		(*com)->pipe_read = fd[0];
		(*com)->pipe_write = NO_VAL;
		execute(head->right, com);
	}
	else if (head->type == GREATER)
	{
		printf("> greater\n");
//		printf("\tinside greater\n");
		fill_redirect_in_info(com, head->right);
		init_simple_command(com, head->left, 0);
		execute_command(*com);
		(*com)->redirect_in = NULL;
		move_to_next_command(&head);
		execute(head->right, com);
	}
	else if (head->type == DGREATER)
	{
		printf(">> command\n");
		fill_redirect_in_info(com, head->right);
		init_simple_command(com, head->left, 0);
		execute_command(*com);
		(*com)->redirect_in = NULL;
		move_to_next_command(&head);
		execute(head->right, com);
	}
	else if (head->type == LOWER)
	{
		printf("< lower \n");
//		printf("\tinside greater\n");
		fill_redirect_out_info(com, head->right);
		init_simple_command(com, head->left, 0);
		(*com)->save = LOWER;
		execute_command(*com);
		(*com)->save = NO_VAL;
		free((*com)->redirect_out);
		(*com)->redirect_out = NULL;
		move_to_next_command(&head);
		execute(head->right, com);
	}
	else if (head->type == DLOWER)
	{
		printf("<< dlower \n");
//		printf("\tinside greater\n");
		fill_redirect_out_info(com, head->right);
		init_simple_command(com, head->left, 0);
		(*com)->save = DLOWER;
		execute_command(*com);
		(*com)->save = NO_VAL;
		free((*com)->redirect_out);
		(*com)->redirect_out = NULL;
		move_to_next_command(&head);
		execute(head->right, com);
	}
	else if (head->type == SEMICOLON)
	{
		printf("; semicolon\n");
		init_simple_command(com, head->left, 0);
		execute_command(*com);
		clear_simple_command(com);
		execute(head->right, com);
	}
	else if (head->type == CHAR_NULL)
	{
		printf("0 char_null\n");
//		printf("\tinside chr null\n");
		init_simple_command(com, head->left, 0);
		execute_command(*com);
	}
}

void	print_simple_command_info(t_simple_command *com)
{
	int i;

	i = -1;
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
}
