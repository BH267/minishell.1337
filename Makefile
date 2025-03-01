CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
PATH_PRINTF = ft_printf/
LIBFTPRINTF = $(PATH_PRINTF)libftprintf.a
LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFTPRINTF) $(LIBS)

$(LIBFTPRINTF):
	make -C $(PATH_PRINTF)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(PATH_PRINTF) clean

fclean: clean
	rm -f $(NAME)
	make -C $(PATH_PRINTF) fclean

re: fclean all

.PHONY: all clean fclean re
