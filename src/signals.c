#include "minishell.h"

extern t_all *g_all;

void sigint(int sig)
{
	(void)sig;
	if (g_all->exec_flag == 0)
	{
		g_all->exit_status = 130;
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void sigquit(int sig)
{
	(void)sig;
}
