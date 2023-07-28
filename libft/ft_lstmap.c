/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:29:41 by sakkus            #+#    #+#             */
/*   Updated: 2023/07/28 11:29:56 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_map;
	t_list	*new;

	lst_map = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (new)
			ft_lstadd_back(&lst_map, new);
		else
			ft_lstclear(&new, del);
		lst = lst->next;
	}
	return (lst_map);
}
