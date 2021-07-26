#include "minishell.h"

t_tree_node	*init_tree_node(int	size)
{
	t_tree_node	*node;

	node = malloc(sizeof(t_tree_node));
	node->data = malloc(size + 1);
	node->data[0] = 0;
	node->type = CHAR_NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_tree_node	*init_tree_with_values(char *data, int type)
{
	t_tree_node	*node;

	node = init_tree_node(ft_strlen(data));
	free(node->data);
	node->data = NULL;
	node->data = ft_strdup(data);
	node->type = type;
	return (node);
}

void	insert_node(t_tree_node **head, t_tree_node *new)
{
	if (new->type == CHAR_GENERAL)
	{
		while (*head)
			*head = (*head)->left;
		*head = new;
	}
	else
	{
		while (*head)
			*head = (*head)->left;
		*head = new;
	}
}

int	implement_f_to_all_tree_nodes(t_tree_node *n, void (*f)())
{
	if (n == NULL)
		return (0);
	f(n);
	implement_f_to_all_tree_nodes(n->left, f);
	implement_f_to_all_tree_nodes(n->right, f);
	return (1);
}
