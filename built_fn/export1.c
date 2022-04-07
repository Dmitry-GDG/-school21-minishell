/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:38:05 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/10 17:50:58 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_add_env4(t_data *data, char *args)
{
	int	j;
	int	tmp;

	j = 0;
	while (args[j] != '=')
		j++;
	data->env[data->qty_env]->key = (char *)malloc(sizeof(char) * (j + 1));
	if (!data->env[data->qty_env]->key)
		return (3);
	j = -1;
	while (args[++j] != '=')
		data->env[data->qty_env]->key[j] = args[j];
	data->env[data->qty_env]->key[j] = '\0';
	tmp = j + 1;
	while (args[tmp])
		tmp++;
	data->env[data->qty_env]->value = (char *)malloc(sizeof(char) * (tmp - j));
	if (!data->env[data->qty_env]->value)
		return (3);
	tmp = -1;
	while (args[++tmp + j + 1])
		data->env[data->qty_env]->value[tmp] = args[tmp + j + 1];
	data->env[data->qty_env]->value[tmp] = '\0';
	return (0);
}

int	my_add_env3(t_data *data, char *args)
{
	data->env[data->qty_env] = (t_env *)malloc(sizeof(t_env));
	if (!data->env[data->qty_env])
		return (7);
	if (my_add_env4(data, args))
		return (7);
	data->qty_env++;
	return (0);
}
