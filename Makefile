# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -I./includes
LIBS        = -lreadline ./libft/libft.a

# **************************************************************************** #
#                               SOURCE FILES                                   #
# **************************************************************************** #

# Builtins
BUILTINS_SRCS = \
    srcs/builtins/echo.c \
    srcs/builtins/pwd.c \
    srcs/builtins/env.c \
    srcs/builtins/cd_utils.c \
    srcs/builtins/cd.c \
    srcs/builtins/export.c \
    srcs/builtins/unset.c \
    srcs/builtins/exit.c \
    srcs/builtins/builtins_dispatch.c \
	srcs/executor/execute_single.c \
	srcs/executor/redirection.c \
	srcs/executor/utils_execution.c \
	srcs/executor/ft_split_path.c \
	srcs/executor/execution.c \
	srcs/executor/heredoc.c \
	srcs/executor/signals.c \

# Main Minishell Sources
SRCS = \
    srcs/main.c \
    srcs/lexer/tokenizer.c \
    srcs/lexer/token_utils.c \
    srcs/lexer/extract_word.c \
    srcs/lexer/handle_operators.c \
    srcs/parser/parse.c \
    srcs/parser/parse_cmds.c \
    srcs/parser/parse_utils.c \
    srcs/parser/parse_free.c \
    srcs/parser/print_parse.c \
    srcs/expander/expand.c \
    srcs/expander/expand_variables_main.c \
    srcs/expander/expand_variables.c \
    srcs/expander/expand_utils.c \
    srcs/expander/expand_quotes.c \
    $(BUILTINS_SRCS)

OBJS = $(SRCS:.c=.o)

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: libft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

libft:
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)
	rm -f $(BUILTINS_NAME)

re: fclean all

# **************************************************************************** #
#                         BUILTINS TEST (ROUDY)                               #
# **************************************************************************** #

BUILTINS_TEST_SRCS = \
    srcs/tests/builtins_main.c \
    $(BUILTINS_SRCS)

BUILTINS_TEST_OBJS = $(BUILTINS_TEST_SRCS:.c=.o)
BUILTINS_NAME = builtins_test

test_builtins: libft $(BUILTINS_TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(BUILTINS_TEST_OBJS) ./libft/libft.a -o $(BUILTINS_NAME)
	@echo "\n\033[1;32m[Running builtins test...]\033[0m\n"
	./$(BUILTINS_NAME)

clean_builtins:
	rm -f $(BUILTINS_TEST_OBJS)
	rm -f $(BUILTINS_NAME)

.PHONY: all clean fclean re libft test_builtins clean_builtins
