#include "minishell.h"

int	read_from_pipe(t_simple_command **command)
{
	int					std_in;
	t_simple_command	*com;

	com = *command;
	std_in = dup(0);
	dup2(com->pipe_read, 0);
	if (com->redirect_in != NULL)
		redirect_in(&com);
	if (com->pipe_write != NO_VAL)
		write_in_pipe(&com);
	else
		do_func(com);
	close(com->pipe_read);
	com->pipe_read = NO_VAL;
	dup2(std_in, 0);
	return (1);
}

int	write_in_pipe(t_simple_command **command)
{
	int					std_out;
	t_simple_command	*com;

	com = *command;
	std_out = dup(1);
	dup2(com->pipe_write, 1);
	do_func(com);
	close(com->pipe_write);
	com->pipe_write = NO_VAL;
	dup2(std_out, 1);
	return (1);
}
