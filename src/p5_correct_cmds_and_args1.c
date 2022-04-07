/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p5_correct_cmds_and_args1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 09:35:16 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 21:21:39 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*my_convert_env2(char *str, int *i, t_data *data)
{
	char	tmp1[1000];
	int		m;
	int		l;

	m = -1;
	while (++m < *i - 1)
		tmp1[m] = str[m];
	l = -1;
	while (data->env[data->tmp.k]->value[++l])
		tmp1[m + l] = data->env[data->tmp.k]->value[l];
	m += l;
	l = -1;
	while (str[(*i) + 1 + data->tmp.p + (++l)])
		tmp1[m + l] = str[(*i) + 1 + data->tmp.p + l];
	tmp1[m + l] = '\0';
	return (ft_strdup(tmp1));
}

static char	*my_convert_env1(char *str, int *i, t_data *data)
{
	char	*outp;

	if ((str[*i + 1 + data->tmp.p] && (str[*i + 1 + data->tmp.p] == 32 || \
	str[*i + 1 + data->tmp.p] == 34 || str[*i + 1 + data->tmp.p] == 39)) || \
	str[*i + 1 + data->tmp.p] == '\0')
	{
		outp = my_convert_env2(str, i, data);
		if (!outp)
			return (NULL);
		*i = *i + data->tmp.p + 1;
		return (outp);
	}
	else
	{
		(*i)--;
		return (ft_substr(str, 0, *i));
	}
}

char	*my_convert_env(char *str, int *i, t_data *data)
{
	char	*tmp;

	data->tmp.p = -1;
	while (str[*i + (++data->tmp.p)])
	{
		tmp = ft_substr(str, (*i), data->tmp.p + 1);
		if (!tmp)
			return (NULL);
		data->tmp.k = -1;
		while (++data->tmp.k < data->qty_env)
		{
			if (!ft_strcmp(tmp, data->env[data->tmp.k]->key))
			{
				free (tmp);
				return (my_convert_env1(str, i, data));
			}
		}
		free (tmp);
	}
	return (str);
}

// char	*my_convert_env(char *str, int *i, t_data *data)
// {
// 	char	*tmp;

// 	data->tmp.p = -1;
// 	while (str[*i + (++data->tmp.p)])
// 	{
// 		tmp = ft_substr(str, (*i), data->tmp.p + 1);
// 		if (!tmp)
// 			return (NULL);
// 		data->tmp.k = -1;
// 		while (++data->tmp.k < data->qty_env)
// 		{
// 			if (!ft_strcmp(tmp, data->env[data->tmp.k]->key))
// 			{
// 				free (tmp);
// 				return (my_convert_env1(str, i, data, &tmp));
// 			}
// 		}
// 		free (tmp);
// 	}
// 	return (str);
// }
