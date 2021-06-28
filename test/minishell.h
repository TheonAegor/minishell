#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum token_type {
	WORD = 1,
	ESCAPE = '\\',
	QUOTE = '\'',
	DQOUTE = '\"',
	DOLLAR = '$',
	SEMICOLON = ';',
	PIPE = '|',
	GREATER = '>',
	LOWER = '<',
	WHITESPACE = ' ',
	TAB = '\t',
	NEWLINE = '\n'
};

enum state {
	GENERAL_S,
	QUOTE_S,
	DQUOTE_S,
	ESCAPE_S
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

t_token	*init_token(char *data);
void    add_token_front(t_token **last_token, t_token *new_token);
void    implement_f_to_all_tokens(t_token **last_token,void (*f)());
