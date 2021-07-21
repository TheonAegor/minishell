#include "minishell.h"

int	redirect_in(t_simple_command **command)
{
	t_simple_command	*com;
	int					fd;
	int					std_out;

	com = *command;
	std_out = dup(1);
	printf("com->save = %d\n",com->save);
	if (com->save == NO_VAL)
		fd = open(com->redirect_in, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		fd = open(com->redirect_in, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd == -1)
		return (fd);
	dup2(fd, 1);

	do_func(com);

	close(fd);
	dup2(std_out, 1);
}

int			redirect_out(t_simple_command **command)
{
	int					std_in;
	int					std_out;
	int					fd_read;
	int					fd_write;
	t_simple_command	*com;
//	char				*buf;
/* сохраняем стандартный ипут и аутпут
	сохраняем файловый дескриптор на инпут
	дуплицируем его
	если есть дуплицируем на аутпут

	выполняем команду

	закрываем на чтение
	если есть закрываем на аутпут
	дуплицируем обратно все
*/
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
		if (com->save == NO_VAL)
			fd_write = open(com->redirect_in, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		else
			fd_write = open(com->redirect_in, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		dup2(fd_write, 1);
		free(com->redirect_in);
		com->redirect_in = NULL;
	}

	do_func(com);

	close(fd_read);
	close(com->pipe_write);
	dup2(std_out, 1);
	dup2(std_in, 0);
	return (1);
}
