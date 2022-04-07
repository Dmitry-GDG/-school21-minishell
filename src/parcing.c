/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:48:45 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 18:35:32 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*my_substr(char *s)
{
	char	*outp;
	size_t	len_outp;
	size_t	i;
	size_t	j;

	len_outp = ft_strlen(s);
	while (len_outp - 1 && s[len_outp - 1] == 32)
		len_outp--;
	i = 0;
	while (s[i] && s[i] == 32)
		i++;
	len_outp -= i;
	outp = (char *)malloc(sizeof(char) * (len_outp + 1));
	if (outp == NULL)
		return (NULL);
	j = -1;
	while (++j < len_outp)
		outp[j] = s[j + i];
	outp[j] = '\0';
	free (s);
	return (outp);
}

static int	my_correct_data(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->qty_cmds)
	{
		data->cmds[i]->cmd = my_substr(data->cmds[i]->cmd);
		if (!data->cmds[i]->cmd)
			return (7);
	}
	return (0);
}

int	my_parcing_data(t_data *data)
{
	int	i;

	i = my_pre_parcing(data);
	if (i == 1)
		return (0);
	if (i > 1)
		return (i);
	i = my_split_cmds(data);
	if (i)
		return (i);
	if (my_correct_data(data))
		return (7);
	if (my_chck_redirections(data))
		return (5);
	if (my_correct_cmds_and_args(data))
		return (7);
	return (0);
}
