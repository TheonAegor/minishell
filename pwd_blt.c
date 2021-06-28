#include "minishell.h"

void pwd_blt(t_all *all)
{
	all->result = NULL;
	all->result = getcwd(all->result, 0);
	all->result = stradd(all->result, "\n");
	change_last_arg(all);
	all->exit_status = 0;
}
