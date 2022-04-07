/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 13:49:53 by trurgot           #+#    #+#             */
/*   Updated: 2022/02/16 17:26:39 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/errno.h>

void	*ft_calloc(size_t count, size_t size)
{
	void			*outp;
	unsigned long	i;
	size_t			mem;

	mem = count * size;
	if (count && size != (mem / count))
	{
		errno = ENOMEM;
		return (NULL);
	}
	outp = malloc(mem);
	if (outp == NULL)
		return (NULL);
	i = 0;
	while (i < mem)
	{
		((unsigned char *)outp)[i] = 0;
		i++;
	}
	return (outp);
}
