#include "libft.h"
#include <stdio.h>

typedef struct	s_Simple_Command
{
	char *command_name;
	char **arguments;
	int	num_of_arguments;
	int	last_argument;

}	t_Simple_Command;

typedef struct	s_Command
{
	int					num_of_commands;
	t_Simple_Command	**simple_commands;
	int					*operations;
} t_Command;

char	*ft_qoute_single(char *str, int *i);
char	*ft_slash(char *str, int *i);
char	*ft_qout_double(char *str, int *i);
char	*ft_dollar(char *str, int *i, char **env);
int		ifstop(char c);
void	ft_parser(char *str, char **env);

