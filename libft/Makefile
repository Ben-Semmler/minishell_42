NAME	= libft.a

c_flags = -Wall -Werror -Wextra -c -D BUFFER_SIZE=25

libft_proj	= isalpha isdigit isalnum isascii isprint strlen memset bzero memcpy memmove strlcpy strlcat\
			toupper tolower strchr strrchr strncmp memchr memcmp strnstr atoi calloc strdup\
			substr strjoin strtrim split itoa strmapi striteri putchar_fd putstr_fd putendl_fd putnbr_fd\
			lstnew lstadd_front lstsize lstlast lstadd_back lstdelone lstclear lstiter lstmap\
			abs

LIBFT_PROJ = $(addprefix "ft_", $(libft_proj))
LIBFT_PROJ_DIR = $(addprefix "libft_proj/", $(LIBFT_PROJ))

all: $(NAME) clean

$(NAME):
	gcc $(c_flags) $(addsuffix ".c", $(LIBFT_PROJ_DIR))
	ar -crs $(NAME) $(addsuffix ".o", $(LIBFT_PROJ))

clean:
	rm -f $(addsuffix ".o", $(LIBFT_PROJ))

fclean: clean
	rm -f $(NAME)

re: fclean all
	
.PHONY: all clean fclean re
