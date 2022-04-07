/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parcing0_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:48:06 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 07:53:38 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_fill_env1(t_data *data, char **envp, int i)
{
	int	j;
	int	tmp;

	j = 0;
	while (envp[i][j] != '=')
		j++;
	data->env[i]->key = (char *)malloc(sizeof(char) * (j + 1));
	if (!data->env[i]->key)
		return (2);
	j = -1;
	while (envp[i][++j] != '=')
		data->env[i]->key[j] = envp[i][j];
	data->env[i]->key[j] = '\0';
	tmp = j + 1;
	while (envp[i][tmp])
		tmp++;
	data->env[i]->value = (char *)malloc(sizeof(char) * (tmp - j));
	if (!data->env[i]->value)
		return (2);
	tmp = -1;
	while (envp[i][++tmp + j + 1])
		data->env[i]->value[tmp] = envp[i][tmp + j + 1];
	data->env[i]->value[tmp] = '\0';
	return (0);
}

static int	my_correct_shlvl1(t_data *data, int i)
{
	data->env[i] = (t_env *)malloc(sizeof(t_env));
	if (!data->env[i])
		return (2);
	data->env[i]->key = ft_strdup("SHLVL");
	if (!data->env[i]->key)
		return (2);
	data->env[i]->value = ft_strdup("1");
	if (!data->env[i]->value)
		return (2);
	data->qty_env++;
	return (0);
}

static int	my_correct_shlvl(t_data *data)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (i < data->qty_env && ft_strcmp(data->env[i]->key, "SHLVL"))
		i++;
	if (i == data->qty_env)
	{
		if (my_correct_shlvl1(data, i))
			return (2);
	}
	else
	{
		tmp = data->env[i]->value;
		data->env[i]->value = ft_itoa(ft_atoi(tmp) + 1);
		if (!data->env[i]->value)
			return (2);
		free (tmp);
	}
	return (0);
}

int	my_fill_env(t_data *data, char **envp)
{
	int	i;
	int	err;

	data->exit_status = 1;
	data->qty_env = 0;
	while (envp[data->qty_env])
		data->qty_env++;
	i = -1;
	while (++i < data->qty_env)
	{
		data->env[i] = (t_env *)malloc(sizeof(t_env));
		if (!data->env[i])
			return (2);
		err = my_fill_env1(data, envp, i);
		if (err)
			return (err);
	}
	data->env[i] = NULL;
	err = my_correct_shlvl(data);
	if (err)
		return (err);
	data->exit_status = 0;
	return (0);
}
