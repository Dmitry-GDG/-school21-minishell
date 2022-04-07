/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 13:55:11 by trurgot           #+#    #+#             */
/*   Updated: 2022/02/16 17:30:23 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned long	i;
	unsigned long	j;
	char			*outp;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	outp = (char *)malloc(sizeof(char) * (i + 1));
	if (outp == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		outp[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		outp[i + j] = s2[j];
		j++;
	}
	outp[i + j] = '\0';
	return (outp);
}
