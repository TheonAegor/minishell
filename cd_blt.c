#include "libft.h"
#include "minishell.h"

char *gethome(t_all *all)
{
	int i;
	char *home;

	i = 0;
	home = NULL;
	while (all->envp[i] != NULL)
	{
		if (ft_strncmp(all->envp[i], "HOME=", 5) == 0)
			home = ft_strdup(all->envp[i] + 5);
		i++;
	}
	return(home);
}

void cd_blt(t_all *all)
{
	char *pwd;
	char *home;

	pwd = NULL;
	home = gethome(all);
	if (arraylen(all->argv) == 1 && ft_strncmp(all->argv[0], "~", 2) != 0)
	{
		if (chdir(all->argv[0]) == 0)
		{
			pwd = getcwd(pwd, 0);
			change_env(all, "PWD", pwd);
			free(pwd);
		}
		else
			result_error(all, "Нет такого файла или каталога\n", all->argv[0], 1);
	}
	else if (arraylen(all->argv) > 1)
		result_error(all, "слишком много аргументов\n", NULL, 1);
	else
	{
		if (home == NULL)
			result_error(all, "Не задана переменная HOME\n", NULL, 1);
		else if (chdir(home) == 0)
			change_env(all, "PWD", home);
		else
			result_error(all, "Нет такого файла или каталога\n", home, 1);
	}
	free(home);
	change_last_arg(all);
}
