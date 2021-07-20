#include "minishell.h"

extern t_all *all;

void free_all()
{
	if (all->name != NULL)
		free(all->name);
	if (all->argv != NULL)
		arrayfree(all->argv);
//	if (all->envp != NULL)
//		arrayfree(all->envp);
	if (all->redirect_in != NULL)
		free(all->redirect_in);
	if (all->redirect_out != NULL)
		free(all->redirect_out);
	if (all->result != NULL)
		free(all->result);
	if (all->error != NULL)
		free(all->error);
	if (all->path != NULL)
		free(all->path);
}

void init_all()
{
	all->name = NULL;
	all->argv = NULL;
	all->envp = NULL;
	all->result = NULL;
	all->error = NULL;
	all->path = NULL;
	all->redirect_in = NULL;
	all->redirect_out = NULL;
}

void list_to_list(t_simple_command *com)
{
	init_all();
	all->name = ft_strdup(com->command_name);
	all->argv = arraycpy(com->arguments, com->num_of_arguments);
	all->envp = arraycpy(com->envp, arraylen(com->envp));
	all->pipe_read = com->pipe_read;
	all->pipe_write = com->pipe_write;
	all->save = com->save;
	all->redirect_in = ft_strdup(com->redirect_in);
	all->redirect_out = ft_strdup(com->redirect_out);
}

void do_func(t_simple_command *com)
{
	extern t_signal signal_flags;

	all->exit_status = 0;
	list_to_list(com);
	if (strncmp_mix(all->name, "pwd", 4) == 0)
		pwd_blt();
	else if (strncmp_mix(all->name, "env", 4) == 0)
		env_blt();
	else if (strncmp_mix(all->name, "export", 7) == 0)
		export_blt();
	else if (strncmp_mix(all->name, "cd", 3) == 0)
		cd_blt();
	else if (strncmp_mix(all->name, "echo", 5) == 0)
		echo_blt();
	else if (strncmp_mix(all->name, "unset", 6) == 0)
		unset_blt();
	else if (strncmp_mix(all->name, "exit", 5) == 0)
		exit_blt();
	else
		exec_blt("./a.out");
	if (all->result != NULL)
	{
		com->result = ft_strdup(all->result);
//		printf("===============RESULT=================\n");
		printf("%s", all->result);
//		printf("===============RESULT=================\n");
	}
	if (all->error != NULL)
	{
		com->error_log = ft_strdup(all->error);
		printf("===============ERROR=================\n");
		printf("%s", all->error);
		printf("===============ERROR=================\n");
	}
	signal_flags.exec_flag = 0;
	was_error();
//	write(1, " QQQ ", 5);
	free_all();
}
