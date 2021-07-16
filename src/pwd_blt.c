#include "minishell.h"

extern t_all *all;

void pwd_blt()
{
	all->result = NULL;
	all->result = getcwd(all->result, 0);
	all->result = stradd(all->result, "\n");
	change_last_arg();
	all->exit_status = 0;
}
