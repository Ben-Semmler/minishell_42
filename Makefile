NAME = minishell

c_flags = -Wall -Werror -Wextra
libraries = -lreadline libft/libft.a -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib

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

run: all
	./minishell

norm: all
	norminette $(SRC)

git:
	@clear
	@git add .
	@echo "commit msg" 
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;

test: all
	gcc testmain.c
	./minishell

re: fclean all
