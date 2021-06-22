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

void		insert_node(t_tree_node **head, t_tree_node *new)
{
	t_tree_node *tmp;
	t_tree_node *tmp2;

	printf("\nstart insert_node...\n");
	tmp = *head;
	tmp2 = (*head)->left;
	printf("tmp_addr = %p, head_addr = %p, tmp2_addr = %p\n", tmp, (*head), tmp2);
	if (new->type == CHAR_GENERAL)
	{
		while(tmp)
		{
			printf("ttttt\n");
			tmp = (*tmp).left;
		}
		printf("tmp_addr = %p, head->left_addr = %p, tmp2_addr = %p\n", &tmp, (*head)->left, &tmp2);
		if (tmp == NULL)
			printf("tmp == null\n"); 
		else
			printf("tmp != null\n"); 
		tmp = new; 
		if (tmp == NULL)
			printf("tmp is null\n");
		else
			printf("tmp is NOT null\n");
		print_node_data_type((*head)->left);
	}
	else
	{
		while(tmp)
			tmp = tmp->right;
		tmp = new;
	}
	printf("\n...end insert_node\n");
}

int			implement_f_to_all_tree_nodes(t_tree_node *n,void (*f)())
{
	if (n == NULL)
	{
//		printf("node is null");
		return (0);	
	}
	f(n);
	printf("here\n");
	implement_f_to_all_tree_nodes(n->left, f);
//	printf("after first rec, n = %s\n", n->data);
	implement_f_to_all_tree_nodes(n->right, f);
//	printf("after second rec\n");
}

void			print_node_data_type(t_tree_node *n)
{
	if (n != NULL)
	{
		printf("node->data = %s\n", n->data);
		printf("node->type = %d\n", n->type);
	}
	else
		printf("n is null inside print_node_data_type\n");
}
