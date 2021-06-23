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
//	printf("\nstart insert_node...\n");
//	printf("before head = %s\n", (*head)->data);
	if (new->type == CHAR_GENERAL)
	{
		while(*head)
			*head = (*head)->left;
		*head = new; 
//		printf("before head = %s\n", (*head)->data);
	}
	else
	{
		while(*head)
		{
			*head = (*head)->left;
		}
		*head = new;
	}
//	printf("\n...end insert_node\n");
}

int			implement_f_to_all_tree_nodes(t_tree_node *n,void (*f)())
{
	if (n == NULL)
	{
//		printf("node is null");
		return (0);	
	}
	f(n);
//	printf("here\n");
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

void		insert(char *data, int type, t_tree_node **leaf)
{
//	printf("here\n");
	if (*leaf == NULL)
	{
		*leaf = malloc(sizeof(t_tree_node));
		(*leaf)->data = malloc(sizeof(char) * ft_strlen(data) +1);	
		(*leaf)->data = data;
//		(*leaf)->data[0] = 0;
		(*leaf)->type = type;
		(*leaf)->left = 0;
		(*leaf)->right = 0;

	}
	else if (type == CHAR_GENERAL)
		insert(data, type, &(*leaf)->left);
	else
		insert(data, type, &(*leaf)->right);
}

void		insert_tree(t_tree_node *new, t_tree_node **leaf)
{
	if (*leaf == NULL)
		*leaf = new;
	else if (new->type == CHAR_GENERAL)
		insert_tree(new, &(*leaf)->left);
	else
		insert_tree(new, &(*leaf)->right);
}

void			find_num_of_left_nodes(t_tree_node *head, int *count)
{
	if (head != NULL)
	{
		find_num_of_left_nodes(head->left, count);		
		(*count)++;
	}
}
