/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:19:37 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 17:52:34 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_chck_continues(char *str, t_data *data)
{
	int		i;
	char	*tmp;

	if (str[0] == '\0' && data->pipe_status)
		return (1);
	tmp = str;
	i = 0;
	while (tmp[i])
		i++;
	i--;
	while (tmp[i] == 32)
		i--;
	if ((tmp[i] == 124 && tmp[i - 1] && ((tmp[i - 1] != 124) || \
	(tmp[i - 1] == 124 && tmp[i - 2] && tmp[i - 2] != 124))) || \
	(tmp[i] == 38 && tmp[i - 1] && tmp[i - 1] == 38 && tmp[i - 2] && \
	tmp[i - 2] != 38))
	{
		data->pipe_status = 1;
		return (1);
	}
	return (0);
}

static char	*my_strcat(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	tmp = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		tmp[i] = s1[i];
		i++;
	}
	free (s1);
	tmp[i] = 32;
	i++;
	j = 0;
	while (s2[j] != '\0')
	{
		tmp[i + j] = s2[j];
		j++;
	}
	free (s2);
	tmp[i + j] = '\0';
	return (tmp);
}

int	minishell1(t_data *data)
{
	char	*str;
	char	*tmp;

	while (my_chck_continues(data->cmd_line, data))
	{
		str = readline("> ");
		if (!str)
		{
			data->exit_status = 258;
			data->pipe_status = 0;
			printf ("minishell: syntax error: unexpected end of file\n");
			break ;
		}
		tmp = data->cmd_line;
		data->cmd_line = my_strcat(tmp, str);
		if (!data->cmd_line)
			return (3);
	}
	return (0);
}

int	minishell2(t_data *data)
{
	int		err;

	err = my_parcing_data(data);
	if (err)
		return (err);
	err = exec_cmd(data);
	if (err)
		return (err);
	return (0);
}
