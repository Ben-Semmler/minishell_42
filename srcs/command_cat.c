/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:22:12 by bsemmler          #+#    #+#             */
/*   Updated: 2022/09/27 14:22:12 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_cat(const t_inputs *input, t_outputs *output)
{
	t_outputs	output_read;

	if (input->argc > 0)
	{
		readFile(input->argv[0], &output_read);
		if (output_read.stdout == NULL)
		{
			output->stderr = ft_strjoin(input->argv[0], ": No such file or directory"); 
			return (1);
		}
		printf("%s\n", output_read.stdout);
	}
	else
		printf("%s", input->stdin);
	return (0);
}
