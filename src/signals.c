#include "minishell.h"

extern t_signal signal_flags;

void sigint(int sig)
{
	(void)sig;
	if (signal_flags.exec_flag == 0)
	{
//		all->exit_status = 130;
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
