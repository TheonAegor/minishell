#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

enum token_type {
	CHAR_GENERAL = -1,
	ESCAPE = '\\',
	QUOTE = '\'',
	DQUOTE = '\"',
	DOLLAR = '$',
	SEMICOLON = ';',
	PIPE = '|',
	GREATER = '>',
	LOWER = '<',
	WHITESPACE = ' ',
	TAB = '\t',
	NEWLINE = '\n',
	CHAR_NULL = 0,

	TOKEN = -1,
};

enum state {
	GENERAL_S,
	QUOTE_S,
	DQUOTE_S,
	ESCAPE_S,
};

enum gram_types {
	CMD,
	ARG,
};

typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct	s_simple_command
{
	int		num_of_arguments;
	char	*command_name;
	char	**arguments;
}	t_simple_command;

typedef struct	s_tree_node
{
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	char				*data;
	int					type;
} t_tree_node;

t_token			*init_token(int size);
t_token			*first_token(t_token *last_token);
t_token			*ft_parser(char *str, char **env);
void		    add_token_front(t_token **last_token, t_token *new_token);
void		    implement_f_to_all_tokens(t_token **last_token,void (*f)());
void			grammar(t_token *p);
void			print_token_data(t_token *token);
void			print_node_data_type(t_tree_node *n);
t_tree_node     *init_tree_with_values(char *data, int type);
t_tree_node		*init_tree_node(int size);
int		        implement_f_to_all_tree_nodes(t_tree_node *n,void (*f)());
void	        insert_node(t_tree_node **head, t_tree_node *new);
