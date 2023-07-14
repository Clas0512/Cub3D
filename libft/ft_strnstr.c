#include "libft.h"

char	*ft_strnstr(const char *haystacks, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	h = 0;
	if (needle[0] == '\0')
		return ((char *)haystacks);
	while (haystacks[h] != '\0')
	{
		n = 0;
		while (haystacks[h + n] == needle[n] && (h + n) < len)
		{
			if (haystacks[h + n] == '\0' && needle[n] == '\0')
				return ((char *)&haystacks[h]);
			n++;
		}
		if (needle[n] == '\0')
			return ((char *)haystacks + h);
		h++;
	}
	return (0);
}
