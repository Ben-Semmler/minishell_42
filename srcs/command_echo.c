/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:35:20 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/15 16:02:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_echo_len(char **argv);

int	command_echo(const t_inputs *input)
{
	int		i;
	bool	space;

	i = (input->argc > 0 && ft_strncmp(input->argv[0], "-n", 3) == 0);
	space = i;
	while (input->argv[i])
	{
		if (i != 0 && space == false)
			printf(" ");
		printf("%s", input->argv[i]);
		i++;
		space = false;
	}
	if (input->argc == 0 || ft_strncmp(input->argv[0], "-n", 3) != 0)
		printf("\n");
	return (0);
}

int	get_echo_len(char **argv)
{
	int		i;
	int		j;
	char	*key;
	int		sum;

	i = (ft_strncmp(argv[0], "-n", 3) == 0);
	sum = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] == '$')
			{
				key = get_key(&argv[i][++j]);
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
