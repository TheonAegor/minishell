#include "minishell.h"

void	print_node_data_type(t_tree_node *n)
{
	if (n != NULL)
	{
		printf("node->data = %s\n", n->data);
		printf("node->type = %d\n", n->type);
	}
	else
		printf("n is null inside print_node_data_type\n");
}

void	insert(char *data, int type, t_tree_node **leaf)
{
	if (*leaf == NULL)
	{
		*leaf = malloc(sizeof(t_tree_node));
		(*leaf)->data = ft_strdup(data);
		(*leaf)->type = type;
		(*leaf)->left = NULL;
		(*leaf)->right = NULL;
	}
	else if (type == CHAR_GENERAL || type == DQUOTE \
			|| type == QUOTE || type == DOLLAR)
		insert(data, type, &(*leaf)->left);
	else
		insert(data, type, &(*leaf)->right);
}

void	insert_tree(t_tree_node *new, t_tree_node **leaf)
{
	if (*leaf == NULL)
		*leaf = new;
	else if (new->type == CHAR_GENERAL || new->type == DQUOTE \
			|| new->type == QUOTE)
		insert_tree(new, &(*leaf)->left);
	else
		insert_tree(new, &(*leaf)->right);
}

void	find_num_of_left_nodes(t_tree_node *head, int *count)
{
	if (head != NULL)
	{
		find_num_of_left_nodes(head->left, count);
		(*count)++;
	}
}

void	free_del_all_nodes(t_tree_node **head)
{
	if ((*head)->right == NULL && (*head)->left == NULL)
	{
		free((*head)->data);
		(*head)->data = NULL;
		free(*head);
		*head = NULL;
		return ;
	}
	if ((*head)->left)
		free_del_all_nodes(&(*head)->left);
	if ((*head)->right)
		free_del_all_nodes(&(*head)->right);
	free_del_all_nodes(head);
}
