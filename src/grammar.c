#include "minishell.h"

int		is_end_of_command(int type)
{
	if (type == PIPE || type == SEMICOLON || type == GREATER || type == LOWER \
	|| type == CHAR_NULL || type == DGREATER || type == DLOWER)
		return (1);
	return (0);
}

void	init_right_side(t_token *this, t_tree_node **head)
{
	t_tree_node *tmp;

	tmp = *head;
	while(tmp)
		tmp = tmp->right;
	tmp = init_tree_with_values(this->data, this->type);
}

void	init_left_side(t_token *this, t_tree_node **head)
{
	t_tree_node *tmp;

	tmp = *head;
	if (this->type == CHAR_GENERAL)
	{
		if (tmp != NULL)
		{
			while (tmp)
				tmp = tmp->left;
			tmp = init_tree_with_values(this->data, this->type);
		}
		else
			*head = init_tree_with_values(this->data, this->type);
	}
}

t_tree_node	*grammar(t_token *p)
{
	t_tree_node *node;
	t_tree_node *save;
	t_tree_node *tmp;
	t_tree_node *head = NULL;

	t_token		*end;
	t_token		*tmp2;
	int			flag;

	end = p; //token

	node = NULL;
	save = node;

	flag = 0;

//	printf("\nstart of grammar\n");
	while (1)
	{
		if (is_end_of_command(end->type))
		{
			if (flag == 0)
			{
				insert(end->data, end->type, &head);
				insert_tree(node, &head);
			}
			else
			{
				tmp = init_tree_with_values(end->data, end->type);
				insert_tree(node, &tmp);
				insert_tree(tmp, &head);
			}
			if (end->type == CHAR_NULL)
				break;
			node = NULL;
			flag++;
		}
		else
			insert(end->data, end->type, &node);
		end = end->next;
	}
#ifdef PRINT
	implement_f_to_all_tree_nodes(head, print_node_data_type);
#endif
//	printf("end of grammar\n");
	return (head);
}
