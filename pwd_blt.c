#include "minishell.h"

int pwd_blt(t_all *all)
{
	all->result = NULL;
	all->result = getcwd(all->result, 0);
	return(1);
}
