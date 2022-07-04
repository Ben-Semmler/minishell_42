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

void	command_echo(char **input)
{
	int		len;
	int		i;
	int		j;
	char	*to_print;
	int		nl;
	
	to_print = malloc(get_echo_len(input));
	i = 1 + (ft_strncmp(input[1], "-n", 3) == 0);
	nl = i;
	len = 0;
	while (input[i])
	{
		if (input[i][0] == '>')
			break ;
		j = -1;
		while (input[i][++j])
		{
			if (input[i][j] == '$')
			{
				len += insert_data(&to_print[len], get_key(&input[i][++j]));
				while (input[i][j] && input[i][j] != ' ')
					j++;
			}
			else
			{
				to_print[len] = input[i][j];
				len++;
			}
		}
		to_print[len] = ' ';
		len++;
		i++;
	}
	len--;
	to_print[len] = '\0';
	printf("%s", to_print);
	if (ft_strncmp(input[1], "-n", 3) != 0)
		printf("\n");
	free(to_print);
}

int	get_echo_len(char **input)
{
	int		len;
	int		i;
	int		j;
	char	*key;
	int		sum;

	i = 0 + (ft_strncmp(input[1], "-n", 3) == 0);
	sum = 0;
	len = 0;
	while (input[++i])
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
		sum++;
	}
	return (sum);
}
