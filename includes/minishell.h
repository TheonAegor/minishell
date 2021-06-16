#include "libft.h"
#include <stdio.h>

typedef struct	s_func_args
{
	char *func_name;
	char *args[];
}	t_funcs_args;

char	*ft_qoute_single(char *str, int *i);
char	*ft_slash(char *str, int *i);
char	*ft_qout_double(char *str, int *i);
char	*ft_dollar(char *str, int *i, char **env);
int		ifstop(char c);
void	ft_parser(char *str, char **env);

