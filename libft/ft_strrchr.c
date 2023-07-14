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
