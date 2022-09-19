#include "minishell.h"

void	readFile(char *command, t_outputs *output)
{
	//DEBUG
	if (debug)
		printf("READING FROM FILE\n");
	//DEBUG

	int		fd;
	int		return_val;
	char	buf[256];

	fd = open(command, O_RDONLY);
	output->stdout = NULL;
	while (true)
	{
		return_val = read(fd, buf, 255);
		if (return_val <= 0)
			break;
		buf[return_val] = 0;
		if (output->stdout != NULL)
			output->stdout = ft_joinfree(output->stdout, 1, buf, 0);
		else
			output->stdout = ft_strdup(buf);
	}
}

void	insert_doc(char *command, t_outputs *output)
{
	//DEBUG
	if (debug)
		printf("USING DOCUMENT INSERTION\n");
	//DEBUG

	char	*input;

	input = ft_strdup("");
	output->stdout = ft_strdup("");
	while (true)
	{
		input = readline("> ");
		if (ft_strncmp(input, command, ft_strlen(input) + 1) == 0)
			break;
		output->stdout = ft_joinfree(output->stdout, true, input, true);
		output->stdout = ft_joinfree(output->stdout, true, "\n", false);
	}
	free(input);
}