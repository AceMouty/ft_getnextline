#include "get_next_line.h"

static char *read_into_stash(int fd, char *stash);
static char *extract_line(char *stash);
static char *trim_stash(char *stash);

/*
* get_next_line flow
*
* - read into stash
* - extract one line
* - trim stash so only leftovers remain
* - return line
*/
char *get_next_line(int fd)
{
  static char *stash;
  char *line;

  if(fd < 0 || BUFFER_SIZE <= 0)
    return NULL;

  stash = read_into_stash(fd, stash);
  if(!stash)
    return NULL;

  line = extract_line(stash);
  if(!line)
  {
    free(stash);
    stash = NULL;
    return NULL;
  }

  stash = trim_stash(stash);
  return line;
}

/* get data from read into stash
*
* we need to..
* - read chunks from fd
* - append chunks into stash
* - stop when stash contains '\n'
* - or stop when read() reaches EOF
*
* this gives us the raw material needed to return a line
*/
static char *read_into_stash(int fd, char *stash)
{
  char *buffer;
  size_t bytes_read;

  // we need +1 for null termination
  buffer = malloc((size_t)BUFFER_SIZE + 1);
  if(!buffer)
  {
    free(stash);
    return NULL;
  }

  bytes_read = 1; // allow loop entry
  while(!ft_strchr(stash, '\n') && bytes_read > 0)
  {
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if(bytes_read < 0)
    {
      free(buffer);
      free(stash);
      return NULL;
    }

    buffer[bytes_read] = '\0';
    if(bytes_read > 0)
    {
      stash = ft_strjoin_free(stash, buffer);
      if(!stash)
      {
        free(buffer);
        return NULL;
      }
    }
  }

  free(buffer);
  return stash;
}

/* we need to extract out a line
*
* ex: 
* stash: "hello\nworld\nabc"
* return: "hello\n"
*
*/
static char *extract_line(char *stash)
{
  char *line;
  size_t i;

  if(!stash || stash[0] == '\0')
    return NULL;

  // first find the len of the line
  // i will be the number of characters we need to alloc
  i = 0;
  while(stash[i] && stash[i] != '\n')
    i++;
  if(stash[i] == '\n')
    i++;

  // +1 for null termination
  line = malloc(i + 1);
  if(!line)
    return NULL;

  i = 0;
  while(stash[i] && stash[i] != '\n')
  {
    line[i] = stash[i];
    i++;
  }

  if(stash[i] == '\n')
  {
    line[i] = stash[i];
    i++;
  }

  line[i] = '\0';
  return line;
}

/*
* remove the line that gets extracted
* from extract_line
*
*/
static char *trim_stash(char *stash)
{
  char *new_stash;
  size_t i;
  size_t j;

  if(!stash)
    return NULL;

  /*
  * given: stash = "hello\nworld\nadbc"
  * 
  * we need to find the first instance of \n 
  * resulting in
  *
  * "hello\nworld\nadbc"
  *       ^
  *       i
  */
  i = 0;
  while(stash[i] && stash[i] != '\n')
    i++;

  // check if at end of stash with no new line eg "abc"
  if(!stash[i])
  {
    free(stash);
    return NULL;
  }

  /* now we need to skip over the \n resulting in
  * "hello\nworld\nadbc"
  *         ^
  *         i
  */
  i++;

  // check if at end of stash with new line delimeter 'abc\n'
  if(!stash[i])
  {
    free(stash);
    return NULL;
  }

  /* now alloc a new stash providing the offset we need
  * effetively discarding the hello\n portion of the current stash
  * 
  * +1 for null termination
  */
  new_stash = malloc(ft_strlen(stash + i) + 1);
  if(!new_stash)
  {
    free(stash);
    return NULL;
  }

  // copy over old to new starting at our offset
  j = 0;
  while(stash[i])
    new_stash[j++] = stash[i++];
  new_stash[j] = '\0';
  free(stash);
  return new_stash;
}
