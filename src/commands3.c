#include "minishell.h"

int			read_from_redirect(t_simple_command *com)
{
	int	std_in;
	int	std_out;
	int	fd;

	std_in = dup(0);
	std_out = dup(1);
	fd = open(com->redirect_out, O_RDONLY);
	if (fd == -1)
		return (fd);
	dup2(fd, 0);
	if (com->pipe_write != NO_VAL)
		dup2(com->pipe_write, 1);
//	do_func(com);
	close(fd);
	close(com->pipe_write);
	dup2(std_out, 1);
	dup2(std_in, 0);
	return (1);
}
