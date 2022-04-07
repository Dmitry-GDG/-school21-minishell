/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 08:13:07 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 07:49:53 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_if_built2(t_data *data)
{
	int		i;
	char	**str;

	str = data->cmds[data->tmp.h]->args;
	i = -1;
	while (str[++i])
	{
		if (!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "export"))
		{
			if (my_export(data, str))
				return (10);
		}
		else if (!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "unset"))
		{
			if (my_unset(data, str))
				return (10);
		}
	}
	return (0);
}

static int	my_if_built1(t_data *data)
{
	if (!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "pwd"))
		return (my_pwd(data));
	else if (!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "echo"))
		return (my_echo(data, data->cmds[data->tmp.h]->args));
	else if (!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "cd"))
		return (my_cd(data, data->cmds[data->tmp.h]->args));
	else if (!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "export") && \
	!data->cmds[data->tmp.h]->args[0])
		return (my_export(data, data->cmds[data->tmp.h]->args));
	else if (!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "unset") && \
	!data->cmds[data->tmp.h]->args[0])
		printf("");
	else if ((!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "export")) || \
	(!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "unset")))
		return (my_if_built2(data));
	return (0);
}

int	my_if_built(t_data *data)
{
	int	err;

	if (!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "echo") || \
	!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "cd") || \
	!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "pwd") || \
	!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "env") || \
	!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "exit") || \
	!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "export") || \
	!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "unset"))
	{
		if (!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "exit"))
			my_exit(data, data->cmds[data->tmp.h]->delimiter_l);
		else if (!ft_strcmp(data->cmds[data->tmp.h]->cmd_bin, "env"))
			my_env(data);
		else
		{
			err = my_if_built1(data);
			if (err)
				return (err);
		}
		return (11);
	}
	return (0);
}
