#include "minishell.h"

int	is_end_of_command(int type)
{
	if (type == PIPE || type == SEMICOLON || type == GREATER || type == LOWER \
	|| type == CHAR_NULL || type == DGREATER || type == DLOWER)
		return (1);
	return (0);
}

void	init_right_side(t_token *this, t_tree_node **head)
{
	t_tree_node	*tmp;

	tmp = *head;
	while (tmp)
		tmp = tmp->right;
	tmp = init_tree_with_values(this->data, this->type);
}

void	init_left_side(t_token *this, t_tree_node **head)
{
	t_tree_node	*tmp;

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
