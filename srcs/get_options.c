/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:05:05 by bsemmler          #+#    #+#             */
/*   Updated: 2022/05/19 17:05:06 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_argn(char *input);
char	*copy_arg(char *input);
int		get_arg_size(char *input, int include_quotes);
void	handle_quotations(char *input, int *quotations);

char	**get_options(char *input)
{
	char	**args;
	int		i;
	int		argi;
	int		argn;

	argn = get_argn(input);
	args = malloc(sizeof(char *) * (argn + 1));
	i = 0;
	argi = 0;
	while (input[i] && argi < argn)
	{
		args[argi] = copy_arg(&input[i]);
		i += get_arg_size(&input[i], 1);
		while (input[i] && input[i] == ' ')
			i++;
		argi++;
	}
	i = 0;
	while (i < argn + 1)
		i++;
	args[argi] = NULL;
	return (args);
}

int	get_argn(char *input)
{
	char	quotations;
	int		argn;
	int		i;

	argn = 0;
	i = 0;
	while (input[i])
	{
		quotations = 0;
		while (input[i] && (quotations != 0 || input[i] != ' '))
		{
			if (input[i] == 34 || input[i] == 39)
			{
				if (quotations == 0)
					quotations = input[i];
				else if (quotations == input[i])
					quotations = 0;
			}
			i++;
		}
		while (input[i] == ' ')
			i++;
		argn++;
	}
	return (argn);
}

char	*copy_arg(char *input)
{
	int		len;
	int		i;
	int		offset;
	int		quotations;
	char	*arg;

	len = get_arg_size(input, 0);
	arg = malloc(sizeof(char) * (len + 1));
	i = 0;
	quotations = 0;
	offset = 0;
	while (i - offset < len)
	{
		if ((input[i] == 34 || input[i] == 39)
			&& (quotations == 0 || quotations == input[i]))
		{
			handle_quotations(&input[i], &quotations);
			offset++;
		}
		else
			arg[i - offset] = input[i];
		i++;
	}
	arg[i] = 0;
	return (arg);
}

int	get_arg_size(char *input, int include_quotes)
{
	int	quotations;
	int	len;
	int	adjust;

	len = 0;
	adjust = 0;
	quotations = 0;
	while (input[len] && (quotations != 0 || input[len] != ' '))
	{
		if (input[0] == 34 || input[0] == 39)
		{
			if (quotations == 0)
				quotations = input[len];
			else if (quotations == input[len])
			{
				adjust += 2;
				quotations = 0;
			}
		}
		len++;
	}
	if (include_quotes == 1)
		return (len);
	return (len - adjust);
}

void	handle_quotations(char *input, int *quotations)
{
	if (*quotations == 0)
		*quotations = input[0];
	else if (*quotations == input[0])
		*quotations = 0;
}
