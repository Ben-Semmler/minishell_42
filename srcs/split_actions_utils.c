/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_actions_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:07:02 by jgobbett          #+#    #+#             */
/*   Updated: 2022/11/14 14:08:16 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_action(t_action *action, char *input, int size, int returnval)
{
	char	*tempin;

	tempin = ft_strncpy(input, size);
	get_options(action, tempin, returnval);
	action->next = NULL;
	free(tempin);
}

t_action	*init_next_action(t_action *action)
{
	action->next = malloc(sizeof(t_action));
	action = action->next;
	action->command = NULL;
	action->argc = 0;
	action->argv = NULL;
	action->relation = NULL;
	action->next = NULL;
	action->fork = true;
	return (action);
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

int	check_pipe_chars(char *input)
{
	if (input[0] != '|' && input[0] != '>' && input[0] != '<')
		return (0);
	if (input[1] == 0 || (ft_strncmp(input, ">>", 2) != 0
			&& ft_strncmp(input, "<<", 2) != 0))
		return (1);
	return (2);
}

char	*find_relation(char *input)
{
	int		size;

	size = check_pipe_chars(input);
	if (!size)
		return (NULL);
	return (ft_strncpy(input, size));
}
