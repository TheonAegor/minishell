#ifndef MINISHELL_H
# define MINISHELL_H
# define PRINT

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define CD_DELETED_DIR "cd: ошибка определения текущего каталога: \
getcwd: нет доступа к родительским каталогам: \
Нет такого файла или каталога\n"
# define NO_FILE_OR_DIR "Нет такого файла или каталога\n"
# define IT_IS_NOT_DIR "Это не каталог\n"
# define TOO_MANY_ARGS "слишком много аргументов\n"
# define NO_HOME "Не задана переменная HOME\n"
# define QUIT "Выход (стек памяти сброшен на диск)"
# define NUM_NEEDED "требуется числовой аргумент\n"
# define INVALID_IDENT "это недопустимый идентификатор\n"
# define COMMAND_NOT_FOUND "команда не найдена\n"

enum e_token_type {
	CHAR_GENERAL = -1,
	ESCAPE = '\\',
	QUOTE = '\'',
	DQUOTE = '\"',
	DOLLAR = '$',
	SEMICOLON = ';',
	PIPE = '|',
	GREATER = '>',
	DGREATER,
	LOWER = '<',
	DLOWER,
	WHITESPACE = ' ',
	TTAB = '\t',
	NNEWLINE = '\n',
	CHAR_NULL = 0,
	TOKEN = -1,
	NO_VAL = -99,
	SKIP_LEFT,
};

enum e_state {
	GENERAL_S,
	QUOTE_S,
	DQUOTE_S,
	ESCAPE_S,
};

enum e_gram_types {
	CMD,
	ARG,
};

typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_simple_command
{
	int		num_of_arguments;
	char	*command_name;
	char	**arguments;
	char	**envp;
	char	*result;
	char	*error_log;
	int		pipe_read;
	int		pipe_write;
	int		save;
	char	*redirect_in;
	char	*redirect_out;
}	t_simple_command;

typedef struct s_all
{
	char				*name;
	char				**argv;
	char				**envp;
	char				*result;
	char				*error;
	char				**path;
	int					exit_status;
	int					error_flag;	
	int					exec_flag;
	t_simple_command	**command;
}				t_all;

typedef struct s_commands
{
	t_simple_command	**simple_commands;
}	t_commands;

typedef struct s_tree_node
{
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	char				*data;
	int					type;
}	t_tree_node;

typedef struct s_support_token
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
void			add_token_front(t_token **last_token, t_token *new_token);
void			implement_f_to_all_tokens(t_token **last_token, void (*f)());
t_tree_node		*grammar(t_token *p);
void			print_token_data(t_token *token);
void			print_node_data_type(t_tree_node *n);
t_tree_node		*init_tree_with_values(char *data, int type);
t_tree_node		*init_tree_node(int size);
int				implement_f_to_all_tree_nodes(t_tree_node *n, void (*f)());
void			insert_node(t_tree_node **head, t_tree_node *new);
void			insert(char *data, int type, t_tree_node **leaf);
void			insert_tree(t_tree_node *new, t_tree_node **leaf);
void			execute(t_tree_node *head, t_simple_command **com);
void			find_num_of_left_nodes(t_tree_node *head, int *count);
void			init_simple_command(t_simple_command **com, t_tree_node *head);
void			print_simple_command_info(t_simple_command *com);
int				del_comm_name_args(t_simple_command **com);
void			fill_redirect_in_info(t_simple_command **com,
					t_tree_node *head);
void			fill_redirect_out_info(t_simple_command **com,
					t_tree_node *head);
void			execute_command(t_simple_command **com);
int				error_manager(void);
void			ft_dollar(t_token **token, char **env, t_support_token **sup);
void			dquote_state_processor(t_support_token **sup, char **env);
void			quote_state_processor(t_support_token **sup);
void			escape_state_processor(t_support_token **sup);
void			general_state_processor(t_support_token **sup, char **env);
void			case_whitespace(t_support_token **sup, t_token **tmp);
void			case_dquote(t_support_token **sup);
void			case_quote(t_support_token **sup);
void			case_dollar(t_support_token **sup, char **env, t_token **tmp);
void			case_separator(t_support_token **sup, t_token **tmp);
void			case_charnull_in_general(t_support_token **sup, t_token **tmp);
void			case_general_char(t_support_token **sup, t_token **tmp);
int				pipe_case(t_tree_node *head, t_simple_command **com);
int				redir_cases(t_tree_node *head, t_simple_command **com);
int				dgreater_case(t_tree_node *head, t_simple_command **com);
int				lower_case(t_tree_node *head, t_simple_command **com);
int				dlower_case(t_tree_node *head, t_simple_command **com);
int				semicolon_case(t_tree_node *head, t_simple_command **com);
int				null_case(t_tree_node *head, t_simple_command **com);
int				is_separator(int chtype);
void			free_delete_all_tokens(t_token **last_token);
void			free_support_token(t_support_token **sup);
void			free_array(char **arr);
void			free_del_str(char *str);
void			free_del_all_nodes(t_tree_node **head);
void			case_lower_greater(t_support_token **sup, t_token **tmp);
void			move_to_next_command(t_tree_node **node);
int				read_from_pipe(t_simple_command **com);
int				redirect_out(t_simple_command **com);
int				write_in_pipe(t_simple_command **com);
void			clear_simple_command(t_simple_command **com);
void			swap(char ***envp, int j);
int				strncmp_mix(const char *s1, const char *s2, size_t n);
void			sigint(int sig);
void			sigquit(int sig);
char			**arraycpy(char **src, int len);
int				arraylen(char **array);
void			result_error(char *error, char *arg, int exit_status);
char			*stradd(char *dst, char *str);
char			**arrayadd(char **src, char *str);
void			arrayfree(char **array);
void			envadd(char *new_str);
void			change_env(char *key, char *data);
void			change_last_arg(void);
void			pwd_blt(void);
void			env_blt(void);
void			export_blt(void);
void			cd_blt(void);
void			echo_blt(void);
void			unset_blt(void);
void			exit_blt(void);
int				exec_blt(void);
void			do_func(t_simple_command *com);
void			init_all(void);
void			was_error(void);
int				change_env_error(int exit_status);
void			free_and_exit(char *msg);
void			free_all(void);
int				redirect_in(t_simple_command **command);
int				is_end_of_command(int type);
int				check_tokens(t_token *tok);
int				find_num_redir_in(t_tree_node *head);
int				pipe_case_no_init(t_simple_command **com);
void			redir_middle(t_tree_node **head, \
		t_simple_command **com, int num_redirs);
int				mywexitstatus(int status);
int				mywtermsig(int status);
int				mywifsignaled(int status);
int				mywifexited(int status);
void			free_simple_command(t_simple_command **com);
#endif
