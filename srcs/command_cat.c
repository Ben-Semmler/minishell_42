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

int	command_cat(const t_inputs *input)
{
	t_outputs	output;

	if (input->argc > 0)
	{
		readFile(input->argv[0], &output);
		if (output.stdout == NULL)
			return (1);
		printf("%s\n", output.stdout);
	}
	else
		printf("%s", input->stdin);
	return (0);
}
