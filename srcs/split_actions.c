/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:15:01 by bsemmler          #+#    #+#             */
/*   Updated: 2022/06/28 15:15:02 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strncpy(char *src, int size);

t_action	*split_actions(char *input)
{
	t_action	*actions;
	t_action 	*tempaction;
	char		*tempin = NULL;
	char		quotations = 0;
	int			i;
	int			i2;

	actions = malloc(sizeof(t_action));
	tempaction = actions;
	tempaction->command = NULL;
	i = 0;
	while ((size_t)i < ft_strlen(input))
	{
		i2 = 0;
		while (input[i + i2] && (input[i + i2] != '|' || quotations != 0))
		{
			if (input[i + i2] == 34 || input[i + i2] == 39)
			{
				if (quotations == 0)
					quotations = input[i + i2];
				else
					quotations = 0;
			}
			i2++;
		}
		tempin = ft_strncpy(&input[i], i2);
		tempaction->command = get_options(tempin);
		tempaction->next = NULL;
		free(tempin);
		i += i2 + 1;
		if (input[i])
		{
			tempaction->next = malloc(sizeof(t_action));
			tempaction = tempaction->next;
		}
	}
	return (actions);
}

char	*ft_strncpy(char *src, int size)
{
	int		i;
	char	*out;

	i = 0;
	out = malloc(sizeof(char) * (size + 1));
	while (src[i] && i < size)
	{
		out[i] = src[i];
		i++;
	}
	out[i] = 0;
	return (out);
}
