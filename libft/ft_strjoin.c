/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakkus <sakkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:30:30 by sakkus            #+#    #+#             */
/*   Updated: 2023/07/28 11:30:30 by sakkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*new_s;

	i = 0;
	if (!s1 || !s2)
		return (0);
	new_s = malloc((sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_s == 0)
		return (0);
	while (*s1)
		new_s[i++] = *s1++;
	while (*s2)
		new_s[i++] = *s2++;
	new_s[i] = 0;
	return (new_s);
}
