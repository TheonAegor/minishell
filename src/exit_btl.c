#include "minishell.h"

extern t_all *all;

int checknum(char *str)
{
	int i;

	i = 0;
	while (str[i] != 0)
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '-')
			return (1);
		i++;
	}
	return (0);
}

void exit_blt()
{
	if (arraylen(all->argv) > 1)
		result_error("слишком много аргументов\n", NULL, 1);
	else
	{
		printf("exit\n");
		if (arraylen(all->argv) == 0)
			exit(all->exit_status);
		else if (checknum(all->argv[0]) == 1)
		{
			result_error("требуется числовой аргумент\n", all->argv[0], 2);
			printf("%s", all->error);
			exit(all->exit_status);
		}
		else
			exit((char)(ft_atoi(all->argv[0])));
		change_last_arg();
	}
}
