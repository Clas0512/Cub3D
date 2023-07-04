#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
char	*ft_strchrr(char *str, int c);
size_t	ft_strllen(char *str);
char	*ft_strjjoin(char *str, char *buff);
char	*get_returnline(char *str);
char	*dlt_line(char *str);
#endif
