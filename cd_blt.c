#include "libft.h"
#include "minishell.h"

char *gethome(t_all *all)
{
	int i;
	char *home;

	i = 0;
	while (all->envp[i] != NULL)
	{
		if (ft_strncmp(all->envp[i], "HOME=", 5) == 0)
			home = ft_strdup(all->envp[i] + 5);
		i++;
	}
	return(home);
}

int pwdchange(t_all *all)
{
	char *pwd;
	int i;

	i = 0;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	while (all->envp[i] != 0)
	{
		if (ft_strncmp(all->envp[i], "PWD=", 4) == 0)
		{
			free(all->envp[i]);
			all->envp[i] = ft_strjoin("PWD=", pwd);
		}
		i++;
	}
	return(1);
}

int cd_blt(t_all *all)
{
	if (arraylen(all->argv) == 2)
	{
		if (chdir(all->argv[1]) == 0)
			pwdchange(all);
		else
			printf("minishell: cd: %s: Нет такого файла или каталога\n", all->argv[1]);
	}
	else if (arraylen(all->argv) > 2)
		printf("minishell: cd: слишком много аргументов\n");
	else
	{
		chdir(gethome(all));
		pwdchange(all);
	}
	return(1);
}
