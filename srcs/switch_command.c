/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:23:22 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/14 15:11:41 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	switch_command(char *command, t_inputs *input, t_outputs *output, bool *run)
{
	if (ft_strncmp(command, "./", 3) == 0)
		return (run_executable(input, output));
	else if (ft_strncmp(command, "echo", 5) == 0)
		return (command_echo(input));
	else if (ft_strncmp(command, "cd", 3) == 0)
		return (command_cd(input));
	else if (ft_strncmp(command, "pwd", 4) == 0)
		return (command_pwd());
	else if (ft_strncmp(command, "export", 7) == 0)
		return (command_export(input));
	else if (ft_strncmp(command, "unset", 6) == 0)
		return (unset(input));
	else if (ft_strncmp(command, "env", 3) == 0)
		return (command_env());
	else if (ft_strncmp(command, "exit", 4) == 0)
	{
		*run = false;
		return (0);
	}
	return (run_cmd_exec(command, input, output));
}
