/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 07:12:36 by trurgot           #+#    #+#             */
/*   Updated: 2022/02/16 17:27:53 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	while (tmp->next)
	{
		tmp2 = tmp->next;
		tmp->next = NULL;
		del(tmp->content);
		tmp->content = NULL;
		free (tmp);
		tmp = tmp2;
	}
	del(tmp->content);
	tmp->content = NULL;
	free (tmp);
	*lst = NULL;
}
