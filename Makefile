SRCS = ft_printf.c helpers.c number_helpers.c string_helpers.c io_helper.c
OBJS = $(SRCS:.c=.o)
NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS) 

all: $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

test: all
	@$(CC) $(CFLAGS) -L. -lftprintf ./__tests__/main.c -o test
	@./test

.PHONY: all clean fclean re