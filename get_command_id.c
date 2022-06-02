/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_id.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:25:21 by bsemmler          #+#    #+#             */
/*   Updated: 2022/04/12 16:25:21 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var(char *input);
int	check_command(char *input, char *to_check);

int	get_command_id(char *input)
{
	//Check inputted command against list of commands -b
	if (ft_strncmp(input, "./", 2) == 0)
		return (0);
	if (check_var(input) == 1)
		return (1);
	if (check_command(input, "echo") == 1)
		return (2);
	if (check_command(input, "cd") == 1)
		return (3);
	if (check_command(input, "pwd") == 1)
		return (4);
	if (check_command(input, "export") == 1)
		return (5);
	if (check_command(input, "unset") == 1)
		return (6);
	if (check_command(input, "env") == 1)
		return (7);
	if (check_command(input, "exit") == 1)
		return (8);
	return (-1);
}

int	check_var(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != ' ' && input[i] != '=')
		i++;
	if (input[i] == '=')
		return (1);
	return (0);
}

int	check_command(char *input, char *to_check)
{
	//check if command is inputted without options -b
	if (ft_strlen(input) == ft_strlen(to_check))
	{
		if (ft_strncmp(input, to_check, ft_strlen(to_check)) == 0)
			return (1);
	}
	//check if command is inputted with options -b
	else if (ft_strncmp(input, ft_strjoin(to_check, " "),
			ft_strlen(to_check) + 1) == 0)
		return (1);
	return (0);
}
