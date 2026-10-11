#ifndef GET_NEXT_LINE_UTILS_H
# define GET_NEXT_LINE_UTILS_H

# include <unistd.h> // needed for read()
# include <stdlib.h> // needed for malloc() and free()
                     //
// used when compiled without -D BUFFER_SIZE=<number>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strdup(const char *s);
char	*gnl_strjoin_free(char *s1, char *s2);

#endif
