/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:47:31 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/10 15:58:53 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_fill_oldpwd(t_data *data, int i, char *str)
{
	data->env[i] = (t_env *)malloc(sizeof(t_env));
	if (!data->env[i])
		return (3);
	data->env[i]->key = ft_strdup("OLDPWD");
	if (!data->env[i]->key)
		return (3);
	data->env[i]->value = ft_strdup(str);
	if (!data->env[i]->value)
		return (3);
	data->env[i + 1] = NULL;
	return (0);
}

static int	my_delete_env2(t_data *data, char *tmp1)
{
	int		j;
	char	*tmp3;
	int		err;

	j = 0;
	while ((j < data->qty_env) && \
	(ft_strcmp(data->env[j]->key, "OLDPWD")))
		j++;
	if (j != data->qty_env)
	{
		tmp3 = data->env[j]->value;
		data->env[j]->value = ft_strdup(tmp1);
		free (tmp3);
		if (!data->env[j]->value)
			return (1);
	}
	else
	{
		err = my_fill_oldpwd(data, j, tmp1);
		if (err)
			return (err);
		data->qty_env++;
	}
	return (0);
}

static void	my_delete_env1(t_data *data, int i)
{
	char	*tmp2;

	tmp2 = data->env[i]->key;
	while (data->env[i] && (data->env[i + 1] != NULL))
	{
		data->env[i]->key = data->env[i + 1]->key;
		data->env[i]->value = data->env[i + 1]->value;
		i++;
	}
	free (tmp2);
	tmp2 = NULL;
	free (data->env[i]);
	data->env[i] = NULL;
	data->qty_env--;
}

static int	my_delete_env(t_data *data, char *tmp)
{
	int		i;
	char	*tmp1;
	int		err;

	i = -1;
	while (++i < data->qty_env)
	{
		if (!ft_strcmp(data->env[i]->key, tmp))
		{
			tmp1 = data->env[i]->value;
			my_delete_env1(data, i);
			if (!ft_strcmp(tmp, "PWD"))
			{
				err = my_delete_env2(data, tmp1);
				if (err)
					return (err);
			}
			free (tmp1);
			tmp1 = NULL;
		}
	}
	return (0);
}

int	my_unset(t_data *data, char **args)
{
	int	i;

	i = -1;
	while (args[++i] != NULL)
	{
		data->exit_status = 0;
		if (!args)
			return (0);
		if (my_delete_env(data, args[i]))
		{
			data->exit_status = 1;
			return (1);
		}
	}
	return (0);
}
