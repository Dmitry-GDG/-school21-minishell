/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p1_split_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:37:40 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 18:37:25 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	my_init_cmds(t_cmds *cmds)
{
	cmds->cmd = NULL;
	cmds->args[0] = NULL;
	cmds->qty_args = 0;
	cmds->delimiter_l = 0;
	cmds->delimiter_r = 0;
	cmds->redir_l[0] = NULL;
	cmds->qty_redir_l = 0;
	cmds->redir_r[0] = NULL;
	cmds->qty_redir_r = 0;
	cmds->cmd_bin = NULL;
	cmds->if_built = 0;
}

static void	my_split_cmds2(t_data *data, int *i, int *begin)
{
	char	*str;

	str = data->cmd_line;
	if (str[*i] == 124 && str[*i - 1] != 124 && str[*i + 1] != 124)
		data->cmds[data->qty_cmds]->delimiter_r = 1;
	if (data->qty_cmds > 0)
		data->cmds[data->qty_cmds]->delimiter_l = \
		data->cmds[data->qty_cmds - 1]->delimiter_r;
	data->qty_cmds++;
	*begin = *i + 1;
}

static int	my_split_cmds1(t_data *data, int *i, int *begin)
{
	int		j;
	char	*str;

	str = data->cmd_line;
	j = 0;
	while (j < data->qty_quotes)
	{
		if ((data->quotes[j]->first < *i) && (data->quotes[j]->second > *i))
			break ;
		else
			j++;
	}
	if (j == data->qty_quotes)
	{
		data->cmds[data->qty_cmds] = malloc(sizeof(t_cmds));
		if (!data->cmds[data->qty_cmds])
			return (5);
		my_init_cmds(data->cmds[data->qty_cmds]);
		data->cmds[data->qty_cmds]->cmd = \
		ft_substr(data->cmd_line, *begin, *i - *begin);
		if (!data->cmds[data->qty_cmds]->cmd)
			return (5);
		my_split_cmds2(data, i, begin);
	}
	return (0);
}

static int	my_split_cmds3(t_data *data, int *i, int *begin)
{
	data->cmds[data->qty_cmds] = malloc(sizeof(t_cmds));
	if (!data->cmds[data->qty_cmds])
		return (5);
	my_init_cmds(data->cmds[data->qty_cmds]);
	data->cmds[data->qty_cmds]->cmd = \
	ft_substr(data->cmd_line, *begin, *i - *begin);
	if (!data->cmds[data->qty_cmds]->cmd)
		return (5);
	if (data->qty_cmds > 0)
		data->cmds[data->qty_cmds]->delimiter_l = \
		data->cmds[data->qty_cmds - 1]->delimiter_r;
	data->qty_cmds++;
	data->cmds[data->qty_cmds] = NULL;
	return (0);
}

int	my_split_cmds(t_data *data)
{
	int		i;
	int		begin;
	char	*str;

	str = data->cmd_line;
	i = -1;
	begin = 0;
	while (str[++i])
	{
		while (str[i] && str[i] == 32)
			i++;
		if (str[i] && (str[i] == 124) && str[i + 1] && (str[i + 1] != 124) && \
		str[i - 1] && (str[i - 1] != 124))
		{
			if (my_split_cmds1(data, &i, &begin))
				return (5);
		}
	}
	if (my_split_cmds3(data, &i, &begin))
		return (5);
	return (0);
}

// int	my_split_cmds(t_data *data)
// {
// 	int		i;
// 	int		begin;
// 	char	*str;

// 	str = data->cmd_line;
// 	i = -1;
// 	begin = 0;
// 	while (str[++i])
// 	{
// 		while (str[i] && str[i] == 32)
// 			i++;
// 		if (str[i] && ((str[i] == 124) || (str[i] == 38 && str[i + 1] && 
// 		str[i + 1] == 38)))
// 		{
// 			if (my_split_cmds1(data, &i, &begin))
// 				return (5);
// 		}
// 	}
// 	if (my_split_cmds3(data, &i, &begin))
// 		return (5);
// 	return (0);
// }

// static void	my_split_cmds2(t_data *data, int *i, int *begin)
// {
// 	char	*str;

// 	str = data->cmd_line;
// 	if (str[*i] == 124 && str[*i - 1] != 124 && str[*i + 1] != 124)
// 		data->cmds[data->qty_cmds]->delimiter_r = 1;
// 	if (str[*i] == 124 && str[*i + 1] && str[*i + 1] == 124)
// 		data->cmds[data->qty_cmds]->delimiter_r = 2;
// 	if (str[*i] == 38 && str[*i + 1] && str[*i + 1] == 38)
// 		data->cmds[data->qty_cmds]->delimiter_r = 3;
// 	if (data->qty_cmds > 0)
// 		data->cmds[data->qty_cmds]->delimiter_l = 
// 		data->cmds[data->qty_cmds - 1]->delimiter_r;
// 	data->qty_cmds++;
// 	while (str[*i + 1] && (str[*i + 1] == 38 || str[*i + 1] == 124))
// 		(*i)++;
// 	*begin = *i + 1;
// }
