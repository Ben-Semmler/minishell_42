/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:35:20 by bsemmler          #+#    #+#             */
/*   Updated: 2022/06/10 21:54:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_echo_len(char **input);

char	*command_echo(char **input)
{
	int		len;
	int		i;
	int		i2;
	char	*to_print;

	to_print = malloc(get_echo_len(input) + 1);
	i = 1;
	len = 0;
	while (input[i])
	{
		i2 = 0;
		while (input[i][i2])
		{
			if (input[i][i2] == '$')
				len += insert_data(&to_print[len], get_key(&input[i][++i2]));
			else
				to_print[len] = input[i][i2];
			len++;
			i2++;
		}
		to_print[len] = ' ';
		len++;
		i++;
	}
	if (!ft_strcmp(input[1], "-n"))
		to_print[len - 1] = '\n';
	to_print[len] = 0;
	return (to_print);
}

int	get_echo_len(char **input)
{
	int		len;
	int		i;
	int		j;
	char	*key;
	t_env	env_var;

	i = 0;
	while (input[++i])
	{
		j = -1;
		while (input[i][++j])
		{
			if (input[i][j] == '$')
			{
				key = get_key(&input[i][++j]);
				env_var = search(key);
				sum += ft_strlen(env_var.data);
				j += ft_strlen(key);
			}
			else
				len++;
		}
	}
	return (len);
}
