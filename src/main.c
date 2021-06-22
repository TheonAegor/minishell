#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *str = strdup("ls           | cat -e > 1");
	int	i = -1;
	t_token *token;
/*
	while(env[++i])
		printf("%s\n", env[i]);
*/
	printf("Original str = %s\n", str);
	token = ft_parser(str, env);
	grammar(token);
	
	return (1);
}
