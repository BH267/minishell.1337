CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c
OBJS = $(SRCS:.c=.o)
LIBHB_PATH = libhb/
LIBHB = $(LIBHB_PATH)libhb.a
NAME = minishell
LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBHB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBHB) $(LIBS)

$(LIBHB) : 
	@make -C $(LIBHB_PATH) 2>/dev/null

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBHB_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBHB_PATH) fclean

re: fclean all

.PHONY: clean
