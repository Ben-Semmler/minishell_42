/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <bsemmler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:55:24 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/18 15:06:16 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg_size(char *input, bool include_quotes, int returnval);
int	interpret_input(char *input, char *arg, int *offset, int returnval);

char	*copy_arg(char *input, int returnval)
{
	int		i;
	int		offset;
	char	quotations;
	char	prev_quotations;
	char	*arg;
	bool	interpret;

	int arg_size = get_arg_size(input, 0, returnval);
	arg = malloc(arg_size + 1);
	i = 0;
	quotations = 0;
	offset = 0;
	interpret = true;
	while (input[i] && i - offset < arg_size)
	{
		prev_quotations = quotations;
		quotations = check_quotations(input[i], quotations);
		if (input[i] == 39)
			interpret = !interpret;
		if (input[i] == '$' && interpret)
			i += interpret_input(input, arg, &offset, returnval);
		else
		{
			if (prev_quotations != quotations)
				offset++;
			else
				arg[i - offset] = input[i];
			i++;
		}
	}
	arg[i - offset] = 0;
	return (arg);
}

int	interpret_input(char *input, char *arg, int *offset, int returnval)
{
	int	i;
	int	i2;

	i = 0;
	if (input[i + 1] == '?')
	{
		i2 = 0;
		while (ft_itoa(returnval)[i2])
		{
			arg[i - *offset + i2] = ft_itoa(returnval)[i2];
			i2++;
		}
		i += 2;
		*offset -= i2 - 2;
	}
	else
	{
		i += 1;
		*offset += 1;
		*offset -= insert_data(&arg[i - *offset],
				get_key(&input[i])) - ft_strlen(get_key(&input[i]));
		i += ft_strlen(get_key(&input[i]));
	}
	return (i);
}
