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
	printf("\nthis->data == %s\n", this->data);
	if (tmp == NULL)
		printf("node is null inside init\n");
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
	if (*head == NULL)
		printf("head is null after inside init\n");
	else
		printf("head is NOT null after inside init\n");

//	printf("inside init_left\n");
//	print_node_data_type(head);
	printf("end of init_left\n");
}

void	grammar(t_token *p)
{
	t_tree_node *node;
	t_tree_node *save;
	t_tree_node *tmp;
	t_tree_node *head;

	t_token		*end;
	t_token		*start;
	t_token		*tmp2;
	int			flag;


	end = p;
	node = init_tree_with_values(end->data, end->type);;
	save = node;
	start = end;
	flag = 0;
	while (1)
	{
		end = end->next;
		if (is_end_of_command(end->type))
		{
			if (flag == 0)
			{
//				printf("\nhere1\n");
				head = init_tree_with_values(end->data, end->type);
				insert_node(&head, node);
				node = NULL;
				implement_f_to_all_tree_nodes(head, print_node_data_type);
				break;
			}
			else
			{
//				printf("\nhere2\n");
				tmp = init_tree_with_values(end->data, end->type);
				insert_node(&tmp, node);
				implement_f_to_all_tree_nodes(tmp, print_node_data_type);
				printf("\ntmp->type = %d\n",tmp->type);
				printf("\nchar_general = %d\n", CHAR_GENERAL);
				if (node == NULL)
					printf("node is null indisere here2\n");
				else
					insert_node(&head, tmp);
				node = NULL;
			}
			flag++;
		}
		if (end->type == CHAR_NULL)
		{
//			printf("end = null\n");
			break;
		}
//		printf("\nhere\n");
		init_left_side(end, &node);
//		printf("end  = next\n");
	}
	printf("\nbefore implement\n");
	implement_f_to_all_tree_nodes(head, print_node_data_type);
	/*
	print_node_data_type(node);
	print_node_data_type(node->left);
	*/
//	implement_f_to_all_tokens(&p, print_token_data);
}
