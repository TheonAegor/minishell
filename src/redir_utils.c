#include "minishell.h"

int     find_num_redir_in(t_tree_node *head)
{
    int res;

    res = 0;
    if (!head)
        return (-1);
    while (head && (head->type == GREATER || head->type == DGREATER || \
    head->type == LOWER || head->type == DLOWER))
    {
        if (head->type == GREATER || head->type == DGREATER)
            res++;
        head = head->right;
    }
    return (res);
}

int pipe_case_no_init(t_tree_node *head, t_simple_command **com)
{
    int	fd[2];

	pipe(fd);
	(*com)->pipe_write = fd[1];

	execute_command(com);

	(*com)->pipe_read = fd[0];
	(*com)->pipe_write = NO_VAL;
}

void    redir_middle(t_tree_node **p_head, t_simple_command **com, int num_redirs)
{
    t_tree_node *head;

    head = *p_head;
    if ((head->type == GREATER || head->type == DGREATER))
	{
		fill_redirect_in_info(com, head->right);
		if (num_redirs > 1)
		{
     	   (*com)->arguments[0] = ft_strdup("");
     	   (*com)->command_name = ft_strdup("echo");
			execute_command(com);
		}
	}
	if (head->type == LOWER || head->type == DLOWER)
	{
		fill_redirect_out_info(com, head->right);
		if (head->right->type == LOWER)
			(*com)->save = LOWER;
		if (head->right->type == DLOWER)
			(*com)->save = DLOWER;
	}
    *p_head = (*p_head)->right;
}