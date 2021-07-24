#include "minishell.h"

extern t_all	*g_all;

static char	*gethome(void)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	while (g_all->envp[i] != NULL)
	{
		if (ft_strncmp(g_all->envp[i], "HOME=", 5) == 0)
			home = ft_strdup(g_all->envp[i] + 5);
		i++;
	}
	return (home);
}

static void	cd_one_arg(void)
{
	char	*pwd;

	pwd = NULL;
	if (chdir(g_all->argv[0]) == 0)
	{
		pwd = getcwd(pwd, 0);
		if (pwd == NULL && errno == 2)
			g_all->error = stradd(g_all->error, CD_DELETED_DIR);
		else
			change_env("PWD", pwd);
		free(pwd);
	}
	else
	{
		if (errno == 2)
			result_error(NO_FILE_OR_DIR, g_all->argv[0], 1);
		else
			result_error(IT_IS_NOT_DIR, g_all->argv[0], 1);
	}
}

void cd_blt(void)
{
	char	*home;

	home = gethome();
	if (arraylen(g_all->argv) == 1 && ft_strncmp(g_all->argv[0], "~", 2) != 0)
		cd_one_arg();
	else if (arraylen(g_all->argv) > 1)
		result_error(TOO_MANY_ARGS, NULL, 1);
	else
	{
		if (home == NULL)
			result_error(NO_HOME, NULL, 1);
		else if (chdir(home) == 0)
			change_env("PWD", home);
		else
			result_error(NO_FILE_OR_DIR, home, 1);
	}
	free(home);
	change_last_arg();
}
