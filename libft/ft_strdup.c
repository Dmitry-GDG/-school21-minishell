/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 13:51:04 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/05 08:41:28 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*outp;
	unsigned long	i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	outp = malloc((i + 1) * sizeof(char));
	if (outp == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		outp[i] = s1[i];
		i++;
	}
	outp[i] = '\0';
	return (outp);
}
