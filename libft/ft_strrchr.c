/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:30:40 by sakkus            #+#    #+#             */
/*   Updated: 2023/07/28 11:30:41 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			ptr = (char *)(str + i);
		i++;
	}
	if (str[i] == (char)c)
		ptr = (char *)(str + i);
	return (ptr);
}
