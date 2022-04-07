/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:00:47 by trurgot           #+#    #+#             */
/*   Updated: 2022/02/16 17:30:48 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*outp;
	unsigned long	len_s;

	if (!s)
		return (NULL);
	len_s = 0;
	while (s[len_s])
		len_s++;
	outp = (char *)malloc(sizeof(char) * (len_s + 1));
	if (!outp)
		return (NULL);
	outp[len_s] = '\0';
	while (len_s > 0)
	{
		outp[len_s - 1] = f(len_s - 1, s[len_s - 1]);
		len_s--;
	}
	return (outp);
}
