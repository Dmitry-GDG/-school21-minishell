/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:46:18 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 07:48:00 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	my_echo2(t_data *data, char *str)
{
	data->exit_status %= 255;
	if (!ft_strcmp(str, "$?"))
		printf ("%d", data->exit_status);
	else
		printf("%s", str);
}

static void	my_echo1(t_data *data, char **arg)
{
	int	sign;
	int	i;

	sign = 0;
	i = -1;
	if (!(ft_strncmp(arg[0], "-n", 3)))
	{
		sign = 1;
		i = 0;
	}
	while (arg[++i] != NULL)
	{
		my_echo2(data, arg[i]);
		if (arg[i + 1] != NULL)
			printf (" ");
	}
	if (!sign)
		printf("\n");
}

int	my_echo(t_data *data, char **arg)
{
	if (!arg || !*arg)
	{
		printf("\n");
		data->exit_status = 0;
		return (0);
	}
	my_echo1(data, arg);
	data->exit_status = 0;
	return (0);
}
