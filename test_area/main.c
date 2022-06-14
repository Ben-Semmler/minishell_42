#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_cmd t_cmd;

typedef struct s_cmd
{
	char	**input;
	char	*output;

	void	(*in_fun)(t_cmd *cmd);
	void	(*out_fun)(t_cmd *cmd);
}	t_cmd;

void writeToFile(char *input, char *file)
{
	write(open(file, O_WRONLY | O_CREAT, 0644), input, ft_strlen(input));
}

void	echo(t_cmd *cmd)
{
	int		len;
	int		i;
	int		i2;
	char	*to_print;

	to_print = malloc(100);
	i = 1 + (ft_strncmp(cmd->input[1], "-n", 2) == 0);
	len = 0;
	while (cmd->input[i] && ft_strncmp(cmd->input[i], ">>", 2))
	{
		i2 = 0;
		while (cmd->input[i][i2])
		{
			to_print[len] = cmd->input[i][i2];
			len++;
			i2++;
		}
		to_print[len] = ' ';
		len++;
		i++;
	}
	if (ft_strncmp(cmd->input[1], "-n", 2))
		to_print[len - 1] = '\n';
	to_print[len] = 0;
	cmd->output = to_print;
}

void print_out(t_cmd *cmd)
{
	printf("%s\n", cmd->output);
}

void	append_out(t_cmd *cmd)
{
	int		i;
	char	*name;

	i = 1;
	while (cmd->input[i] && ft_strncmp(cmd->input[i], ">>", 2) && ft_strncmp(cmd->input[i], ">", 1)
		i++;
	name = cmd->input[i + 1];
	i = 0;
	while (*name && (*name == ' ' || *name == '	'))
		name++;
	writeToFile(cmd->output, name);
}

int	main(int ac, char **av)
{
	t_cmd	cmd;
	char	*test_input[6] = {"echo", "-n", "hello", "world", ">", "out"};
	char	*test_output = "hello world";

	//cmd.input = av;

	//writeToFile(test, "t");
	cmd.input = test_input;
	cmd.output = test_output;

	//void	(*in_fun)(t_cmd *cmd);
	//void	(*out_fun)(t_cmd *cmd);

	//in_fun	= &echo;
	//out_fun = &append_out;

	cmd.in_fun = &echo;
	cmd.out_fun = &append_out;
	cmd.in_fun(&cmd);
	cmd.out_fun(&cmd);

	cmd.in_fun(&cmd);
	cmd.out_fun(&cmd);
}
