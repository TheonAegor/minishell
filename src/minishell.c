#include "minishell.h"

t_all	*g_all;

static t_simple_command	*init_command()
{
	t_simple_command *command;

	command = malloc(sizeof(t_simple_command));
	command->num_of_arguments = 0;
	command->pipe_read = NO_VAL;
	command->pipe_write = NO_VAL;
	command->save = NO_VAL;
	command->redirect_in = NULL;
	command->redirect_out = NULL;
	return (command);
}

/* char **gnl(int fd) */
/* { */
/* 	char **strs; */
/* 	char *str; */
/* 	char buf[2]; */
/*  */
/* 	while (read(ft, buf, 1) == 1) */
/* 	{ */
/* 		if (buf[0] != '\n') */
/*  */
/* 	} */
/* } */
/*  */
/* void history_from_file() */
/* { */
/* 	int fd; */
/* 	char **str; */
/*  */
/* 	fd = open("./.minishell_history", O_RDWR || O_APPEND || O_CREAT || O_EXCL); */
/* 	str = gnl(fd); */
/* } */
/*  */

static void main_inits(t_simple_command **command, char **envp)
{
	g_all = malloc(sizeof(t_all));
	g_all->exec_flag = 0;
	rl_catch_signals = 0;
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	*command = init_command();
	init_all();
	g_all->envp = arraycpy(envp, arraylen(envp));
	g_all->exit_status = 0;
	change_env("_", "minishell");
	change_env("?", "0");
}

int main(int argc, char **argv, char **envp)
{
	char *str;
	t_token *token;
	t_tree_node *head;
	t_simple_command *command;
	(void) argc;

	main_inits(&command, envp);
	while (1 == 1)
	{
		str = readline("minishell$ ");
		if (str == NULL)
			free_and_exit("exit\n");
		if (str[0] == 0)
			continue;
		add_history(str);
		token = ft_parser(str, g_all->envp);
		if (token == NULL)
			free_and_exit("");
		free(str);
		if (token->type != CHAR_NULL)
		{
			head = grammar(token);
			free_delete_all_tokens(&token);
			execute(head, &command);
			g_all->exec_flag = 0;
		}
	}
	return (0);
}