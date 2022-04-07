/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p4_fill_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:30:56 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 21:10:13 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_fill_redirs4(t_data *data, int j, int i)
{
	int		k;

	if (!data->cmds[i]->redir_r[0])
	{
		data->cmds[i]->redir_r[0] = ft_substr(data->cmds[i]->cmd, \
		data->tmp.begin, j - data->tmp.begin + 1);
		if (!data->cmds[i]->redir_r[0])
			return (5);
		data->cmds[i]->qty_redir_r++;
		data->cmds[i]->redir_r[1] = NULL;
	}
	else
	{
		k = 0;
		while (data->cmds[i]->redir_r[k])
			k++;
		data->cmds[i]->redir_r[k] = ft_substr(data->cmds[i]->cmd, \
		data->tmp.begin, j - data->tmp.begin + 1);
		if (!data->cmds[i]->redir_r[k])
			return (5);
		data->cmds[i]->qty_redir_r++;
		data->cmds[i]->redir_r[k + 1] = NULL;
	}
	return (0);
}

static int	my_fill_redirs3(t_data *data, int j, int i)
{
	int		k;

	if (!data->cmds[i]->redir_l[0])
	{
		data->cmds[i]->redir_l[0] = ft_substr(data->cmds[i]->cmd, \
		data->tmp.begin, j - data->tmp.begin + 1);
		if (!data->cmds[i]->redir_l[0])
			return (5);
		data->cmds[i]->qty_redir_l++;
		data->cmds[i]->redir_l[1] = NULL;
	}
	else
	{
		k = 0;
		while (data->cmds[i]->redir_l[k])
			k++;
		data->cmds[i]->redir_l[k] = ft_substr(data->cmds[i]->cmd, \
		data->tmp.begin, j - data->tmp.begin + 1);
		if (!data->cmds[i]->redir_l[k])
			return (5);
		data->cmds[i]->qty_redir_l++;
		data->cmds[i]->redir_l[k + 1] = NULL;
	}
	return (0);
}

static int	my_fill_redirs2(t_data *data, int j, int i)
{
	if (!data->cmds[i]->cmd_bin)
	{
		data->cmds[i]->cmd_bin = ft_substr(data->cmds[i]->cmd, \
		data->tmp.begin, j - data->tmp.begin + 1);
		if (!data->cmds[i]->cmd_bin)
			return (5);
	}
	else
	{
		data->cmds[i]->args[data->cmds[i]->qty_args] = \
		ft_substr(data->cmds[i]->cmd, data->tmp.begin, \
		j - data->tmp.begin + 1);
		if (!data->cmds[i]->args[data->cmds[i]->qty_args])
			return (5);
		data->cmds[i]->qty_args++;
		data->cmds[i]->args[data->cmds[i]->qty_args] = NULL;
	}
	return (0);
}

static int	my_fill_redirs1(t_data *data, int j, int i)
{
	if (data->tmp.sig == 0)
		return (my_fill_redirs2(data, j, i));
	if (data->tmp.sig == 1)
		return (my_fill_redirs3(data, j, i));
	if (data->tmp.sig == 2)
		return (my_fill_redirs4(data, j, i));
	return (0);
}

int	my_fill_redirs(t_data *data, int j, int i)
{
	int	err;

	err = my_fill_redirs1(data, j, i);
	if (err)
		return (err);
	return (0);
}
