/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:47:46 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 21:24:59 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

typedef struct s_quotes
{
	int		first;
	int		second;
	int		sign;
}			t_quotes;

//delimiters: 1 = pipe, 2 = ||, 3 = &&
typedef struct s_cmds
{
	char	*cmd;
	int		delimiter_l;
	int		delimiter_r;
	char	*redir_l[100];
	int		qty_redir_l;
	char	*redir_r[100];
	int		qty_redir_r;
	int		fd[2];	
	char	*cmd_bin;
	char	*args[500];
	int		qty_args;
	int		if_built;
	char	*tmp;
	char	**rdr_name;
	char	**new_arg;
}			t_cmds;

typedef struct s_pipes
{
	int	lpipe[2];
	int	rpipe[2];
}	t_pipes;

typedef struct s_tmp
{
	int		flagq;
	int		flagdq;
	int		firstflagq;
	int		firstflagdq;
	int		k;
	int		l;
	int		m;
	int		p;
	int		sig;
	int		begin;
	int		quot;
	int		dquot;
	int		i;
	int		j;
	int		h;
	int		n;
	int		filein;
	int		fileout;
	int		hdk;
	char	*tt;
}	t_tmp;

typedef struct s_data
{
	t_env			*env[100];
	int				qty_env;
	int				flag_env;
	char			*cmd_line;
	t_cmds			*cmds[100];
	int				qty_cmds;
	t_quotes		*quotes[100];
	int				qty_quotes;
	t_tmp			tmp;
	int				qty_pipes;
	int				pipe_status;
	int				exit_status;
	char			**envp;
	t_pipes			pipes;
}	t_data;

int		my_cd(t_data *data, char **str);
int		my_echo(t_data *data, char **arg);
void	my_env(t_data *data);
void	my_exit(t_data *data, int i);
int		my_export(t_data *data, char **args);
int		my_add_env3(t_data *data, char *args);
int		my_pwd(t_data *data);
int		my_unset(t_data *data, char **args);
int		my_calc_pipes(t_data *data);
int		my_chck_env_vars(t_data *data);
int		my_chck_redirections(t_data *data);
int		my_chck_amp_and_redirs(t_data *data);
char	*my_convert_env(char *str, int *i, t_data *data);
int		my_correct_cmds_and_args(t_data *data);
int		my_fill_env(t_data *data, char **envp);
int		my_fill_redirs(t_data *data, int j, int i);
void	my_free_env(t_data *data);
int		minishell1(t_data *data);
int		minishell2(t_data *data);
int		my_parcing_data(t_data *data);
int		my_pre_parcing(t_data *data);
void	my_print_errors(t_data *data, int sign);
int		my_return_mssg(t_data *data, int sign);
int		my_split_cmds(t_data *data);

int		exec_cmd(t_data *data);
int		my_if_built(t_data *data);
int		child_rdr(t_data *data);
int		child_rdl(t_data *data);
int		child_hdk(t_data *data);
int		calc_hdk(t_data *data);
int		calc_hdk1(t_data *data);
char	*check_cmd(t_data *data);
int		remake_env(t_data *data);
int		check_cd_left_pipe(t_data *data);
int		fork_and_chain(int *lpipe, int *rpipe, t_data *data);
char	**join_args(t_data *data);
void	signal_quit1(int c);
void	chk_cmd_exit(t_data *data, int i);
void	hdk_wait(t_data *data);

#endif
