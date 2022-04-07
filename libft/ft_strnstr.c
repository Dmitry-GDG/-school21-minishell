/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 13:46:12 by trurgot           #+#    #+#             */
/*   Updated: 2022/02/16 17:31:00 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	char	*outp;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (i < (int)len && haystack[i])
	{
		if (haystack[i] == needle [0])
		{
			outp = &((char *)haystack)[i];
			j = 0;
			while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
				j++;
			if (needle[j] == '\0' && (i + j) <= (int)len)
				return (outp);
		}
		i++;
	}
	return (NULL);
}
