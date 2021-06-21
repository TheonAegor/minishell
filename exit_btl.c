#include "libft.h"
#include "minishell.h"

int checknum(char *str)
{
	int i;

	i = 0;
	while (str[i] != 0)
	{
		if ((str[i] < 48 || str[i] > 57) && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int exit_blt(t_all *all)
{
	if (arraylen(all->argv) > 2)
		printf("minishell: exit: слишком много аргументов\n");
	else if (arraylen(all->argv) == 1)
		exit(0);
	else if (checknum(all->argv[1]) == 0)
	{
		printf("minishell: exit: %s: требуется числовой аргумент\n", all->argv[1]);
		exit(2);
	}
	else
		exit((char)(ft_atoi(all->argv[1])));
	return(1);
}
