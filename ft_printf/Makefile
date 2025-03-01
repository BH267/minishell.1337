NAME = libftprintf.a

SOURCES = ft_putstr.c ft_putbase.c ft_printf.c

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(AR) -rcs $(NAME) $(OBJECTS)


clean :
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
