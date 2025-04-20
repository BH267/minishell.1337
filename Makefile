CC = cc
CFLAGS = -g -Wall -Wextra -Werror
SRCS = main.c builtins/cd.c ft_malloc/ft_malloc.c getpath.c \
       execute.c ft_exit.c builtins/pwd.c builtins/echo.c \
	builtins/env.c dolar.c editenv.c

OBJS = $(SRCS:.c=.o)
LIBHB_PATH = libhb/
LIBHB = $(LIBHB_PATH)libhb.a
NAME = minishell
LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBHB)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBHB) $(LIBS)

$(LIBHB) : 
	@make -C $(LIBHB_PATH) 
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBHB_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBHB_PATH) fclean

re: fclean all

.PHONY: clean
