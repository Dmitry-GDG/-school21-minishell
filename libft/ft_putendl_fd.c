/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:05:25 by trurgot           #+#    #+#             */
/*   Updated: 2022/02/16 17:29:24 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	unsigned long	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &(s[i]), 1);
			i++;
		}
		write (fd, "\n", 1);
	}
}
