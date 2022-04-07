/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_join_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarg <kmarg@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:10:07 by kmarg             #+#    #+#             */
/*   Updated: 2022/03/16 18:11:08 by kmarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*j_args1(char *str, t_data *data)
{
	char	*hz;
	char	*outp;

	if (!ft_strcmp(str, "$?"))
	{
		hz = str;
		data->exit_status %= 255;
		str = ft_itoa(data->exit_status);
		free(hz);
		if (!str)
			return (NULL);
	}
	outp = str;
	return (outp);
}

char	**join_args(t_data *data)
{
	char	**tmp3;
	char	**tmo4;
	int		i;
	int		j;

	tmp3 = data->cmds[data->tmp.h]->args;
	i = -1;
	while (tmp3 && tmp3[++i])
	{
		if (j_args1(tmp3[i], data) == NULL)
			return (NULL);
	}
	tmo4 = malloc(sizeof(char *) * (i + 2));
	if (!tmo4)
		return (NULL);
	tmo4[i + 1] = NULL;
	i = 0;
	tmo4[i++] = data->cmds[data->tmp.h]->cmd_bin;
	if (tmp3)
	{
		j = -1;
		while (tmp3[++j])
			tmo4[i++] = tmp3[j];
	}
	return (tmo4);
}

void	signal_quit1(int c)
{
	(void) c;
	write(2, "^\\Quit: 3\n\n", 11);
	exit (131);
}

void	hdk_wait(t_data *data)
{
	int	a;

	if (calc_hdk(data))
	{
		if (data->tmp.n)
			wait(&a);
	}
}
