NAME = pipex

UNAME_S := $(shell uname -s)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I includes/ -I libft/
LDFLAGS = -L libft/ -lft

SRCD = srcs

SRC=	error_handler.c		\
		ft_free.c			\
		parse.c				\
		path_utils.c		\
		here_doc_utils.c	\
		pipex.c

OBJ=$(SRC:%.c=%.o)

SRCS=$(addprefix srcs/, $(SRC))
OBJS=$(addprefix srcs/, $(OBJ))

# debug
ifeq ($(UNAME_S),Linux)
debug: CFLAGS += -pedantic -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -g3
endif
ifeq ($(UNAME_S),Darwin)
debug: CFLAGS += -pedantic -fsanitize=address -g3
endif
debug: $(NAME)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

$(OBJD)/%.o: $(SRCD)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(SRCD)/*.o
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
