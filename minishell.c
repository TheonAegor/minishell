#include "libft.h"
#include "minishell.h"

int arrayfree(char **array)
{
	int i;

	i = 0;
	if (array == 0)
		return(0);
	while (array[i] != 0)
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
	return(0);
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

int buffree(char *buf, char *buftrim, char **bufsplit)
{
	free(buf);
	free(buftrim);
	arrayfree(bufsplit);
	return(0);
}

int main(int argc, char **argv, char **envp)
{
	t_all	all;
	int		i;
	char	*buf;
	char	*buftrim;
	char	**bufsplit;
	(void)	argc;

	i = 0;
	all.argv = arraycpy(argv, arraylen(argv));
	all.envp = arraycpy(envp, arraylen(envp));
	while (1 == 1)
	{
		i = 0;
		buf = readline("minishell$ ");
		add_history(buf);
		buftrim = ft_strtrim(buf, " \n");
		bufsplit = ft_split(buftrim, ' ');
		while (bufsplit[i + 1] != 0)
		{
			all.argv = arrayadd(all.argv, bufsplit[i + 1]);
			i++;
		}
		if (bufsplit[0] == 0)
		{
			buffree(buf, buftrim, bufsplit);
			arrayfree(all.argv);
			all.argv = arraycpy(argv, arraylen(argv));
			continue;
		}
		else if (ft_strncmp(bufsplit[0], "pwd", 4) == 0)
		{
			pwd_blt(&all);
			printf("%s\n", all.result);
		}
		else if (ft_strncmp(bufsplit[0], "env", 4) == 0)
		{
			env_blt(&all);
			printf("%s\n", all.result);
		}
		else if (ft_strncmp(bufsplit[0], "export", 7) == 0)
		{
			export_blt(&all);
			if (arraylen(bufsplit) == 1)
				printf("%s\n", all.result);
		}
		else if (ft_strncmp(bufsplit[0], "cd", 3) == 0)
			cd_blt(&all);
		else if (ft_strncmp(bufsplit[0], "echo", 5) == 0)
		{
			echo_blt(&all);
			printf("%s\n", all.result);
		}
		else if (ft_strncmp(bufsplit[0], "unset", 6) == 0)
			unset_blt(&all);
		else if (ft_strncmp(bufsplit[0], "exit", 5) == 0)
			exit_blt(&all);
		else
		{
			all.name = ft_strdup(bufsplit[0]);
			exec_blt(&all);
			free(all.name);
			arrayfree(all.path);
		}
		buffree(buf, buftrim, bufsplit);
		arrayfree(all.argv);
		all.argv = arraycpy(argv, arraylen(argv));
	}
}
