NAME = gnl_test

CC = clang
CFLAGS = -Wall -Wextra -Werror
BUFFER_SIZE = 42

SRC = get_next_line.c get_next_line_utils.c
TEST_SRC = main.c
OBJ = $(SRC:.c=.o)

VALGRIND = valgrind
VALGRINDFLAGS = --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--errors-for-leak-kinds=all \
	--error-exitcode=1

all: $(NAME)

$(NAME): $(SRC) $(TEST_SRC) get_next_line.h
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) $(TEST_SRC) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: re
	./$(NAME)

valgrind: re
	$(VALGRIND) $(VALGRINDFLAGS) ./$(NAME)

.PHONY: all clean fclean re test valgrind
