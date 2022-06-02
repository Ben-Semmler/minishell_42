NAME = minishell

c_flags = -Wall -Werror -Wextra -lreadline

FILES = main.c\
		get_options.c\
		switch_command.c\
		get_command_id.c\
		run_executable.c\
		command_echo.c\
		command_cd.c\
		command_pwd.c\
		ft_joinfree.c

all:
	$(MAKE) -C libft
	gcc $(c_flags) -o $(NAME) libft/libft.a $(FILES)

clean:

fclean:
	rm -rf $(NAME)

norm:
	norminette $(FILES)

re: fclean all