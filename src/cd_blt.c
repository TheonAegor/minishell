#include "minishell.h"

extern t_all *all;

char *gethome()
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

void cd_blt()
{
	char *pwd;
	char *home;

	pwd = NULL;
	home = gethome();
	if (arraylen(all->argv) == 1 && ft_strncmp(all->argv[0], "~", 2) != 0)
	{
		if (chdir(all->argv[0]) == 0)
		{
			pwd = getcwd(pwd, 0);
			if (pwd == NULL && errno == 2)
				all->error = stradd(all->error, "cd: ошибка определения текущего каталога: getcwd: нет доступа к родительским каталогам: Нет такого файла или каталога\n");
			else
				change_env("PWD", pwd);
			free(pwd);
		}
		else
		{
			if (errno == 2)
				result_error("Нет такого файла или каталога\n", all->argv[0], 1);
			else
				result_error("Это не каталог\n", all->argv[0], 1);
		}
	}
	else if (arraylen(all->argv) > 1)
		result_error("слишком много аргументов\n", NULL, 1);
	else
	{
		if (home == NULL)
			result_error("Не задана переменная HOME\n", NULL, 1);
		else if (chdir(home) == 0)
			change_env("PWD", home);
		else
			result_error("Нет такого файла или каталога\n", home, 1);
	}
	free(home);
	change_last_arg();
}
