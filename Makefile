NAME = libftgetnextline.a
TEST_NAME = gnl_test

CC = clang
CFLAGS = -Wall -Wextra -Werror
BUFFER_SIZE = 42
AR = ar
ARFLAGS = rcs

SRC = get_next_line.c get_next_line_utils.c
TEST_SRC = main.c
OBJ_DIR = build/bs$(BUFFER_SIZE)
#OBJ = $(SRC:.c=.o)
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

VALGRIND = valgrind
VALGRINDFLAGS = --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--errors-for-leak-kinds=all \
	--error-exitcode=1

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c get_next_line.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

test: $(NAME) $(TEST_SRC)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) $(TEST_SRC) ./$(NAME) -o $(TEST_NAME)

run: test
	./$(TEST_NAME)

valgrind: test
	$(VALGRIND) $(VALGRINDFLAGS) ./$(TEST_NAME)

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re: fclean all

.PHONY: all test run valgrind clean fclean re
