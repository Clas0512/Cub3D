#include "get_next_line_bonus.h"

char	*get_returnline(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

size_t	ft_strlen(char *str)
{
	size_t	c;

	c = 0;
	if (!str)
		return (0);
	while (str[c] != '\0')
		c++;
	return (c);
}

char	*dlt_line(char *str)
{
	int		c;
	int		i;
	char	*pstr;

	c = 0;
	while (str[c] && str[c] != '\n')
		c++;
	if (!str[c])
	{
		str[0] = 0;
		return (str);
	}
	pstr = (char *)malloc(sizeof(char) * (ft_strlen(str) - c + 1));
	if (!pstr)
		return (NULL);
	c++;
	i = 0;
	while (str[c])
		pstr[i++] = str[c++];
	pstr[i] = '\0';
	free(str);
	return (pstr);
}

char	*ft_strjoin(char *str, char *buff)
{
	size_t	c;
	size_t	i;
	char	*pstr;

	if (!str)
	{
		str = malloc(1 * sizeof(char));
		str[0] = '\0';
	}
	pstr = malloc(sizeof(char) * ((ft_strlen(str)) + ft_strlen(buff) + 1));
	if (pstr == NULL)
		return (NULL);
	c = -1;
	i = 0;
	while (str[++c] != '\0')
		pstr[c] = str[c];
	while (buff[i] != '\0')
		pstr[c++] = buff[i++];
	pstr[c] = '\0';
	free(str);
	return (pstr);
}
