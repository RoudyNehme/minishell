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
       srcs/parser/print_parse.c \
       srcs/expander/expand_variables.c

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
