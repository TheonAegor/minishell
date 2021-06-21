/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dxenophi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 16:54:55 by dxenophi          #+#    #+#             */
/*   Updated: 2020/11/15 16:39:30 by pruthann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct	s_all
{
	char		*name;
	char		**argv;
	char		**envp;
	char		*result;
	char		**path;
}				t_all;

char **arraycpy(char **src, int len);
int arraylen(char **array);
char **arrayadd(char **src, char *str);
int arrayfree(char **array);
int	pwd_blt(t_all *all);
int	env_blt(t_all *all);
int export_blt(t_all *all);
int cd_blt(t_all *all);
int	echo_blt(t_all *all);
int unset_blt(t_all *all);
int	exit_blt(t_all *all);
int exec_blt(t_all *all);
#endif
