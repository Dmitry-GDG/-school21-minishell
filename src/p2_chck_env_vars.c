/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p2_chck_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:22:18 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/11 09:28:37 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_chck_env_vars4(char *outp, int *start_o, char *value)
{
	int		l;

	outp[(*start_o)++] = 32;
	l = 0;
	while (value[l])
	{
		outp[(*start_o)++] = value[l];
		l++;
	}
	outp[(*start_o)++] = 32;
	return (1);
}

static void	my_chck_env_vars3(t_data *data, char *outp, int *start_o, char *tmp)
{
	int		m;
	int		sign;
	int		l;

	m = -1;
	sign = 0;
	while (data->env[++m])
	{
		if (!ft_strcmp(tmp, data->env[m]->key))
			sign = my_chck_env_vars4(outp, start_o, data->env[m]->value);
	}
	if (!sign)
	{
		outp[(*start_o)++] = 36;
		l = -1;
		while (tmp[++l])
			outp[(*start_o)++] = tmp[l];
	}
}

static void	my_chck_env_vars2(t_data *data, int i, int *j, char *tmp)
{
	int		k;

	k = -1;
	while (data->cmds[i]->cmd[*j + (++k)] && \
	data->cmds[i]->cmd[*j + k] != 36 && data->cmds[i]->cmd[*j + k] != 32 \
	&& data->cmds[i]->cmd[*j + k] != 60 && data->cmds[i]->cmd[*j + k] != 62)
		tmp[k] = data->cmds[i]->cmd[*j + k];
	tmp[k] = '\0';
	*j = *j + k - 1;
}

static int	my_chck_env_vars1(t_data *data, int i, char *outp, \
int *start_o)
{
	int		j;
	char	*tmp;

	j = -1;
	while (data->cmds[i]->cmd[++j])
	{
		tmp = (char *)malloc(sizeof(char) * 101);
		if (!tmp)
		{
			free (outp);
			return (1);
		}
		if (data->cmds[i]->cmd[j] != 36)
			outp[(*start_o)++] = data->cmds[i]->cmd[j];
		else if (data->cmds[i]->cmd[++j])
		{
			my_chck_env_vars2(data, i, &j, tmp);
			my_chck_env_vars3(data, outp, start_o, tmp);
		}
		free (tmp);
	}
	return (0);
}

int	my_chck_env_vars(t_data *data)
{
	int		i;
	int		start_o;
	char	*tmp1;
	char	*outp;

	i = -1;
	while (data->cmds[++i])
	{
		outp = (char *)malloc(sizeof(char) * 1000);
		if (!outp)
			return (1);
		start_o = 0;
		if (my_chck_env_vars1(data, i, outp, &start_o))
			return (1);
		outp[start_o] = '\0';
		tmp1 = data->cmds[i]->cmd;
		data->cmds[i]->cmd = outp;
		free (tmp1);
	}
	return (0);
}
