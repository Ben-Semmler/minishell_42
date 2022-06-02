/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:35:20 by bsemmler          #+#    #+#             */
/*   Updated: 2022/05/24 15:35:21 by bsemmler         ###   ########.fr       */
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

	to_print = malloc(sizeof(char) * (get_echo_len(input) + 1));
	i = 1;
	len = 0;
	while (input[i] != NULL)
	{
		i2 = 0;
		while (input[i][i2])
		{
			to_print[len] = input[i][i2];
			len++;
			i2++;
		}
		to_print[len] = ' ';
		len++;
		i++;
	}
	to_print[len - 1] = '\n';
	to_print[len] = 0;
	return (to_print);
}

int	get_echo_len(char **input)
{
	int		len;
	int		i;

	i = 1;
	len = 0;
	while (input[i] != NULL)
	{
		len += ft_strlen(input[i]) + 1;
		i++;
	}
	return (len);
}
