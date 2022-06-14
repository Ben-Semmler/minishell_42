/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:23:22 by bsemmler          #+#    #+#             */
/*   Updated: 2022/04/14 17:23:24 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_input(char *input);
void	free_split_input(char **s_input);

char	*switch_command(char *input, int *run)
{
	int		c_id;
	char	**s_input;
	char	*output;

	//Splits the input into the command and the options.
	c_id = get_command_id(input);
	s_input = get_options(input);
	output = NULL;
	if (c_id == -1)
		//Invalid command
		output = ft_joinfree(ft_strjoin("minishell: ", s_input[0]), 1,
				": command not found\n", 0);
	else if (c_id == 0)
		//command './'
		output = run_executable(s_input);
	else if (c_id == 1)
		//command for environment variables
		output = ft_joinfree(ft_strjoin("COMMAND '", s_input[0]), 1,
				"' NOT YET IMPLEMENTED\n", 0);
	else if (c_id == 2)
		//command 'echo'
		output = command_echo(s_input);
	else if (c_id == 3)
		//command 'cd'
		output = command_cd(s_input);
	else if (c_id == 4)
		//command 'pwd'
		output = command_pwd(s_input);
	else if (c_id == 5)
		//command 'export'
		output = ft_joinfree(ft_strjoin("COMMAND '", s_input[0]), 1,
				"' NOT YET IMPLEMENTED\n", 0);
	else if (c_id == 6)
		//command 'unset'
		output = ft_joinfree(ft_strjoin("COMMAND '", s_input[0]), 1,
				"' NOT YET IMPLEMENTED\n", 0);
	else if (c_id == 7)
		//command 'env'
		output = ft_joinfree(ft_strjoin("COMMAND '", s_input[0]), 1,
				"' NOT YET IMPLEMENTED\n", 0);
	else if (c_id == 8)
		//command 'exit'
		*run = 0;
	free_split_input(s_input);
	return (output);
}

void	free_split_input(char **s_input)
{
	int	i;

	//Free the split input
	i = 0;
	while (s_input[i] != NULL)
	{
		free(s_input[i]);
		i++;
	}
	free(s_input);
}
