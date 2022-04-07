/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p3_chck_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 09:33:39 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/11 07:52:18 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	my_chck_redirections2(t_data *data, int *j, int i)
{
	if ((data->cmds[i]->cmd[(*j)] == 60 || data->cmds[i]->cmd[(*j)] == 62) && \
	(!(data->tmp.quot % 2) && !(data->tmp.dquot % 2)))
	{
		if (data->cmds[i]->cmd[(*j)] == 60)
			data->tmp.sig = 1;
		if (data->cmds[i]->cmd[(*j)] == 62)
			data->tmp.sig = 2;
		(*j)++;
		if (((data->cmds[i]->cmd[(*j)] == 60) || \
		(data->cmds[i]->cmd[(*j)] == 62)) && data->cmds[i]->cmd[(*j) + 1])
			(*j)++;
	}
	else
		(*j)++;
}

static int	my_chck_redirections1(t_data *data, int *j, int i)
{
	if (((data->cmds[i]->cmd[(*j)] == 32 || data->cmds[i]->cmd[(*j)] == 60 || \
	data->cmds[i]->cmd[(*j)] == 62) && (!(data->tmp.quot % 2) && \
	!(data->tmp.dquot % 2))) || data->cmds[i]->cmd[(*j) + 1] == '\0')
	{
		if (data->cmds[i]->cmd[(*j) + 1] == '\0')
		{
			if (my_fill_redirs(data, (*j), i))
				return (5);
			return (1);
		}
		else if ((*j) - 1 >= data->tmp.begin && \
		data->cmds[i]->cmd[(*j) - 1] != 60 && data->cmds[i]->cmd[(*j) - 1] != \
		62 && data->cmds[i]->cmd[(*j) - 1] != 32)
		{
			if (my_fill_redirs(data, (*j) - 1, i))
				return (5);
			data->tmp.sig = 0;
			while (data->cmds[i]->cmd[(*j)] == 32 && \
			data->cmds[i]->cmd[(*j) + 1])
				(*j)++;
			data->tmp.begin = (*j);
			(*j)--;
		}
	}
	return (0);
}

static void	my_init_redirs_routine(t_data *data, int *j)
{
	data->tmp.begin = 0;
	data->tmp.sig = 0;
	data->tmp.quot = 0;
	data->tmp.dquot = 0;
	*j = 0;
}

int	my_chck_redirections(t_data *data)
{
	int	i;
	int	j;
	int	err;

	i = -1;
	while (data->cmds[++i])
	{
		my_init_redirs_routine(data, &j);
		while (data->cmds[i]->cmd[j] != '\0')
		{
			if (data->cmds[i]->cmd[j] == 39)
				data->tmp.quot++;
			if (data->cmds[i]->cmd[j] == 34)
				data->tmp.dquot++;
			err = my_chck_redirections1(data, &j, i);
			if (err == 1)
				break ;
			if (err == 5)
				return (5);
			my_chck_redirections2(data, &j, i);
		}
	}
	return (0);
}
