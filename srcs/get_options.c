/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:05:05 by bsemmler          #+#    #+#             */
/*   Updated: 2022/09/16 18:42:13 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_command(t_action *action, char *input, int returnval);
int		get_argn(char *input);
char	*copy_arg(char *input, int returnval);
int		get_arg_size(char *input, bool include_quotes, int returnval);
int		get_env_len(char *str);
char	*get_key(char *str);

void	get_options(t_action *action, char *input, int returnval)
{
	int		i;
	int		argi;
	int		argn;

	i = get_command(action, input, returnval);
	argi = 0;
	argn = get_argn(&input[i]);
	action->argv = malloc(sizeof(char *) * (argn + 1));
	while (input[i] && argi < argn)
	{
		while (input[i] && input[i] == ' ')
			i++;
		action->argv[argi] = copy_arg(&input[i], returnval);
		i += get_arg_size(&input[i], 1, returnval);
		argi++;
	}
	action->argv[argi] = NULL;
	action->argc = argi;
}

int	get_command(t_action *action, char *input, int returnval)
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
		action->command = copy_arg(&input[i], returnval);
		i += get_arg_size(&input[i], true, returnval);
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
			if (input[i] == '\\')
				i++;
			i++;
		}
		while (input[i] == ' ')
			i++;
		argn++;
	}
	return (argn);
}

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
		{
			if (input[i + 1] == '?')
			{
				int i2 = 0;
				while (ft_itoa(returnval)[i2])
				{
					arg[i - offset + i2] = ft_itoa(returnval)[i2];
					i2++;
				}
				i += 2;
				offset -= i2 - 2;
			}
			else
			{
				i++;
				offset++;
				offset -= insert_data(&arg[i - offset], get_key(&input[i])) - ft_strlen(get_key(&input[i]));
				i += ft_strlen(get_key(&input[i]));
			}
		}
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
