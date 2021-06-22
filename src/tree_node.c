#include "minishell.h"

t_tree_node		*init_tree_node(int	size)
{
	t_tree_node *node;

	node = malloc(sizeof(t_tree_node));
	node->data = malloc(size+1);
	node->data[0] = 0;
	node->type = CHAR_NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_tree_node		*init_tree_with_values(char *data, int type)
{
	t_tree_node *node;

	node = init_tree_node(ft_strlen(data));
	node->data = data;
	node->type = type;
	return (node);
}

void			implement_f_to_all_tree_nodes(t_tree_node *n,void (*f)())
{
	if (n == NULL)
		return (0);	
	f(n);
	n = n->left;
	implement_f_to_all_tree_nodes(n, f);
	n = n->right;
	implement_f_to_all_tree_nodes(n, f);
}

void			print_node_data_type(t_tree_node *n)
{
	printf("node->data = %s\n", n->data);
	printf("node->type = %d\n", n->type);
}
