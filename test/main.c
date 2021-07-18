#include "minishell.h"

int main(int argc, char *argv[], char **envp)
{
	int fd;

	fd = open('1', O_RDONLY);
	dup(fd, 0);
	

	return (1);
}
