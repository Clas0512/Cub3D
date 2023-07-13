#include "get_next_line_bonus.h"

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*get_buff(int fd, char *str)
{
	int		rd;
	char	*buff;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	rd = 1;
	while (!ft_strchr(str, '\n') && rd != 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1 || (rd == 0 && (!str || !*str)))
		{
			free(buff);
			free(str);
			return (0);
		}
		buff[rd] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*returnline;
	static char	*str[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = get_buff(fd, str[fd]);
	if (!str[fd])
		return (0);
	returnline = get_returnline(str[fd]);
	str[fd] = dlt_line(str[fd]);
	return (returnline);
}
