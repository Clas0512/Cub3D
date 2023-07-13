#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif


char	*ft_strdup(char	*str1);
char	*get_next_line(int fd);
char	*ft_strchr(char *str, int c);
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *str, char *buff);
char	*get_buff(int fd, char *str);
char	*get_returnline(char *str);
char	*dlt_line(char *str);
#endif
