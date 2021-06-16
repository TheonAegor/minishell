#include "libft.h"
#include <stdio.h>

typedef struct	s_Simple_Command
{
	char *command_name;
	char **arguments;
	int	num_of_arguments;
	int	last_argument;

//	t_Simple_Command (*Simple_Command)(s_Simple_Command *self, char *command_name, int num_of_arguments);	
	void	(*insert_argument)(s_Simple_Command *self, char *argument);

}	t_Simple_Command;

void	insert_argument(s_Simple_Command *self, char *argument)
{
	(self->last_argument)++;
	(self->arguments)[self->last_argument] = ft_strdup(argument);	
};
/*
t_Simple_Command Simple_Command(s_Simple_Command *self, char *command_name, int num_of_arguments)
{
	self = malloc(sizeof(t_Simple_Command));

	self->arguments = malloc(sizeof(*char)*num_of_arguments);
	self->num_of_arguments = num_of_arguments;
	self->last_argument = 0;
	return (self);
};
*/

typedef struct	s_Command
{
	int	num_of_commands;
	t_Simple_Command **simple_commands;
}

char	*ft_qoute_single(char *str, int *i);
char	*ft_slash(char *str, int *i);
char	*ft_qout_double(char *str, int *i);
char	*ft_dollar(char *str, int *i, char **env);
int		ifstop(char c);
void	ft_parser(char *str, char **env);

