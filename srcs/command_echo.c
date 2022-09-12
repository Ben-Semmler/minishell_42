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

int	get_echo_len(char **argv);

void	command_echo(const t_inputs *input)
{
	int	i;

	i = (input->argc > 0 && ft_strncmp(input->argv[0], "-n", 3) == 0);
	while (input->argv[i])
	{
		if (i != 0)
			printf(" ");
		printf("%s", input->argv[i]);
		i++;
	}
	if (input->argc == 0 || ft_strncmp(input->argv[0], "-n", 3) != 0)
		printf("\n");

	//int		len;
	//int		i;
	//int		j;
	//char	*to_print;
	//int		nl;
	/*to_print = malloc(get_echo_len(input->argv));
	i = (ft_strncmp(input->argv[0], "-n", 3) == 0);
	nl = i;
	len = 0;
	while (input->argv[i])
	{
		if (input->argv[i][0] == '>')
			break ;
		j = -1;
		while (input->argv[i][++j])
		{
			if (input->argv[i][j] == '$')
			{
				len += insert_data(&to_print[len], get_key(&input->argv[i][++j]));
				while (input->argv[i][j] && input->argv[i][j] != ' ')
					j++;
			}
			else
			{
				to_print[len] = input->argv[i][j];
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
	if (ft_strncmp(input->argv[0], "-n", 3) != 0)
		printf("\n");
	free(to_print);*/
}

int	get_echo_len(char **argv)
{
	int		len;
	int		i;
	int		j;
	char	*key;
	int		sum;

	i = (ft_strncmp(argv[0], "-n", 3) == 0);
	sum = 0;
	len = 0;
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
