/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 07:20:47 by trurgot           #+#    #+#             */
/*   Updated: 2022/02/16 17:28:23 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*outp;

	outp = (t_list *)malloc(sizeof(t_list));
	if (outp == NULL)
		return (NULL);
	outp->content = content;
	outp->next = NULL;
	return (outp);
}
