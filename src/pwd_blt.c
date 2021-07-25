#include "minishell.h"

extern t_all	*g_all;

void	pwd_blt(void)
{
	g_all->result = NULL;
	g_all->result = getcwd(g_all->result, 0);
	g_all->result = stradd(g_all->result, "\n");
	change_last_arg();
	g_all->exit_status = 0;
}
