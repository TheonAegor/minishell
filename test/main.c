#include "minishell.h"

void	print_token_data(t_token *token)
{
	printf("%s\n", token->data);
}

int main()
{
	t_token *o;
	t_token *two;
	t_token *three;

	o = init_token("hello");
	two = init_token("world");
	three = init_token("wow!");
	
	add_token_front(&o, two);
	add_token_front(&o, three);
	implement_f_to_all_tokens(&o, print_token_data);
	printf("o->data = %s\n", o->data);
	printf("END");
/*
	int *pp;
	int **ppp;
	int p;

	p = 1;
	pp = &p;
	*ppp = &p;
//	ppp = &pp;

	printf ("&p\t =\t%p - add of value\n", &p);
	printf ("pp\t =\t%p - add of value\n", pp);
	printf ("*ppp\t =\t%p - value of pointer=add of value\n", *ppp);
	printf ("&pp\t =\t%p - add of pointer\n", &pp);
	printf ("ppp\t =\t%p - add of pointer\n", ppp);
	printf ("&ppp\t =\t%p - add of pointer of pointer\n", &ppp);
	printf ("**ppp\t =\t%d - value\n", **ppp);
	printf ("*pp\t =\t%d - value\n", *pp);
	printf ("p\t =\t%d - value\n", p);
*/
	return (1);
}
