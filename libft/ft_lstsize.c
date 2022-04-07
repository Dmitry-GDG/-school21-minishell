/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 07:21:51 by trurgot           #+#    #+#             */
/*   Updated: 2022/02/16 17:28:31 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		len_lst;

	len_lst = 0;
	tmp = lst;
	while (tmp)
	{
		len_lst++;
		tmp = tmp->next;
	}
	return (len_lst);
}
