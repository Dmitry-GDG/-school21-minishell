/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p5_correct_cmds_and_args.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 07:54:53 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 21:25:52 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	my_init_tmp(t_data *data)
{
	data->tmp.firstflagdq = 0;
	data->tmp.firstflagq = 0;
	data->tmp.flagdq = 0;
	data->tmp.flagq = 0;
}

static void	my_correct_cmds_and_args3(t_data *data, char **str, int *i)
{
	int	j;

	if (!data->tmp.flagq)
		data->tmp.flagq = 1;
	else
		data->tmp.flagq = 0;
	j = *i;
	while ((*str)[++j])
		(*str)[j - 1] = (*str)[j];
	(*str)[j - 1] = '\0';
}

static void	my_correct_cmds_and_args2(t_data *data, char **str, int *i)
{
	int	j;

	if (!data->tmp.flagdq)
		data->tmp.flagdq = 1;
	else
		data->tmp.flagdq = 0;
	j = *i;
	while ((*str)[++j])
		(*str)[j - 1] = (*str)[j];
	(*str)[j - 1] = '\0';
	if ((*str)[*i] == 34)
		(*i)--;
}

static int	my_correct_cmds_and_args1(t_data *data, char **str)
{
	int		i;

	my_init_tmp(data);
	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == 34 && !data->tmp.flagq)
			my_correct_cmds_and_args2(data, str, &i);
		if ((*str)[i] == 39 && !data->tmp.flagdq)
		{
			my_correct_cmds_and_args3(data, str, &i);
			if ((*str)[i] == 34 || (*str)[i] == 39)
				i--;
		}
		if ((*str)[i] == 36 && !data->tmp.flagq)
		{
			i++;
			data->tmp.tt = (*str);
			(*str) = my_convert_env((*str), &i, data);
			free(data->tmp.tt);
			if (!(*str))
				return (7);
		}
	}
	return (0);
}

int	my_correct_cmds_and_args(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->qty_cmds)
	{
		my_correct_cmds_and_args1(data, &data->cmds[i]->cmd_bin);
		j = -1;
		while (data->cmds[i]->args[++j])
			my_correct_cmds_and_args1(data, &data->cmds[i]->args[j]);
	}
	return (0);
}
