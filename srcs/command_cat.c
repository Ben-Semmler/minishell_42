#include "minishell.h"

void	command_cat(const t_inputs *input)
{
	t_outputs	output;

	if (input->argc > 0)
	{
		printf("Here!!\n");
		readFile(input->argv[0], &output);
		printf("%s", output.stdout);
	}
	else
		printf("%s", input->stdin);
}
