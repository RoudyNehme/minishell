# Define variables
Library = libft
Compiler = cc
CmpFlags = -Wall -Wextra -Werror
OUTN = $(Library).a
CFILES = $(files:%=%.c)
OFILES = $(files:%=%.o)
NAME = $(OUTN)

# List of source files
files = \
	ft_isascii \
	ft_memcpy \
	ft_strlcpy \
	ft_tolower \
	ft_atoi \
	ft_isdigit \
	ft_memmove \
	ft_strlen \
	ft_toupper \
	ft_bzero \
	ft_isprint \
	ft_memset \
	ft_strncmp \
	ft_isalnum \
	ft_memchr \
	ft_strchr \
	ft_strnstr \
	ft_isalpha \
	ft_memcmp \
	ft_strlcat \
	ft_strrchr \
	ft_strncpy \
	ft_calloc \
	ft_strdup \
	ft_substr \
	ft_strjoin \
	ft_strtrim \
	ft_split \
	ft_itoa \
	ft_strmapi \
	ft_striteri \
	ft_putchar_fd \
	ft_putstr_fd \
	ft_putendl_fd \
	ft_putnbr_fd \

# Default target to build the library
$(NAME):
	$(Compiler) $(CmpFlags) -c $(CFILES) -I./
	ar -rc $(OUTN) $(OFILES)

# Target to build everything (just the library in this case)
all: $(NAME)

# Clean up object files and the library
clean:
	rm -f $(NAME) $(OFILES)

# Clean everything, including object files and the library
fclean: clean
	rm -f $(NAME)

# Clean and rebuild everything
re: fclean all

# Declare these targets as phony to avoid conflicts with actual file names
.PHONY: all clean fclean re
