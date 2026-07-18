#ifndef _GET_NEXT_LINE_H
# define _GET_NEXT_LINE_H

# include <unistd.h> // need for read()
# include <stdlib.h> // neef for malloc() and free()

// compile without -D BUFFER_SIZE=<number>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char *get_next_line(int fd);

size_t ft_strlen(const char *s);
char *ft_strchr(const char *s, int c);
char *ft_strdup(const char *s);
char *ft_strjoin_free(char *s1, char *s2);

#endif
