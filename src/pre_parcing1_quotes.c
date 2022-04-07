/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parcing1_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 09:06:39 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/07 12:24:46 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_is_only_space(char *str)
{
	unsigned long	i;

	i = 0;
	while (str[i] && str[i] == 32)
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

static int	my_unclosed_quotes1(t_data *data, int i)
{
	data->tmp.flagq++;
	if (data->tmp.flagq == 2)
	{
		data->quotes[data->qty_quotes] = malloc(sizeof(t_quotes));
		if (!data->quotes[data->qty_quotes])
			return (4);
		data->quotes[data->qty_quotes]->sign = 1;
		data->quotes[data->qty_quotes]->first = data->tmp.firstflagq;
		data->quotes[data->qty_quotes]->second = i;
		data->qty_quotes++;
		data->tmp.flagq = 0;
		if (data->tmp.firstflagdq && \
		data->tmp.firstflagq < data->tmp.firstflagdq)
		{
			data->tmp.flagdq = 0;
			data->tmp.firstflagdq = 0;
		}
		data->tmp.firstflagq = 0;
	}
	else
		data->tmp.firstflagq = i;
	return (0);
}

static int	my_unclosed_dquotes1(t_data *data, int i)
{
	data->tmp.flagdq++;
	if (data->tmp.flagdq == 2)
	{
		data->quotes[data->qty_quotes] = malloc(sizeof(t_quotes));
		if (!data->quotes[data->qty_quotes])
			return (4);
		data->quotes[data->qty_quotes]->sign = 2;
		data->quotes[data->qty_quotes]->first = data->tmp.firstflagdq;
		data->quotes[data->qty_quotes]->second = i;
		data->qty_quotes++;
		data->tmp.flagdq = 0;
		if (data->tmp.firstflagq && \
		data->tmp.firstflagdq < data->tmp.firstflagq)
		{
			data->tmp.flagq = 0;
			data->tmp.firstflagq = 0;
		}
		data->tmp.firstflagdq = 0;
	}
	else
		data->tmp.firstflagdq = i;
	return (0);
}

static int	my_unclosed_quotes(t_data *data)
{
	int		i;
	char	*str;

	data->tmp.firstflagdq = 0;
	data->tmp.firstflagq = 0;
	data->tmp.flagdq = 0;
	data->tmp.flagq = 0;
	str = data->cmd_line;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34)
		{
			if (my_unclosed_dquotes1(data, i))
				return (4);
		}
		if (str[i] == 39)
		{
			if (my_unclosed_quotes1(data, i))
				return (4);
		}
	}
	return (data->tmp.flagdq || data->tmp.flagq);
}

int	my_pre_parcing(t_data *data)
{
	int	err;

	if (my_is_only_space(data->cmd_line))
		return (1);
	err = my_unclosed_quotes(data);
	if (err > 1)
		return (err);
	if (err == 1)
	{
		my_print_errors(data, 1);
		return (1);
	}
	if (my_calc_pipes(data))
		return (1);
	if (my_chck_amp_and_redirs(data))
		return (1);
	return (0);
}
