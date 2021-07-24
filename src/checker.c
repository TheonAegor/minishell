#include "minishell.h"

int check_tokens(t_token *tok)
{
    t_token *tmp;

    tmp = tok;
    while (tmp->next)
    {
        if (is_end_of_command(tmp->type) && tmp->type != CHAR_NULL)
        {
            if (tmp->next->type == CHAR_NULL)
                return (-1);
        }
        tmp = tmp->next;
    }
    return (1);
}