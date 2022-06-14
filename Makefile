NAME = minishell

c_flags = -Wall -Werror -Wextra -lreadline

INC = includes
LIB = libft
INCS = -I$(LIB) -I$(INC)

SRC = srcs/*.c

all:
	$(MAKE) -C libft
	gcc $(c_flags) -o $(NAME) $(INCS) libft/libft.a $(SRC)
	./$(NAME)

r:
	@make
	@clear
	@./$(NAME)

i:
	gcc main.c

clean:

fclean:
	rm -rf $(NAME)

norm:
	norminette $(FILES)

git:
	@clear
	@git add .
	@echo "commit msg" 
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;

re: fclean all