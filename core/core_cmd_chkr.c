/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_cmd_chkr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarg <kmarg@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:00:33 by kmarg             #+#    #+#             */
/*   Updated: 2022/03/16 18:08:41 by kmarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	chk_cmd_exit(t_data *data, int i)
{
	if (i == 1)
		printf("minishell: %s: No such file or directory\n", \
		data->cmds[data->tmp.h]->cmd_bin);
	if (i == 2)
		printf("Malloc error\n");
	if (i == 3)
		printf("Fork error\n");
	data->exit_status = 127;
	exit (127);
}

char	*path_finder(t_data *data)
{
	char	**paths;

	paths = NULL;
	paths = ft_split(data->env[data->tmp.i]->value, ':');
	if (!paths)
		chk_cmd_exit(data, 2);
	data->tmp.i = 0;
	while (paths[++(data->tmp.j)])
	{
		paths[data->tmp.j] = ft_strjoin(paths[data->tmp.j], "/");
		if (!paths[data->tmp.j])
			chk_cmd_exit(data, 2);
		if (paths[data->tmp.j])
			free(paths[data->tmp.j]);
		paths[data->tmp.j] = ft_strjoin(paths[data->tmp.j], \
		data->cmds[data->tmp.h]->cmd_bin);
		if (!paths[data->tmp.j])
			chk_cmd_exit(data, 2);
		if (access(paths[data->tmp.j], F_OK) == 0)
			return (paths[data->tmp.j]);
		if (paths[data->tmp.j])
			free(paths[data->tmp.j]);
	}
	chk_cmd_exit(data, 1);
	exit (127);
}

char	*check_cmd(t_data *data)
{
	char	*paths;

	data->tmp.i = 0;
	paths = NULL;
	while (data->cmds[data->tmp.h]->cmd_bin[++data->tmp.i])
	{
		if (data->cmds[data->tmp.h]->cmd_bin[data->tmp.i] == '/')
		{
			if (access(data->cmds[data->tmp.h]->cmd_bin, F_OK) == 0)
				return (data->cmds[data->tmp.h]->cmd_bin);
			else
				chk_cmd_exit(data, 1);
		}
	}
	while (data->env[data->tmp.i] && \
	!ft_strnstr(data->env[data->tmp.i]->key, "PATH", 4))
		data->tmp.i++;
	if (data->tmp.i == data->qty_env)
		chk_cmd_exit(data, 1);
	data->tmp.j = -1;
	paths = path_finder(data);
	if (paths)
		return (paths);
	chk_cmd_exit(data, 1);
	exit (127);
}

int	remake_env(t_data *data)
{
	char	*tmp;

	data->envp = (char **)malloc(sizeof(char *) * (data->qty_env + 1));
	if (!data->envp)
		chk_cmd_exit(data, 2);
	data->tmp.i = -1;
	while (data->env[++data->tmp.i])
	{
		data->envp[data->tmp.i] = ft_strjoin(data->env[data->tmp.i]->key, "=");
		if (!data->envp[data->tmp.i])
			chk_cmd_exit(data, 2);
		tmp = data->envp[data->tmp.i];
		data->envp[data->tmp.i] = ft_strjoin(data->envp[data->tmp.i], \
	data->env[data->tmp.i]->value);
		free (tmp);
		if (!data->envp[data->tmp.i])
			chk_cmd_exit(data, 2);
	}
	data->envp[data->tmp.i] = NULL;
	return (0);
}

int	check_cd_left_pipe(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->qty_cmds)
	{
		if (!ft_strcmp(data->cmds[i]->cmd_bin, "cd") && \
		data->cmds[i]->delimiter_l)
			return (1);
	}
	return (0);
}
