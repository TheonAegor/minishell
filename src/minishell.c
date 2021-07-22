#include "minishell.h"

t_all	*all;

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

char **arraycpy(char **src, int len)
{
	int i;
	char **array;

	i = 0;
	if (len == NO_VAL)
		array = malloc(1 * sizeof(char *));
	else
		array = malloc((len + 1) * sizeof(char *));
	while (i < len)
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

void envadd(char *new_str)
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

int change_env_error(int exit_status)
{
	char *str_error;

	all->exit_status = exit_status;
	str_error = ft_itoa(exit_status);
	change_env("?", str_error);
	free(str_error);
	all->error_flag = 1;
	return (0);
}

void result_error(char *error, char *arg, int exit_status)
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
	change_env_error(exit_status);
}

void change_env(char *key, char *data)
{
	char *complete;

	complete = NULL;
	complete = stradd(complete, key);
	complete = stradd(complete, "=");
	complete = stradd(complete, data);
	envadd(complete);
	free(complete);
}

void change_last_arg()
{
	if (arraylen(all->argv) == 0)
		change_env("_", all->name);
	else
		change_env("_", all->argv[arraylen(all->argv) - 1]);
}

void was_error()
{
	if (all->error_flag == 1)
		all->error_flag = 0;
	else
		all->exit_status = 0;
}

t_simple_command	*init_command()
{
	t_simple_command *command;

	command = malloc(sizeof(t_simple_command));
	command->num_of_arguments = 0;
	command->pipe_read = NO_VAL;
	command->pipe_write = NO_VAL;
	command->save = NO_VAL;
	command->redirect_in = NULL;
	command->redirect_out = NULL;
	return (command);
}

int setup_envp()
{
	change_env("_", "minishell");
	change_env("?", "0");
}

int main(int argc, char **argv, char **envp)
{
	char *str;
	t_token *token;
	t_tree_node *head;
	t_simple_command *command;
	(void)	argc;

	all = malloc(sizeof(t_all));
	all->exec_flag = 0;
	rl_catch_signals = 0;
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	command = init_command();
	all->envp = arraycpy(envp, arraylen(envp));
	setup_envp();
	while (1 == 1)
	{
		str = readline("minishell$ ");
		if (str == NULL)
		{
			printf("exit\n");
			exit(all->exit_status);
		}
		if (str[0] == 0)
			continue;
		add_history(str);
		token = ft_parser(str, all->envp);
		free(str);
		head = grammar(token);
		free_delete_all_tokens(&token);
        execute(head, &command);
		all->exec_flag = 0;
	}
}
