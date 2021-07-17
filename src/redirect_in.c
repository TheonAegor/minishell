#include "minishell.h"

int	redirect_in(t_simple_command **command)
{
	t_simple_command	*com;
	int					fd;
	int					std_out;

	com = *command;
	std_out = dup(1);
	fd = open(com->redirect_in, O_CREAT | O_WRONLY, S_IRWXU);
	if (fd == -1)
	{
		printf("here\n");
		return (fd);
	}
	printf("hereee\n");
	dup2(fd, 1);

	do_func(com);
	
	close(fd);
	dup2(std_out, 1);
	write(1, "now\n", 4);
}
