#include "minishell.h"

t_signal signal_flags;

void arrayfree(char **array)
{
	int i;

	i = 0;
	if (array == 0)
		return;
	while (array[i] != 0)
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}

int arraylen(char **array)
{
	int i;

	i = 0;
	if (array == 0)
		return (0);
	while (array[i] != 0)
		i++;
	return (i);
}

char **arraycpy(char **src)
{
	int i;
	int len;
	char **array;

	i = 0;
	len = arraylen(src);
	array = malloc((len + 1) * sizeof(char *));
	while (src[i] != 0)
	{
		array[i] = ft_strdup(src[i]);
		i++;
	}
	array[i] = 0;
	return(array);
}

char **arrayadd(char **src, char *str)
{
	int i;
	int len;
	char **array;

	len = arraylen(src);
	i = 0;
	array = malloc((len + 2) * sizeof(char *));
	if (src != NULL)
		while (src[i] != 0)
		{
			array[i] = ft_strdup(src[i]);
			i++;
		}
	array[i] = ft_strdup(str);
	i++;
	array[i] = 0;
	arrayfree(src);
	return(array);
}

void buffree(char *buf, char **bufsplit)
{
	free(buf);
	arrayfree(bufsplit);
}

void envadd(t_all *all, char *new_str)
{
	int i;
	char *equal;
	char *temp;

	i = 0;
	temp = ft_strdup(new_str);
	equal = ft_strchr(temp, '=');
	if (equal != NULL)
		*equal = '\0';
	while (all->envp[i] != NULL)
	{
		if (ft_strncmp(all->envp[i], temp, ft_strlen(temp)) == 0)
		{
			if (equal == NULL)
				break;
			else
			{
				free(all->envp[i]);
				all->envp[i] = ft_strdup(new_str);
				break;
			}
		}
		i++;
	}
	if (equal != NULL)
		*equal = '=';
	free(temp);
	if (all->envp[i] == NULL)
		all->envp = arrayadd(all->envp, new_str);
}

char *stradd(char *dst, char *str)
{
	int i;
	int j;
	char *new;

	i = 0;
	j = 0;

	new = malloc((ft_strlen(dst) + ft_strlen(str) + 1) * sizeof(char));
	if (dst != NULL)
		while (dst[i] != 0)
		{
			new[i] = dst[i];
			i++;
		}
	if (str != NULL)
		while (str[j] != 0)
		{
			new[i] = str[j];
			i++;
			j++;
		}
	new[i] = '\0';
	if (dst != NULL)
		free(dst);
	return(new);
}

void result_error(t_all *all, char *error, char *arg, int exit_status)
{
	all->error = stradd(all->error, "minishell: ");
	all->error = stradd(all->error, all->name);
	all->error = stradd(all->error, ": ");
	if (arg != NULL)
	{
		all->error = stradd(all->error, arg);
		all->error = stradd(all->error, ": ");
	}
	all->error = stradd(all->error, error);
	all->exit_status = exit_status;
	all->error_flag = 1;
}

void change_env(t_all *all, char *key, char *data)
{
	char *complete;

	complete = NULL;
	complete = stradd(complete, key);
	complete = stradd(complete, "=");
	complete = stradd(complete, data);
	envadd(all, complete);
	free(complete);
}

void change_last_arg(t_all *all)
{
	if (arraylen(all->argv) == 0)
		change_env(all, "_", all->name);
	else
		change_env(all, "_", all->argv[arraylen(all->argv) - 1]);
}

void was_error(t_all *all)
{
	if (all->error_flag == 1)
		all->error_flag = 0;
	else
		all->exit_status = 0;
}

void init_all(t_all *all)
{
	all->argv = NULL;
	all->result = NULL;
	all->error = NULL;
	all->name = NULL;
}

int main(int argc, char **argv, char **envp)
{
	char *str;
	t_token *token;
	t_tree_node *head;
	t_simple_command *command;
	(void)	argc;

	signal_flags.exec_flag = 0;
	rl_catch_signals = 0;
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	command = malloc(sizeof(t_simple_command));
	while (1 == 1)
	{
		str = readline("minishell$ ");
		if (str != NULL && str[0] != 0)
			add_history(str);
		if (str == NULL)
			exit(0);
		if (str == NULL)
			continue;
		token = ft_parser(str, envp);
		free(str);
		head = grammar(token);
		free_delete_all_tokens(&token);
        execute(head, &command);
		signal_flags.exec_flag = 0;
	}
}
