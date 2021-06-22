#include "minishell.h"

int		is_end_of_command(int type)
{
	if (type == PIPE || type == SEMICOLON || type == GREATER || type == LOWER || type == CHAR_NULL)
		return (1);
	return (0);
}

void	grammar(t_token *p)
{
	t_tree_node *node;
	t_token		*sep;
	t_token		*tmp;
	t_token		*tmp2;

	sep = p;
	tmp = sep;
	while (1)
	{
		if (is_end_of_command(sep->type))
		{
			printf("sep->data = %s\n", sep->data);
			break;
		}
		sep = sep->next;
	}
	printf("here\n");

	node = init_tree_node(ft_strlen(sep->data));
	node->data = sep->data;
	node->type = sep->type;

	node->left = init_tree_with_values(tmp->data, tmp->type);	

	implement_f_to_all_tree_nodes(node, print_node_data_type);
	/*
	print_node_data_type(node);
	print_node_data_type(node->left);
	*/
//	implement_f_to_all_tokens(&p, print_token_data);
}
