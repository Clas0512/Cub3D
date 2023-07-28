/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:29:23 by sakkus            #+#    #+#             */
/*   Updated: 2023/07/28 11:29:24 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nbyte, size_t size)
{
	void	*dst;

	dst = malloc(size * nbyte);
	if (!dst)
		return (0);
	ft_memset(dst, 0, size * nbyte);
	return (dst);
}
