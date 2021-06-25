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
	char	*result;
	char	*error_log;
	int		pipe_read;
	int		pipe_write;
	char	*redirect_in;
	char	*redirect_out;
}	t_simple_command;

typedef struct	s_commands
{
	t_simple_command **simple_commands;
}	t_commands;

typedef struct	s_tree_node
{
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	char				*data;
	int					type;
} t_tree_node;

typedef struct	s_support_token
{
	t_token	*token;
	char	*str;
	int		len;
	int		state;
	int		chtype;
	int		i;
	int		j;
	int		error;
}	t_support_token;

t_token			*init_token(int size);
t_token			*first_token(t_token *last_token);
t_token			*ft_parser(char *str, char **env);
void		    add_token_front(t_token **last_token, t_token *new_token);
void		    implement_f_to_all_tokens(t_token **last_token,void (*f)());
t_tree_node		*grammar(t_token *p);
void			print_token_data(t_token *token);
void			print_node_data_type(t_tree_node *n);
t_tree_node     *init_tree_with_values(char *data, int type);
t_tree_node		*init_tree_node(int size);
int		        implement_f_to_all_tree_nodes(t_tree_node *n,void (*f)());
void	        insert_node(t_tree_node **head, t_tree_node *new);
void			insert(char *data, int type, t_tree_node **leaf);
void			insert_tree(t_tree_node *new, t_tree_node **leaf);
void			execute(t_tree_node *head, t_simple_command **com);
void            find_num_of_left_nodes(t_tree_node *head, int *count);
void			init_simple_command(t_simple_command **com, t_tree_node *head, int flag);
void		    print_simple_command_info(t_simple_command *com);
void		    del_comm_name_args(t_simple_command **com);
void   		    fill_redirect_in_info(t_simple_command **com, t_tree_node *head);
void   		    execute_command(t_simple_command **com);
int				error_manager();
void			ft_dollar(t_token **token, int *i, char *str, char **env, int *n);
void			dquote_state_processor(t_support_token **sup, char **env);
void			quote_state_processor(t_support_token **sup);
void			escape_state_processor(t_support_token **sup);
void			general_state_processor(t_support_token **sup, char **env);
void			case_whitespace(t_support_token **sup, t_token **tmp);
void			case_dquote(t_support_token **sup, t_token **tmp);
void			case_quote(t_support_token **sup, t_token **tmp);
void			case_dollar(t_support_token **sup, char **env, t_token **tmp);
void			case_separator(t_support_token **sup, t_token **tmp);
void			case_charnull_in_general(t_support_token **sup, t_token **tmp);
void			case_general_char(t_support_token **sup, t_token **tmp);
int				is_separator(int chtype);
void			free_delete_all_tokens(t_token **last_token);
void			free_support_token(t_support_token **sup);
void			free_array(char **arr);
char		    *look_in_env(char **env, char *to_find);
void			free_del_str(char *str);
void	        free_del_all_nodes(t_tree_node **head);
