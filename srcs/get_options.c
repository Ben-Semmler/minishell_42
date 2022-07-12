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

int		get_command(t_action *action, char *input);
int		get_argn(char *input);
char	*copy_arg(char *input);
int		get_arg_size(char *input, bool include_quotes);

void	get_options(t_action *action, char *input)
{
	int		i;
	int		argi;
	int		argn;

	i = get_command(action, input);
	argi = 0;
	argn = get_argn(&input[i]);
	action->argv = malloc(sizeof(char *) * (argn + 1));
	while (input[i] && argi < argn)
	{
		while (input[i] && input[i] == ' ')
			i++;
		action->argv[argi] = copy_arg(&input[i]);
		i += get_arg_size(&input[i], 1);
		argi++;
	}
	action->argv[argi] = NULL;
	action->argc = argi;
}

int	get_command(t_action *action, char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (ft_strncmp(&input[i], "./", 2) == 0)
	{
		if (input[i] == 34 || input[i] == 39)
			i++;
		action->command = ft_strdup("./");
		i += 2;
	}
	else
	{
		action->command = copy_arg(&input[i]);
		i += get_arg_size(&input[i], true);
	}
	return (i);
}

int	get_argn(char *input)
{
	char	quotations;
	int		argn;
	int		i;

	argn = 0 - (input[0] == ' ');
	i = 0;
	if (ft_strncmp(input, "./", 2) == 0)
		i += 2;
	while (input[i])
	{
		quotations = 0;
		while (input[i] && (quotations != 0 || input[i] != ' '))
		{
			quotations = check_quotations(input[i], quotations);
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
	int		i;
	int		offset;
	char	quotations;
	char	prev_quotations;
	char	*arg;

	arg = malloc(sizeof(char) * (get_arg_size(input, 0) + 1));
	i = 0;
	quotations = 0;
	offset = 0;
	while (input[i] && i - offset < get_arg_size(input, 0))
	{
		prev_quotations = quotations;
		quotations = check_quotations(input[i], quotations);
		if (prev_quotations != quotations)
			offset++;
		else
			arg[i - offset] = input[i];
		i++;
	}
	arg[i - offset] = 0;
	return (arg);
}

int	get_arg_size(char *input, bool include_quotes)
{
	int		len;
	int		adjust;
	char	quotations;
	char	prev_quotations;

	len = 0;
	adjust = 0;
	quotations = 0;
	while (input[len] && (quotations != 0 || input[len] != ' '))
	{
		prev_quotations = quotations;
		quotations = check_quotations(input[len], quotations);
		if (prev_quotations != quotations)
			adjust++;
		len++;
	}
	if (include_quotes)
		return (len);
	return (len - adjust);
}
