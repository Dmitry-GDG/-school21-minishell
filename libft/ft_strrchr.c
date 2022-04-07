/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 13:38:40 by trurgot           #+#    #+#             */
/*   Updated: 2022/02/16 17:31:07 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		tmp;
	char	*outp;

	i = 0;
	tmp = -1;
	outp = (char *)s;
	while (outp[i])
	{
		if (outp[i] == (char) c)
		{
			tmp = i;
		}
		i++;
	}
	if ((char) c == '\0')
		tmp = i;
	if (tmp == -1)
		return (NULL);
	else
		return (&outp[tmp]);
}
