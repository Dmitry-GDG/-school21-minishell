/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parcing2_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 07:33:18 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/07 12:24:53 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_calc_pipes2(int i, char *str, int j)
{
	if (str[j] && str[j] == 124 && j != i + 1)
		return (2);
	j++;
	while (str[j] && str[j] == 32)
		j++;
	if (str[i] == 124 && str[i + 1] == 124 && str[j] == 124)
		return (3);
	if (str[i] == 124 && str[i + 1] == 124 && str[j] == 38)
		return (4);
	if (str[i] == 124 && str[i + 1] == 124 && str[j] == 60)
		return (5);
	if (str[i] == 124 && str[i + 1] == 124 && str[j] == 62)
		return (6);
	if (str[i] == 124 && str[j] == 38 && (str[i + 1] && str[i + 1] == 38))
		return (7);
	return (0);
}

static int	my_calc_pipes1(t_data *data, int i, char *str)
{
	int	j;
	int	err;

	j = 0;
	while (j < data->qty_quotes)
	{
		if (i > data->quotes[j]->first && i < data->quotes[j]->second)
			break ;
		else
			++j;
	}
	if (j == data->qty_quotes)
	{
		data->qty_pipes++;
		if ((str[i - 1] && str[i - 1] == 124) || (str[i + 1] && \
		str[i + 1] == 124))
			data->qty_pipes--;
		j = i + 1;
		while (str[j] && str[j] == 32)
			j++;
		err = my_calc_pipes2(i, str, j);
		if (err)
			return (err);
	}
	return (0);
}

static int	my_calc_pipes0(t_data *data)
{
	int		i;
	char	*str;
	int		err;

	i = 0;
	str = data->cmd_line;
	while (str[i] == 32)
		i++;
	if (str[i] == 124)
		return (2);
	if (str[i] == 38)
		return (4);
	i--;
	while (str[++i])
	{
		if (str[i] == 124)
		{
			err = my_calc_pipes1(data, i, str);
			if (err)
				return (err);
		}
	}
	return (0);
}

int	my_calc_pipes(t_data *data)
{
	int	err;

	err = my_calc_pipes0(data);
	if (err)
	{
		my_print_errors(data, err);
		return (1);
	}
	return (0);
}
