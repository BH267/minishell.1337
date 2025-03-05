CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = main.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
LIBFT = libft/libft.a
LIBFTPRINTF = ft_printf/libftprintf.a
FTMALLOC = ft_malloc/ft_malloc.o
LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBFTPRINTF) $(FTMALLOC)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBFTPRINTF) $(FTMALLOC) $(LIBS)

$(LIBFT):
	make -C libft

$(LIBFTPRINTF):
	make -C ft_printf

$(FTMALLOC): ft_malloc/ft_malloc.c
	$(CC) $(CFLAGS) -c ft_malloc/ft_malloc.c -o ft_malloc/ft_malloc.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(FTMALLOC)
	make -C libft clean
	make -C ft_printf clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean
	make -C ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
