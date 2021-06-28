#include "minishell.h"

void		free_support_token(t_support_token **sup)
{
	free((*sup)->str);
	(*sup)->str = NULL;
	free(*sup);
	*sup = NULL;
}
