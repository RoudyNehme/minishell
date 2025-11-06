NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes
LIBS = -lreadline ./libft/libft.a

SRCS = srcs/main.c \
       srcs/lexer/tokenizer.c \
       srcs/lexer/token_utils.c \
       srcs/lexer/extract_word.c \
       srcs/lexer/handle_operators.c \
       srcs/parser/parse.c \
       srcs/parser/parse_cmds.c \
       srcs/parser/parse_utils.c \
       srcs/parser/parse_free.c \
       srcs/parser/print_parse.c

OBJS = $(SRCS:.c=.o)

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

re: fclean all

.PHONY: all clean fclean re libft

# **************************************************************************** #
#                         BUILTINS TEST RULE (ROUDI)                           #
# **************************************************************************** #

BUILTINS_SRCS = srcs/tests/builtins_main.c \
                srcs/builtins/echo.c \
                srcs/builtins/pwd.c \
                srcs/builtins/env.c \
                srcs/builtins/cd.c \
                srcs/builtins/export.c \
                srcs/builtins/unset.c \
                srcs/builtins/exit.c \
                srcs/builtins/builtins_dispatch.c

BUILTINS_OBJS = $(BUILTINS_SRCS:.c=.o)
BUILTINS_NAME = builtins_test

test_builtins: libft $(BUILTINS_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(BUILTINS_OBJS) ./libft/libft.a -o $(BUILTINS_NAME)
	@echo "\n\033[1;32m[Running builtins test...]\033[0m\n"
	./$(BUILTINS_NAME)

clean_builtins:
	rm -f $(BUILTINS_OBJS)
	rm -f $(BUILTINS_NAME)

