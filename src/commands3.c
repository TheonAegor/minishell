#include "minishell.h"

int			redirect_out(t_simple_command **command)
{
	int					std_in;
	int					std_out;
	int					fd_read;
	int					fd_write;
	t_simple_command	*com;
//	char				*buf;

	com = *command;
	std_in = dup(0);
	std_out = dup(1);
	fd_read = open(com->redirect_out, O_RDONLY);
	if (fd_read == -1)
		return (fd_read);
	dup2(fd_read, 0);
	if (com->pipe_write != NO_VAL)
		dup2(com->pipe_write, 1);
	else if (com->redirect_in != NULL)
	{
		fd_write = open(com->redirect_in, O_CREAT | O_WRONLY, S_IRWXU);
		dup2(fd_write, 1);
	}

	do_func(com);

	close(fd_read);
	close(com->pipe_write);
	dup2(std_out, 1);
	dup2(std_in, 0);
	return (1);
}
