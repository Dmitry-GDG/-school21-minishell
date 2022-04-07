/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parcing3_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 10:04:51 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 20:40:23 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	my_chck_amp_and_redirs1(t_data *data, int *if_shield, int i)
{
	int	j;

	j = 0;
	while (j < data->qty_quotes)
	{
		if ((data->quotes[j]->first > i) || (data->quotes[j]->second < i))
			j++;
		else
		{
			*if_shield = 1;
			break ;
		}
	}
}

static int	my_chck_amp_and_redirs2(int i, int prev, char c, t_data *data)
{
	if ((i != prev + 1) && (c == 124))
	{
		my_print_errors(data, 2);
		return (2);
	}
	if ((i != prev + 1) && (c == 38))
	{
		my_print_errors(data, 4);
		return (4);
	}
	if ((i != prev + 1) && (c == 60))
	{
		my_print_errors(data, 5);
		return (5);
	}
	if ((i != prev + 1) && (c == 62))
	{
		my_print_errors(data, 6);
		return (6);
	}
	return (0);
}

int	my_chck_amp_and_redirs(t_data *data)
{
	char	*str;
	int		i;
	int		prev;
	int		if_shield;

	str = data->cmd_line;
	if_shield = 0;
	i = -1;
	while (str[++i])
	{
		while (str[i] && str[i] != 38 && str[i] != 60 && str[i] != 62)
			i++;
		if (str[i])
			my_chck_amp_and_redirs1(data, &if_shield, i);
		if (!if_shield)
		{
			prev = i;
			++i;
			while (str[i] && str[i + 1] && str[i] == ' ')
				i++;
			if (my_chck_amp_and_redirs2(i, prev, str[i], data))
				return (1);
		}
	}
	return (0);
}
