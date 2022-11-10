#include "minishell.h"

void	redir_left(char *command, t_outputs *output)
{
	//DEBUG
	if (debug)
		printf("READING FROM FILE (REDIRECTION '<')\n");
	//DEBUG

	output->stdout = readFile(command);
}

char	*readFile(char *filename)
{
	int		fd;
	int		return_val;
	char	buf[256];
	char	*content;

	fd = open(filename, O_RDONLY);
	content = NULL;
	while (true)
	{
		return_val = read(fd, buf, 255);
		if (return_val <= 0)
			break;
		buf[return_val] = 0;
		if (content != NULL)
			content = ft_joinfree(content, 1, buf, 0);
		else
			content = ft_strdup(buf);
	}
	return (content);
}

void	insert_doc(char *command, t_outputs *output)
{
	//DEBUG
	if (debug)
		printf("USING DOCUMENT INSERTION (REDIRECTION '<<')\n");
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