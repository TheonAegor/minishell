#include "minishell.h"

void	execute(t_tree_node *head, t_simple_command **com)
{
	if (head->type == PIPE)
		pipe_case(head, com);
	else if (head->type == GREATER)
		greater_case(head, com);
	else if (head->type == DGREATER)
		dgreater_case(head, com);
	else if (head->type == LOWER)
		lower_case(head, com);
	else if (head->type == DLOWER)
		dlower_case(head, com);
	else if (head->type == SEMICOLON)
		semicolon_case(head, com);
	else if (head->type == CHAR_NULL)
		null_case(head, com);
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
