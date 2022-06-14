#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_cmd t_cmd;

typedef struct s_cmd
{
	char	**input;
	char	*output;

	void	*in_fun;
	void	(*out_fun)(t_cmd *cmd);
}	t_cmd;

int	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	if (!s)
		return (length);
	while (s[length] != 0)
		length++;
	return (length);
}

int	ft_strcmp(const char *s1, const char *s2, size_t n)
{
	size_t	pos;

	pos = 0;
	while ((s1[pos] != 0 || s2[pos] != 0) && pos < n)
	{
		if (((unsigned char *)s1)[pos] != ((unsigned char *)s2)[pos])
			return (((unsigned char *)s1)[pos] - ((unsigned char *)s2)[pos]);
		pos++;
	}
	return (0);
}


// void writeToFile(char *input, char *file)
// {
// 	write(open(file), input, ft_strlen(input));
// }

char	*echo(t_cmd *cmd)
{
	int		len;
	int		i;
	int		i2;
	char	*to_print;

	to_print = malloc(100);
	i = 1;
	len = 0;
	while (cmd->input[i] && ft_strcmp(cmd->input[i], ">>", 2) == 0)
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
	if (!ft_strcmp(cmd->input[1], "-n", 2))
		to_print[len - 1] = '\n';
	to_print[len] = 0;
	return (to_print);
}

void print_out(t_cmd *cmd)
{
	printf("%s\n", cmd->output);
}

int	main(int ac, char **av)
{
	t_cmd	cmd;
	char	*test = "hello world";
	void	(*in_fun)(t_cmd *cmd);
	void	(*out_fun)(t_cmd *cmd);

	out_fun = &print_out;
	cmd.output = test;
	cmd.out_fun = out_fun;
	//cmd.input = av;
	cmd.out_fun(&cmd);
	out_fun(&cmd);
}
