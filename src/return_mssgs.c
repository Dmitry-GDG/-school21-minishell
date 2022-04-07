/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_mssgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:48:55 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 18:00:54 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_print_mssg(char *mssg, t_data *data)
{
	write (2, mssg, ft_strlen(mssg));
	data->exit_status = 1;
	return (data->exit_status);
}

void	my_free_env(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->qty_env)
	{
		if (data->env[i] != NULL)
		{
			if (data->env[i]->key != NULL)
				free (data->env[i]->key);
			if (data->env[i]->value != NULL)
				free (data->env[i]->value);
			free (data->env[i]);
		}
	}
}

static void	my_return_mssg1(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->qty_cmds)
	{
		if (data->cmds[i])
		{
			if (data->cmds[i]->cmd)
				free (data->cmds[i]->cmd);
			j = -1;
			while (++j < data->cmds[i]->qty_args)
				free (data->cmds[i]->args[j]);
			if (data->cmds[i]->cmd_bin)
				free (data->cmds[i]->cmd_bin);
			j = -1;
			while (++j < data->cmds[i]->qty_redir_l)
				free (data->cmds[i]->redir_l[j]);
			j = -1;
			while (++j < data->cmds[i]->qty_redir_r)
				free (data->cmds[i]->redir_r[j]);
			free (data->cmds[i]);
		}
	}
}

int	my_return_mssg(t_data *data, int sign)
{
	int	i;

	if (sign > 1)
	{
		if (sign > 3)
		{
			if (sign > 4)
				my_return_mssg1(data);
			i = -1;
			while (++i < data->qty_quotes)
			{
				if (data->quotes[i])
					free (data->quotes[i]);
			}
		}
		if (data->cmd_line)
			free (data->cmd_line);
	}
	if (sign <= 10 || sign == 11 || sign == 90)
		my_free_env(data);
	if (sign <= 10)
		return (my_print_mssg ("malloc error\n", data));
	if (sign == 90)
		printf("\033[Aminishell$ exit\n");
	return (data->exit_status);
}

void	my_print_errors(t_data *data, int sign)
{
	if (sign == 1)
		my_print_mssg ("minishell: syntax error: unclosed quotes\n", data);
	if (sign == 2)
		my_print_mssg ("minishell: syntax error near unexpected token `|'\n", \
		data);
	if (sign == 3)
		my_print_mssg ("minishell: syntax error near unexpected token `||'\n", \
		data);
	if (sign == 4)
		my_print_mssg ("minishell: syntax error near unexpected token `&'\n", \
		data);
	if (sign == 5)
		my_print_mssg ("minishell: syntax error near unexpected token `<'\n", \
		data);
	if (sign == 6)
		my_print_mssg ("minishell: syntax error near unexpected token `>'\n", \
		data);
	if (sign == 7)
		my_print_mssg ("minishell: syntax error near unexpected token `&&'\n", \
		data);
}
