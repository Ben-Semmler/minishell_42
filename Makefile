NAME = minishell

c_flags = -Wall -Werror -Wextra
libraries = -lreadline libft/libft.a

INC = includes
LIB = libft
INCS = -I$(LIB) -I$(INC)

SRC = srcs/*.c

all:
	$(MAKE) -C libft re
	$(MAKE) -C libft clean
	gcc $(c_flags) -o $(NAME) $(SRC) $(INCS) $(libraries)

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
	norminette $(SRC)

git:
	@clear
	@git add .
	@echo "commit msg" 
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;

re: fclean all