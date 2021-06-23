#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *str = strdup("ls -la -n | cat -e > 1");
	int	i = -1;
	t_token *token;
	t_tree_node *head;
	t_simple_command *command;
/*
	while(env[++i])
		printf("%s\n", env[i]);
*/
	command = malloc(sizeof(t_simple_command));
	printf("Original str = %s\n", str);
	token = ft_parser(str, env);
	head = grammar(token);
	implement_f_to_all_tree_nodes(head, print_node_data_type);
	printf("~~~~~before execute~~~~~\n");
	execute(head, &command);	
	return (1);
}
