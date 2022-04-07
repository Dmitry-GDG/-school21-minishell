/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:47:07 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 07:48:19 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_add_env1(char *args, unsigned long *i, char *tmp)
{
	int	j;

	*i = -1;
	while (args[++(*i)] && args[*i] != 61)
		tmp[*i] = args[*i];
	if ((*i) == ft_strlen(args))
		return (0);
	if (args[(*i) - 1] == 32)
	{
		j = -1;
		while (args[(++j) + (*i) - 1])
			tmp[j] = args[j + (*i) - 1];
		tmp[j] = '\0';
		printf ("minishell: export: '%s': not a valid identifier\n", tmp);
		return (11);
	}
	tmp[*i] = '\0';
	return (1);
}

static int	my_add_env2(char *args, int i, t_env *env, char *tmp)
{
	char	*tmp1;

	if (!ft_strcmp(tmp, env->key))
	{
		tmp1 = env->value;
		env->value = ft_substr(args, i + 1, ft_strlen(args) - i - 1);
		free(tmp1);
		if (!env->value)
			return (7);
		return (0);
	}
	return (0);
}

static int	my_add_env5(t_data *data, char *tmp)
{
	free (tmp);
	data->flag_env = 0;
	data->env[data->qty_env] = NULL;
	return (0);
}

static int	my_add_env(t_data *data, char *args)
{
	unsigned long	i;
	int				j;
	char			*tmp;
	int				err;

	tmp = (char *)malloc(sizeof (char) * 101);
	if (!tmp)
		return (7);
	err = my_add_env1(args, &i, tmp);
	if (err != 1)
		return (err);
	j = -1;
	while (++j < data->qty_env)
	{
		if (!ft_strcmp(tmp, data->env[j]->key))
			data->flag_env = 1;
		if (my_add_env2(args, i, data->env[j], tmp))
			return (7);
	}
	if (data->flag_env != 1)
	{
		if (my_add_env3(data, args))
			return (7);
	}
	return (my_add_env5(data, tmp));
}

int	my_export(t_data *data, char **args)
{
	int	i;
	int	err;

	data->exit_status = 1;
	err = 0;
	if (!args[0])
	{
		i = -1;
		while (data->env[++i])
			printf ("declare -x %s=\"%s\"\n", data->env[i]->key, \
			data->env[i]->value);
	}
	else
	{
		i = -1;
		while (args[++i] != NULL)
		{
			err = my_add_env(data, args[i]);
			if (err > 1 && err != 11)
				return (7);
		}
	}
	if (err == 0)
		data->exit_status = 0;
	return (0);
}
