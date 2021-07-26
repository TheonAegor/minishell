#include "minishell.h"

static void	add_tree(t_token *end, t_tree_node *node, t_tree_node *head)
{
	t_tree_node	*tmp;

	tmp = init_tree_with_values(end->data, end->type);
	insert_tree(node, &tmp);
	insert_tree(tmp, &head);
}

static int	middle_grammar(t_token **end, t_tree_node **node, \
		t_tree_node **head, int *flag)
{
	if (is_end_of_command((*end)->type))
	{
		if (*flag == 0)
		{
			insert((*end)->data, (*end)->type, head);
			insert_tree((*node), head);
		}
		else
			add_tree((*end), (*node), *head);
		if ((*end)->type == CHAR_NULL)
			return (0);
		(*node) = NULL;
		++*flag;
	}
	else
		insert((*end)->data, (*end)->type, node);
	(*end) = (*end)->next;
	return (1);
}

t_tree_node	*grammar(t_token *p)
{
	t_tree_node	*node;
	t_tree_node	*head;
	t_token		*end;
	int			flag;
	int			res;

	end = p;
	head = NULL;
	node = NULL;
	flag = 0;
	res = 1;
	while (res)
	{
		res = middle_grammar(&end, &node, &head, &flag);
	}
	return (head);
}
