#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct	s_all
{
	char		*name;
	char		**argv;
	char		**envp;
	char		*result;
	char		*error;
	char		**path;
	int			exit_status;
	int			error_flag;	
}				t_all;

typedef struct	s_simple_command
{
	int			num_of_arguments;
	char		*command_name;
	char		**arguments;
	char		*result;
	char		*error_log;
	int			pipe_read;
	int			pipe_write;
	int			save;
	char		*redirect_in;
	char		*redirect_out;
}				t_simple_command;

typedef struct	s_signal
{
	int			exec_flag;
	int			pid;
}				t_signal;

int				strncmp_mix(const char *s1, const char *s2, size_t n);
void			sigint(int sig);
void			sigquit(int sig);
char			**arraycpy(char **src);
int				arraylen(char **array);
void			result_error(t_all *all, char *error, char *arg, int exit_status);
char			*stradd(char *dst, char *str);
char			**arrayadd(char **src, char *str);
void			arrayfree(char **array);
void			envadd(t_all *all, char *new_str);
void			change_env(t_all *all, char *key, char *data);
void			change_last_arg(t_all *all);
void			pwd_blt(t_all *all);
void			env_blt(t_all *all);
void			export_blt(t_all *all);
void			cd_blt(t_all *all);
void			echo_blt(t_all *all);
void			unset_blt(t_all *all);
void			exit_blt(t_all *all);
int				exec_blt(t_all *all, char *first_arg);
#endif
