#include "minishell.h"

extern t_all	*g_all;

void	init_all(void)
{
	g_all->name = NULL;
	g_all->argv = NULL;
	g_all->result = NULL;
	g_all->error = NULL;
	g_all->path = NULL;
}

void	free_all(void)
{
	if (g_all->name != NULL)
		free(g_all->name);
	if (g_all->argv != NULL)
		arrayfree(g_all->argv);
	if (g_all->result != NULL)
		free(g_all->result);
	if (g_all->error != NULL)
		free(g_all->error);
	if (g_all->path != NULL)
		arrayfree(g_all->path);
	init_all();
}

void	list_to_list(t_simple_command *com)
{
	init_all();
	g_all->name = ft_strdup(com->command_name);
	if (com->num_of_arguments != 0)
		g_all->argv = arraycpy(com->arguments, com->num_of_arguments);
}

static void	result_and_error(void)
{
	if (g_all->result != NULL)
		printf("%s", g_all->result);
	if (g_all->error != NULL)
		printf("%s", g_all->error);
}

void	do_func(t_simple_command *com)
{
	list_to_list(com);
	if (strncmp_mix(g_all->name, "exit", 5) != 0)
		change_env_error(0);
	if (strncmp_mix(g_all->name, "pwd", 4) == 0)
		pwd_blt();
	else if (strncmp_mix(g_all->name, "env", 4) == 0)
		env_blt();
	else if (strncmp_mix(g_all->name, "export", 7) == 0)
		export_blt();
	else if (strncmp_mix(g_all->name, "cd", 3) == 0)
		cd_blt();
	else if (strncmp_mix(g_all->name, "echo", 5) == 0)
		echo_blt();
	else if (strncmp_mix(g_all->name, "unset", 6) == 0)
		unset_blt();
	else if (strncmp_mix(g_all->name, "exit", 5) == 0)
		exit_blt();
	else
		exec_blt();
	result_and_error();
	g_all->exec_flag = 0;
	was_error();
	free_all();
}
