#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	j = dst_len;
	if (dst_len < dstsize - 1 && dstsize)
	{
		while (*(src + i) != '\0' && dst_len + i < dstsize - 1)
		{
			*(dst + j) = *(src + i);
			i++;
			j++;
		}
		*(dst + j) = 0;
	}
	if (dst_len >= dstsize)
		dst_len = dstsize;
	return (dst_len + src_len);
}
