/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:23:22 by bsemmler          #+#    #+#             */
/*   Updated: 2022/09/27 13:30:38 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_input(char *input);
void	free_split_input(char **s_input);

int	switch_command(char *command, t_inputs *input, bool *run)
{
	if (ft_strncmp(command, "./", 3) == 0)
		//command './'
		return (run_executable(input));
	else if (ft_strncmp(command, "echo", 5) == 0)
		//command 'echo'
		return (command_echo(input));
	else if (ft_strncmp(command, "cd", 3) == 0)
		//command 'cd'
		return (command_cd(input));
	else if (ft_strncmp(command, "pwd", 4) == 0)
		//command 'pwd'
		return (command_pwd(input));
	else if (ft_strncmp(command, "export", 7) == 0)
		//command 'export'
		command_export(input);
	else if (ft_strncmp(command, "unset", 6) == 0)
		//command 'unset'
		unset(input);
	else if (ft_strncmp(command, "env", 4) == 0)
		//command 'env'
		command_env();
	else if (ft_strncmp(command, "exit", 4) == 0)
		//command 'exit'
		*run = false;
	else if (ft_strncmp(command, "cat", 4) == 0)
		return (command_cat(input));
	else
		printf("minishell: %s: command not found\n", command);
	return (1);
	//free_split_input(input);
}
