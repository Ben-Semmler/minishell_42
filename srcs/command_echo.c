/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:35:20 by bsemmler          #+#    #+#             */
/*   Updated: 2022/06/23 12:51:35 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_echo_len(char **input);

void	command_echo(t_cmd *cmd)
{
	int		len;
	int		i;
	int		j;
	char	*to_print;
	int		nl;

	to_print = malloc(get_echo_len(cmd->input) + 1);
	i = 1 + (ft_strncmp(cmd->input[1], "-n", 2) == 0);
	nl = i;
	len = 0;
	while (cmd->input[i][0])
	{
		if (cmd->input[i][0] == '>')
			break ;
		j = -1;
		while (cmd->input[i][++j])
		{
			if (cmd->input[i][j] == '$')
				len += insert_data(&to_print[len], get_key(&cmd->input[i][++j]));
			else
				to_print[len] = cmd->input[i][j];
			len++;
		}
		to_print[len] = ' ';
		i++;
	}
	len--;
	if (ft_strncmp(cmd->input[1], "-n", 2) != 0)
		to_print[len++] = '\n';
	to_print[len] = '\0';
	cmd->output = to_print;
}

int	get_echo_len(char **input)
{
	int		len;
	int		i;
	int		j;
	char	*key;
	int		sum;

	i = 0 + (ft_strncmp(input[1], "-n", 2) == 0);
	sum = 0;
	len = 0;
	while (input[++i][0])
	{
		j = -1;
		while (input[i][++j])
		{
			if (input[i][j] == '$')
			{
				key = get_key(&input[i][++j]);
				sum += ft_strlen(search(key).data);
				j += ft_strlen(key);
			}
			else
				sum++;
		}
	}
	return (sum);
}
