#include "minishell.h"

int			read_from_pipe(t_simple_command **command)
{
	int	std_in;
	int	std_out;
	int	fd;
	t_simple_command *com;

	com = *command;
	std_in = dup(0);
	std_out = dup(1);
	dup2(com->pipe_read, 0);
	if (com->redirect_in != NULL)
	{
//		Нужно добавть проверку save, видимо другие флаги при открытии будут
		redirect_in(&com);
	}
	if (com->pipe_write != NO_VAL)
		write_in_pipe(&com);
	else
		do_func(com);

	if (com->redirect_in != NULL)
		close(fd);
	close(com->pipe_read);
	com->pipe_read = NO_VAL;
//	Возвращаем стандартные фдшники
	dup2(std_in, 0);
	return (1);
}

int			write_in_pipe(t_simple_command **command)
{
	int	std_out;
	t_simple_command *com;
	
	com = *command;
	std_out = dup(1);
	dup2(com->pipe_write, 1);
//	printf("lol\n");
	do_func(com);
//	printf("loliki\n");
	close(com->pipe_write);
	com->pipe_write = NO_VAL;
	dup2(std_out, 1);
	return (1);
}
