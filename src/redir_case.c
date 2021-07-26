#include "minishell.h"

static void	clean_up(t_simple_command **com)
{
	if ((*com)->redirect_in)
		free((*com)->redirect_in);
	if ((*com)->redirect_out)
		free((*com)->redirect_out);
	(*com)->redirect_in = NULL;
	(*com)->redirect_out = NULL;
	(*com)->save = NO_VAL;
}

static void	last_redir(t_tree_node *head, t_simple_command **com)
{
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
}

static void	work_with_args(t_simple_command **com, char ***tmp_arg, \
							char **tmp_cmd, int tmp_num_args)
{
	(*com)->arguments = *tmp_arg;
	(*com)->num_of_arguments = tmp_num_args;
	if ((*com)->command_name)
		free((*com)->command_name);
	(*com)->command_name = *tmp_cmd;
}

int	redir_cases(t_tree_node *head, t_simple_command **com)
{
	char	**tmp_arg;
	char	*tmp_cmd;
	int		num_redirs;
	int		tmp_num_args;

	init_simple_command(com, head->left);
	tmp_arg = (*com)->arguments;
	tmp_cmd = ft_strdup((*com)->command_name);
	tmp_num_args = (*com)->num_of_arguments;
	num_redirs = find_num_redir_in(head);
	while (head->right->type == GREATER || head->right->type == DGREATER || \
	head->right->type == LOWER || head->right->type == DLOWER)
		redir_middle(&head, com, num_redirs);
	work_with_args(com, &tmp_arg, &tmp_cmd, tmp_num_args);
	last_redir(head, com);
	if (head->right->type == PIPE && num_redirs == 0)
		pipe_case_no_init(com);
	else
		execute_command(com);
	clean_up(com);
	move_to_next_command(&head);
	if (head->right)
		execute(head->right, com);
	return (1);
}
