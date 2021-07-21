#include "minishell.h"

void    print_token_data(t_token *token)
{
		printf("(");
		printf("%s", token->data);
//		printf("%d", token->type);
		printf(")");
}