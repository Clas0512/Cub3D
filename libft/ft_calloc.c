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
