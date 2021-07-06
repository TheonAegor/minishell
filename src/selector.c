#include "libft.h"
#include "mihishell.h"

void list_to_list(t_simple_command *pars, t_all *all)
{
	all->name = ft_strdup(pars->command_name);
	all->argv = ft_strdup(pars->arguments);
	all->result = ft_strdup(pars->result);
}

void selector(t_simple_command *pars, t_all *all)
{
	list_to_list(pars, all);
	if (strncmp_mix(all->name, "pwd", 4) == 0)
		pwd_blt(all);
	else if (strncmp_mix(all->name, "env", 4) == 0)
		env_blt(all);
	else if (strncmp_mix(all->name, "export", 7) == 0)
		export_blt(all);
	else if (strncmp_mix(all->name, "cd", 3) == 0)
		cd_blt(all);
	else if (strncmp_mix(all->name, "echo", 5) == 0)
		echo_blt(all);
	else if (strncmp_mix(all->name, "unset", 6) == 0)
		unset_blt(all);
	else if (strncmp_mix(all->name, "exit", 5) == 0)
		exit_blt(all);
	else
	{
		all->name = ft_strdup(bufsplit[0]);
		exec_blt(all, "./a.out");
		arrayfree(all.path);
	}
}
