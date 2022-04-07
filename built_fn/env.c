/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:46:46 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/08 13:36:06 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	my_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->env[++i])
		printf ("%s=%s\n", data->env[i]->key, data->env[i]->value);
	data->exit_status = 0;
}
