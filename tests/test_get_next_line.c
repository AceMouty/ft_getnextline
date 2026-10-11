#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int fd;
  char *line;

  if (argc < 2) {
    fd = 0;
    printf("Reading from stdin. Press Ctrl+D to end.\n");
  } else {
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
      perror("open");
      return (1);
    }
  }
  line = get_next_line(fd);
  while (line) {
    printf("[%s]", line);
    free(line);
    line = get_next_line(fd);
  }
  if (fd != 0)
    close(fd);
  return (0);
}
