/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:23:22 by bsemmler          #+#    #+#             */
/*   Updated: 2022/06/23 12:30:26 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_input(char *input);
void	free_split_input(char **s_input);

void	switch_command(char *command, t_inputs *input)
{
	int		c_id;

	(void)stdin;
	//Splits the input into the command and the options.
	c_id = get_command_id(command);
	if (c_id == -1)
		//Invalid command
		printf("minishell: %s: command not found\n", command);
	else if (c_id == 0)
		//command './'
		run_executable(input);
	else if (c_id == 1)
		//command for environment variables
		printf("minishell: %s: NOT YET IMPLEMENTED\n", command);
	else if (c_id == 2)
		//command 'echo'
		command_echo(input);
	else if (c_id == 3)
		//command 'cd'
		command_cd(input);
	else if (c_id == 4)
		//command 'pwd'
		command_pwd(input);
	else if (c_id == 5)
		//command 'export'
		printf("minishell: %s: NOT YET IMPLEMENTED\n", command);
	else if (c_id == 6)
		//command 'unset'
		printf("minishell: %s: NOT YET IMPLEMENTED\n", command);
	else if (c_id == 7)
		//command 'env'
		printf("minishell: %s: NOT YET IMPLEMENTED\n", command);
	else if (c_id == 8)
		//command 'exit'
		//*run = false;
		printf("ah\n");
	//free_split_input(input);
}
