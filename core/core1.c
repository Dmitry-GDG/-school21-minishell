/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarg <kmarg@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:18:54 by kmarg             #+#    #+#             */
/*   Updated: 2022/03/16 15:43:18 by kmarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	signal_c1(int c)
{
	(void) c;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
}

static void	solo_cmd(t_data *data)
{
	int	pid;
	int	i;

	if (data->qty_pipes == 0)
		pid = fork_and_chain(data->pipes.lpipe, data->pipes.rpipe, data);
	i = -1;
	while (++i < data->qty_cmds)
		waitpid (-1, &data->exit_status, 0);
	if ((data->qty_pipes == 0) && (!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, \
	"cat") || !ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "wc")) && \
	!data->cmds[data->tmp.h]->args[0] && !data->cmds[data->tmp.h]->redir_r[0])
	{
		write(2, "\n", 1);
		printf("\033[A");
	}
	if ((data->qty_pipes > 0) && (!ft_strcmp(data->cmds[data->tmp.h - \
	1]->cmd_bin, "cat") || !ft_strcmp(data->cmds[data->tmp.h - \
	1]->cmd_bin, "wc")) && !data->cmds[data->tmp.h - 1]->args[0] \
	&& !data->cmds[data->tmp.h - 1]->redir_r[0])
	{
		write(2, "\n", 1);
		printf("\033[A");
	}
}

static void	closes25(t_data *data)
{
	close(data->pipes.lpipe[0]);
	close(data->pipes.lpipe[1]);
	close(data->pipes.rpipe[0]);
	close(data->pipes.rpipe[1]);
}

void	exec_pipes(t_data *data, int pid)
{
	if (data->cmds[data->tmp.h]->delimiter_l != 1 \
	&& data->cmds[data->tmp.h]->delimiter_r == 1)
	{
		pid = fork_and_chain(NULL, data->pipes.rpipe, data);
		data->pipes.lpipe[0] = data->pipes.rpipe[0];
		data->pipes.lpipe[1] = data->pipes.rpipe[1];
		if (calc_hdk(data))
			close(data->pipes.lpipe[1]);
	}
	if (data->cmds[data->tmp.h]->delimiter_l == 1 \
	&& data->cmds[data->tmp.h]->delimiter_r == 1)
	{
		pid = fork_and_chain(data->pipes.lpipe, data->pipes.rpipe, data);
		close(data->pipes.lpipe[0]);
		if (data->tmp.hdk == 0)
			close(data->pipes.lpipe[1]);
		data->pipes.lpipe[0] = data->pipes.rpipe[0];
		data->pipes.lpipe[1] = data->pipes.rpipe[1];
	}
	if (data->cmds[data->tmp.h]->delimiter_l == 1 \
	&& data->cmds[data->tmp.h]->delimiter_r != 1)
	{
		pid = fork_and_chain(data->pipes.lpipe, NULL, data);
		closes25(data);
	}
}

int	exec_cmd(t_data *data)
{
	int	pid;

	pid = 0;
	data->tmp.hdk = calc_hdk1(data);
	signal(SIGINT, signal_c1);
	if (data->qty_cmds == 0)
		return (0);
	data->tmp.n = 0;
	data->tmp.h = -1;
	while ((++(data->tmp.h) < data->qty_cmds) && (data->qty_pipes >= 1))
	{
		if (check_cd_left_pipe(data))
			return (0);
		pipe(data->pipes.rpipe);
		exec_pipes(data, pid);
		if (data->exit_status == 0 && data->cmds[data->tmp.h]->delimiter_r == 2)
			break ;
	}
	solo_cmd(data);
	return (0);
}
