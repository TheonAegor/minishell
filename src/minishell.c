#include "libft.h"
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

void sigint(int sig)
{
	(void)sig;
	if (signal_flags.exec_flag == 0)
	{
//		all->exit_status = 130;
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void sigquit(int sig)
{
	(void)sig;
}

void was_error(t_all *all)
{
	if (all->error_flag == 1)
		all->error_flag = 0;
	else
		all->exit_status = 0;
}

int main(int argc, char **argv, char **envp)
{
	t_all	all;
	int		i;
	int		j;
	char	*buf;
	char	**bufsplit;
	(void)	argc;

	i = 0;
	all.argv = NULL;
	all.result = NULL;
	all.error = NULL;
	all.name = NULL;
	buf = NULL;
	signal_flags.exec_flag = 0;
	all.exit_status = 0;
	rl_catch_signals = 0;
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
	all.envp = arraycpy(envp);
	while (1 == 1)
	{
		i = 0;
		buf = readline("minishell$ ");
		if (buf != NULL && buf[0] != 0)
			add_history(buf);
		if (buf == NULL)
			exit(0);
		bufsplit = ft_split(buf, ' ');
		if (bufsplit[0] != 0)
		{
			all.name = ft_strdup(bufsplit[0]);
			while (bufsplit[i + 1] != 0)
			{
				all.argv = arrayadd(all.argv, bufsplit[i + 1]);
				i++;
			}
		}
		if (bufsplit[0] == 0)
		{
			buffree(buf, bufsplit);
			continue;
		}
		else if (ft_strncmp(all.name, "?", 2) == 0)
			printf("%d\n", all.exit_status);
		else if (ft_strncmp(all.name, "_", 2) == 0)
		{
			j = 0;
			while (all.envp[j] != 0)
			{
				if (ft_strncmp(all.envp[j], "_=", 2) == 0)
					break;
				j++;
			}
			printf("%s\n", all.envp[j] + 2);
		}
		else if (strncmp_mix(all.name, "pwd", 4) == 0)
			pwd_blt(&all);
		else if (strncmp_mix(all.name, "env", 4) == 0)
			env_blt(&all);
		else if (strncmp_mix(all.name, "export", 7) == 0)
			export_blt(&all);
		else if (strncmp_mix(all.name, "cd", 3) == 0)
			cd_blt(&all);
		else if (strncmp_mix(all.name, "echo", 5) == 0)
			echo_blt(&all);
		else if (strncmp_mix(all.name, "unset", 6) == 0)
			unset_blt(&all);
		else if (strncmp_mix(all.name, "exit", 5) == 0)
			exit_blt(&all);
		else
		{
			all.name = ft_strdup(bufsplit[0]);
			exec_blt(&all, argv[0]);
			arrayfree(all.path);
		}
		if (all.result != NULL)
		{
			printf("%s", all.result);
			free(all.result);	
		}
		if (all.error != NULL)
		{
			printf("%s", all.error);
			free(all.error);	
		}
		if (all.name != NULL)
			free(all.name);
		signal_flags.exec_flag = 0;
		was_error(&all);
		buffree(buf, bufsplit);
		arrayfree(all.argv);
		all.argv = NULL;
		all.name = NULL;
		all.result = NULL;
		all.error = NULL;
		buf = NULL;
	}
}
