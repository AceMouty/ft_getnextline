#include "get_next_line.h"

/*
* This is a helper that lets our stash grow
*
* Its job
* - take old stash
* - take newly read buffer
* - join them together
* - free the old stash
* - return the new joined string
*
* ex: stash = ft_strjoin_free(stash, buffer);
* 
* this means:
* - stash used to be: "hello"
* - buffer contains:  "\nworld"
* - new stash:        "hello\nworld"
* - old stash:        freed
*/
char	*ft_strjoin_free(char *s1, char *s2)
{
  char *joined;
  size_t i;
  size_t j;

  if(!s2)
    return NULL;

  joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
  if(!joined){
    free(s1);
    return NULL;
  }

  i = 0;
  while(s1 && s1[i])
  {
    joined[i] = s1[i];
    i++;
  }

  j = 0;
  while(s2[j])
  {
    joined[i + j] = s2[j];
    j++;
  }

  joined[i + j] = '\0';
  free(s1);

  return joined;
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	target;

	if (!s)
		return (NULL);
	target = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == target)
			return ((char *)&s[i]);
		i++;
	}
	if (target == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	i;

	if (!s)
		return (NULL);
	copy = malloc(ft_strlen(s) + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

