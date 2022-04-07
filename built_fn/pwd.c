/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:47:19 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 07:49:32 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	my_pwd(t_data *data)
{
	char	dir[1000];

	if (!getcwd(dir, 1000))
	{
		data->exit_status = 1;
		return (11);
	}
	printf ("%s\n", dir);
	data->exit_status = 0;
	return (0);
}
