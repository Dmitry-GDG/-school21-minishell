/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:45:06 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/10 15:48:17 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_update_env1(t_data *data, char *str, int i)
{
	data->env[i] = (t_env *)malloc(sizeof(t_env));
	if (!data->env[i])
		return (3);
	data->env[i]->key = ft_strdup(str);
	if (!data->env[i]->key)
		return (3);
	data->env[i + 1] = NULL;
	data->qty_env++;
	return (0);
}

static int	my_update_env(t_data *data, char *mypwd, char *str)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while ((i < data->qty_env) && ft_strcmp(data->env[i]->key, str))
		i++;
	if (i == data->qty_env)
	{
		if (my_update_env1(data, str, i))
			return (3);
	}
	else
		tmp = data->env[i]->value;
	data->env[i]->value = ft_strdup(mypwd);
	if (tmp)
		free (tmp);
	if (!data->env[i]->value)
		return (3);
	return (0);
}

static int	my_home_dir(t_data *data)
{
	int		i;

	i = 0;
	while ((i < data->qty_env) && ft_strcmp(data->env[i]->key, "HOME"))
		i++;
	if (i == data->qty_env)
	{
		printf("minishell$ cd: HOME not set\n");
		return (1);
	}
	else
	{
		if (chdir(data->env[i]->value) == -1)
		{
			printf("minishell$ cd: No such file or directory\n");
			return (1);
		}
	}
	return (0);
}

int	my_cd(t_data *data, char **str)
{
	char	oldpwd[1000];
	char	newpwd[1000];

	data->exit_status = 1;
	if (!getcwd(oldpwd, 1000))
		return (11);
	if (!str || !*str || !ft_strcmp(str[0], "~"))
	{
		if (my_home_dir(data))
			return (11);
	}
	else
	{
		if (chdir(str[0]) == -1)
		{
			printf("minishell$ cd: No such file or directory\n");
			return (11);
		}
	}
	if (!getcwd(newpwd, 1000))
		return (11);
	data->exit_status = 0;
	return (my_update_env(data, newpwd, "PWD") || \
	my_update_env(data, oldpwd, "OLDPWD"));
}
