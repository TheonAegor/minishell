#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *str = strdup(" \\|   ls -la \'$USER      hell yeali\'      | cat -e   ");
	int	i = -1;
/*
	while(env[++i])
		printf("%s\n", env[i]);
*/
	printf("Original str = %s\n", str);
	ft_parser(str, env);
	
	return (1);
}
