#include "minishell.h"

int		is_end_of_command(int type)
{
	if (type == PIPE || type == SEMICOLON || type == GREATER || type == LOWER || type == CHAR_NULL)
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
//	printf("inside init_right\n");
//	print_node_data_type(head);
}

void	init_left_side(t_token *this, t_tree_node **head)
{
	t_tree_node *tmp;

	tmp = *head;
//	printf("\nthis->data == %s\n", this->data);
//	if (tmp == NULL)
//		printf("node is null inside init\n");
	if (this->type == CHAR_GENERAL)
	{
//		printf("inside general char\n");
		if (tmp != NULL)
		{
			while (tmp)
				tmp = tmp->left;
			tmp = init_tree_with_values(this->data, this->type);
		}
		else
			*head = init_tree_with_values(this->data, this->type);
	}
	/*
	if (*head == NULL)
		printf("head is null after inside init\n");
	else
		printf("head is NOT null after inside init\n");
		*/

//	printf("inside init_left\n");
//	print_node_data_type(head);
//	printf("end of init_left\n");
}

t_tree_node	*grammar(t_token *p)
{
	t_tree_node *node;
	t_tree_node *save;
	t_tree_node *tmp;
	t_tree_node *head = NULL;

	t_token		*end;
	t_token		*start;
	t_token		*tmp2;
	int			flag;


	end = p;
	node = NULL;
	save = node;
	start = end;
	flag = 0;
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
//	printf("\nbefore implement\n");
//	implement_f_to_all_tree_nodes(head, print_node_data_type);
	return (head);
}
