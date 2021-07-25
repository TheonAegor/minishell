#include "minishell.h"

int	mywexitstatus(int status)
{
	return (((status) & 0xff00) >> 8);
}

int	mywtermsig(int status)
{
	return ((status) & 0x7f);
}

int	mywifsignaled(int status)
{
	return (((signed char)(((status) & 0x7f) + 1) >> 1) > 0);
}

int	mywifexited(int status)
{
	if (mywtermsig(status) == 0)
		return (1);
	return (0);
}
