/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_hdc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarg <kmarg@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:23:38 by kmarg             #+#    #+#             */
/*   Updated: 2022/03/15 17:55:55 by kmarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	hdc_tmp(t_data *data, char tmpe[33][33], int m)
{
	int		super_file;
	char	*line;

	tmpe[data->tmp.i][m] = '\0';
	super_file = open("tmpx", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, tmpe[data->tmp.i]) == 0)
		{
			data->tmp.n--;
			break ;
		}
		write(super_file, line, ft_strlen(line));
		write(super_file, "\n", 1);
	}
	close(super_file);
	data->tmp.i++;
}

static void	hdc_exec(t_data *data)
{
	char	tmpe[33][33];
	int		m;
	int		j;

	data->tmp.i = 0;
	while (data->cmds[data->tmp.h]->redir_l[data->tmp.i])
	{
		j = 0;
		m = 0;
		while (data->cmds[data->tmp.h]->redir_l[data->tmp.i][j] != '\0')
		{
			if (data->cmds[data->tmp.h]->redir_l[data->tmp.i][j] != '<' \
	&& data->cmds[data->tmp.h]->redir_l[data->tmp.i][j] != ' ' \
	&& data->cmds[data->tmp.h]->redir_l[data->tmp.i][j] != '\0')
				tmpe[data->tmp.i][m++] = \
				data->cmds[data->tmp.h]->redir_l[data->tmp.i][j++];
			else
				j++;
		}
		hdc_tmp(data, tmpe, m);
	}
}

int	child_hdk(t_data *data)
{
	int	super_file;

	while (data->tmp.n != 0)
		hdc_exec(data);
	super_file = open("tmpx", O_RDONLY);
	unlink("tmpx");
	dup2(super_file, STDIN_FILENO);
	close(super_file);
	return (0);
}

int	calc_hdk(t_data *data)
{
	int	i;

	i = 0;
	data->tmp.n = 0;
	while (data->cmds[data->tmp.h]->redir_l[i] != NULL)
	{
		if (data->cmds[data->tmp.h]->redir_l[i][1] == '<')
			data->tmp.n++;
		i++;
	}
	return (data->tmp.n);
}

int	calc_hdk1(t_data *data)
{	
	int	i;
	int	h;

	data->tmp.hdk = 0;
	h = -1;
	while (++h < data->qty_cmds)
	{
		i = -1;
		while (data->cmds[h]->redir_l[++i] != NULL)
		{
			if (data->cmds[h]->redir_l[i][1] == '<')
				data->tmp.hdk++;
		}
	}
	return (data->tmp.hdk);
}
