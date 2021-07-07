#include "minishell.h"

void init_all(t_all *all)
{
	all->argv = NULL;
	all->result = NULL;
	all->error = NULL;
	all->name = NULL;
	all->redirect_in = NULL;
	all->redirect_out = NULL;
}

t_all *list_to_list(t_simple_command *com)
{
	t_all *all;

	all = malloc(sizeof(t_all));
	all->name = ft_strdup(com->command_name);
	all->argv = arraycpy(com->arguments, com->num_of_arguments);
	all->envp = arraycpy(com->envp, arraylen(com->envp));
	all->pipe_read = com->pipe_read;
	all->pipe_write = com->pipe_write;
	all->save = com->save;
	all->redirect_in = ft_strdup(com->redirect_in);
	all->redirect_out = ft_strdup(com->redirect_out);
	return (all);
}

void do_func(t_simple_command *com)
{
	t_all *all;
	extern t_signal signal_flags;

	all = list_to_list(com);
	all->exit_status = 0;
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
		exec_blt(all, "./a.out");
		arrayfree(all->path);
	}
	if (all->result != NULL)
	{
		printf("===============RESULT=================\n");
		printf("%s", all->result);
		printf("===============RESULT=================\n");
		free(all->result);
	}
	if (all->error != NULL)
	{
		printf("===============ERROR=================\n");
		printf("%s", all->error);
		printf("===============ERROR=================\n");
		free(all->error);
	}
	if (all->name != NULL)
		free(all->name);
	signal_flags.exec_flag = 0;
	was_error(all);
	arrayfree(all->argv);
//	init_all(all);
}
