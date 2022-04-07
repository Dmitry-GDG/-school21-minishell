/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 13:44:37 by trurgot           #+#    #+#             */
/*   Updated: 2022/02/16 17:28:44 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((i < (unsigned int) n) && \
			((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
	{
		i++;
	}
	if (i == (unsigned int) n)
	{
		return (0);
	}
	else
	{
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
}
