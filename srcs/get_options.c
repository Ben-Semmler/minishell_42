/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <bsemmler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:05:05 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/18 15:01:45 by bsemmler         ###   ########.fr       */
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
	action->args.argv = malloc(sizeof(char *) * (argn + 1));
	while (input[i] && argi < argn)
	{
		while (input[i] && input[i] == ' ')
			i++;
		action->args.argv[argi] = copy_arg(&input[i], returnval);
		i += get_arg_size(&input[i], 1, returnval);
		argi++;
	}
	action->args.argv[argi] = NULL;
	action->args.argc = argi;
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

t_container	get_arg_size2(char *input, int returnval,
	t_container c, bool include_interpret)
{
	if (input[c.i1] == '$' && c.b)
	{
		if (input[c.i1 + 1] == '?')
		{
			c.i1 += 2;
			c.i3 += (int)ft_strlen(ft_itoa(returnval)) - 2;
		}
		else
		{
			c.i3 += ft_strlen(search(get_key(&input[++c.i1])).data);
			c.i3 -= ft_strlen(get_key(&input[c.i1])) + 1;
			c.i1 += ft_strlen(get_key(&input[c.i1]));
			if (include_interpret)
				c.i3 -= 2;
		}
	}
	else
	{
		c.c2 = c.c1;
		c.c1 = check_quotations(input[c.i1], c.c1);
		if (c.c2 != c.c1)
			c.i2 += 1;
		c.i1++;
	}
	return (c);
}

int	get_arg_size(char *input, bool include_interpret, int returnval)
{
	t_container	c;

	c.i1 = 0;
	c.b = true;
	c.i3 = 0;
	c.i2 = 0;
	c.c1 = 0;
	while (input[c.i1] && (c.c1 != 0 || input[c.i1] != ' '))
	{
		if (input[c.i1] == 39)
			c.b = !c.b;
		c = get_arg_size2(input, returnval, c, include_interpret);
	}
	if (include_interpret)
		return (c.i1);
	return (c.i1 + c.i3 - c.i2);
}
