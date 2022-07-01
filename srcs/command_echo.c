/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:35:20 by bsemmler          #+#    #+#             */
/*   Updated: 2022/06/14 15:17:02 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_echo_len(char **input);

void	command_echo(char **input)
{
	int		len;
	int		i;
	int		i2;
	char	*to_print;

	to_print = malloc(100);//get_echo_len(input) + 1);
	i = 1 + (input[1] != NULL && ft_strncmp(input[1], "-n", 2) == 0);
	len = -1 + (input[1] == NULL);
	while (input[i])
	{
		i2 = 0;
		len++;
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
		i++;
	}
	to_print[len] = 0;
	printf("%s", to_print);
	if (input[1] == NULL || ft_strncmp(input[1], "-n", 2))
		printf("\n");
}

// int	get_echo_len(char **input)
// {
// 	int		len;
// 	int		i;
// 	int		j;
// 	char	*key;
// 	int		sum;
// 	t_env	env_var;

// 	i = 0 + (ft_strncmp(input[1], "-n", 2) == 0);
// 	sum = 0;
// 	len = 0;
// 	while (input[++i])
// 	{
// 		j = -1;
// 		while (input[i][++j])
// 		{
// 			if (input[i][j] == '$')
// 			{
// 				key = get_key(&input[i][++j]);
// 				env_var = search(key);
// 				sum += ft_strlen(env_var.data);
// 				j += ft_strlen(key);
// 			}
// 			else
// 				len++;
// 		}
// 	}
// 	return (sum);
// }
