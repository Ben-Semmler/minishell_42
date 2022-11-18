/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <bsemmler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:55:06 by jgobbett          #+#    #+#             */
/*   Updated: 2022/11/18 15:09:55 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_arg_size(char *input, bool include_quotes, int returnval);

/*
	int		i = c.i1;
	int		offset c.i2;
	int		arg_size = c.i3;
	char	quotations = c.c1;
	char	prev_quotations = c.c2;
	char	*arg = c.cp1;
	bool	interpret c.b;
*/

t_container	copy_arg2(char *input, int returnval, t_container c)
{
	if (input[c.i1 + 1] == '?')
	{
		c.i4 = 0;
		while (ft_itoa(returnval)[c.i4])
		{
			c.cp1[c.i1 - c.i2 + c.i4] = ft_itoa(returnval)[c.i4];
			c.i4 += 1;
		}
		c.i1 += 2;
		c.i2 -= c.i4 - 2;
	}
	else
	{
		c.i1 += 1;
		c.i2 += 1;
		c.i2 -= insert_data(&c.cp1[c.i1 - c.i2],
				get_key(&input[c.i1])) - ft_strlen(get_key(&input[c.i1]));
		c.i1 += ft_strlen(get_key(&input[c.i1]));
	}
	return (c);
}

t_container	copy_arg3(char *input, t_container c)
{
	if (c.c2 != c.c1)
		c.i2++;
	else
		c.cp1[c.i1 - c.i2] = input[c.i1];
	c.i1 += 1;
	return (c);
}

char	*copy_arg(char *input, int returnval)
{
	t_container	c;

	c.i3 = get_arg_size(input, 0, returnval);
	c.cp1 = malloc(c.i3 + 1);
	c.i1 = 0;
	c.c1 = 0;
	c.i2 = 0;
	c.b = true;
	while (input[c.i1] && c.i1 - c.i2 < c.i3)
	{
		c.c2 = c.c1;
		c.c1 = check_quotations(input[c.i1], c.c1);
		if (input[c.i1] == 39)
			c.b = !c.b;
		if (input[c.i1] == '$' && c.b)
			c = copy_arg2(input, returnval, c);
		else
			c = copy_arg3(input, c);
	}
	c.cp1[c.i1 - c.i2] = 0;
	return (c.cp1);
}
