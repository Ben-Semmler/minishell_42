/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:23:22 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/15 16:18:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_input(char *input);
void	free_split_input(char **s_input);

int	switch_command(char *command, t_args *args, bool *run)
{
	if (ft_strncmp(command, "./", 3) == 0)
		return (run_executable(args));
	else if (ft_strncmp(command, "echo", 5) == 0)
		return (command_echo(args));
	else if (ft_strncmp(command, "cd", 3) == 0)
		return (command_cd(args));
	else if (ft_strncmp(command, "pwd", 4) == 0)
		return (command_pwd());
	else if (ft_strncmp(command, "export", 7) == 0)
		return (command_export(args));
	else if (ft_strncmp(command, "unset", 6) == 0)
		return (unset(args));
	else if (ft_strncmp(command, "env", 3) == 0)
		return (command_env());
	else if (ft_strncmp(command, "exit", 4) == 0)
	{
		*run = false;
		return (0);
	}
	return (run_cmd_exec(command, args));
}
