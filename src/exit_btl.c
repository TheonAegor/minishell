#include "minishell.h"

extern t_all *g_all;

static int checknum(char *str)
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
	if (arraylen(g_all->argv) > 1 && checknum(g_all->argv[0]) == 0)
		result_error(TOO_MANY_ARGS, NULL, 1);
	else
	{
		printf("exit\n");
		if (arraylen(g_all->argv) == 0)
			free_and_exit(NULL);
		else if (checknum(g_all->argv[0]) == 1)
		{
			result_error(NUM_NEEDED, g_all->argv[0], 2);
			printf("%s", g_all->error);
			free_and_exit(NULL);
		}
		else
		{
			g_all->exit_status = (char)(ft_atoi(g_all->argv[0]));
			free_and_exit(NULL);
		}
		change_last_arg();
	}
}
