CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror
SRCS = 2main.c builtins/cd.c getpath.c \
       execute.c ft_exit.c builtins/pwd.c builtins/echo.c \
       builtins/env.c builtins/export.c dolar.c editenv.c env.c \
       envlst.c builtins/unset.c builtins/exit.c builtins/expars.c \
       redirection.c pipeline.c single_cmd.c runcmd.c isbins.c heredoc.c \
       signals.c lastcmd.c \
    parsing.c parscmd/parser.c parscmd/splitcmd.c exitstatus.c  parscmd/parscmd_utils.c\
	parsing/lexer.c parsing/lexer_utils.c parsing/lexer_utils_extra.c \
	parsing/lexer_handlers.c \
	parsing/help_lh.c \
	parsing/redirection_helpers.c parsing/helper_functions.c \
	parsing/gramer.c \
	expand/split_args_utils.c \
	expand/expand_utils.c \
	expand/expand.c \
	expand/expand_check.c \
	expand/expand_mask.c \
	expand/expand_herdoc.c \
	expand/expand_loop_utils.c \
	expand/expand_handle_word.c \
	expand/expand_process_utils.c \
	expand/expand_mask_utils_extra.c \
	card/wildcard.c \
	card/wildcard_utils.c \
	card/help_rtwm.c \

OBJS = $(SRCS:.c=.o)
LIBHB_PATH = libhb/
LIBHB = $(LIBHB_PATH)libhb.a
NAME = minishell
LIBS = -lreadline


all: $(NAME)
	@bash -c ' \
	MANGENTA="\033[35m"; \
	BOLD="\033[1m"; \
	CLEAR_LINE="\033[2K"; \
	LINE_START="\033[0G"; \
	RED="\033[31m"; \
	WHITE="\033[37m"; \
	GRAY="\033[90m"; \
	BLUE="\033[34m"; \
	GREEN="\033[32m"; \
	RESET="\033[0m"; \
	spin[0]="⠁"; \
	spin[1]="⠃"; \
	spin[2]="⠇"; \
	spin[3]="⠧"; \
	spin[4]="⠷"; \
	spin[5]="⠿"; \
	spin[6]="⠷"; \
	spin[7]="⠧"; \
	spin[8]="⠇"; \
	spin[9]="⠃"; \
	echo -ne "$$WHITE$$${spin[0]}$$RESET Loading..."; \
	for i in {1..3}; do \
	    for j in "$${spin[@]}"; do \
	        echo -ne "$$CLEAR_LINE$$LINE_START$$WHITE$$j$$RESET Processing..."; \
	        sleep 0.1; \
	    done; \
	done; \
	printf "$$CLEAR_LINE$$LINE_START$$GREEN$$BOLD✔$$RESET Compilation finished successfully!$$WHITE$$BOLD\n"; \
	'

$(NAME): $(OBJS) $(LIBHB)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBHB) $(LIBS)

$(LIBHB) :
	@make -C $(LIBHB_PATH) --no-print-directory
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBHB_PATH) clean --no-print-directory

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBHB_PATH) fclean --no-print-directory

re: fclean all

.PHONY: clean
