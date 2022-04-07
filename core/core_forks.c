/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarg <kmarg@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:39:10 by kmarg             #+#    #+#             */
/*   Updated: 2022/03/16 18:07:47 by kmarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_read(int *lpipe)
{
	dup2(lpipe[0], STDIN_FILENO);
	close(lpipe[0]);
	close(lpipe[1]);
}

static void	set_write(int *rpipe)
{
	dup2(rpipe[1], STDOUT_FILENO);
	close(rpipe[0]);
	close(rpipe[1]);
}

static int	chidx(int *lpipe, int *rpipe, t_data *data)
{
	int	err;

	err = 0;
	signal(SIGQUIT, signal_quit1);
	calc_hdk(data);
	if (data->tmp.n > 0)
		err = child_hdk(data);
	if (lpipe)
		set_read(lpipe);
	if (rpipe)
		set_write(rpipe);
	if (!err && (data->cmds[data->tmp.h]->redir_l[0] != NULL \
	&& data->cmds[data->tmp.h]->redir_l[0][1] != '<'))
		err = child_rdl(data);
	if (!err && (data->cmds[data->tmp.h]->redir_r[0] != NULL))
		err = child_rdr(data);
	err = my_if_built(data);
	if (err == 11 && data->qty_pipes > 0)
	{
		data->tmp.h++;
		exit (0);
	}
	return (err);
}

static int	exec_func(int *lpipe, int *rpipe, t_data *data)
{
	char	**j_args;
	char	*path;
	int		err;

	err = 0;
	err = chidx(lpipe, rpipe, data);
	path = check_cmd(data);
	if (remake_env(data))
		data->exit_status = 1;
	if (data->cmds[data->tmp.h]->args[0])
	{
		j_args = join_args(data);
		if (!j_args || !execve(path, join_args(data), data->envp))
		{
			data->exit_status = 1;
			exit(1);
		}
		free (j_args);
		exit (0);
	}
	execve(path, join_args(data), data->envp);
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, path, ft_strlen(path));
	write(STDERR_FILENO, " is a directory\n", 16);
	exit (126);
}

int	fork_and_chain(int *lpipe, int *rpipe, t_data *data)
{
	int	err;
	int	pid;

	err = 0;
	if (data->cmds[data->tmp.h]->delimiter_r != 1 \
	&& data->cmds[data->tmp.h]->delimiter_l != 1)
		err = my_if_built(data);
	if (err == 11 && (data->cmds[data->tmp.h]->delimiter_r != 1 \
	&& data->cmds[data->tmp.h]->delimiter_l != 1))
		return (0);
	if (err == 11 && data->qty_pipes > 0)
		data->tmp.h++;
	pid = fork();
	if (pid == -1)
		chk_cmd_exit(data, 3);
	if (!pid)
		err = exec_func(lpipe, rpipe, data);
	else
		hdk_wait(data);
	return (pid);
}
// data->tmp.i = -1;    
// while (data->env[++data->tmp.i])
//     free (data->envp[data->tmp.i]);
// free (data->envp[data->tmp.i]);
// free (data->envp);
