/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:47:31 by marvin            #+#    #+#             */
/*   Updated: 2022/11/15 16:47:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	switch_relation(t_action *action, bool *run, int outfd)
{
	if (action->relation == NULL || ft_strncmp(action->relation, "|", 2) == 0)
		return(switch_command(action->command, &action->args, run));
	else if (ft_strncmp(action->relation, ">", 2) == 0)
		return(write_file(action->command));
	else if (ft_strncmp(action->relation, ">>", 3) == 0)
		return(write_file_append(action->command));
	else if (ft_strncmp(action->relation, "<", 2) == 0)
		return(redir_left(action->command, outfd));
	else if (ft_strncmp(action->relation, "<<", 3) == 0)
		return(insert_doc(action->command, outfd));
	return (0);
}

void	free_split_input(char **s_input)
{
	int	i;

	i = 0;
	while (s_input[i] != NULL)
	{
		free(s_input[i]);
		i++;
	}
	free(s_input);
}

size_t	action_size(t_action *action)
{
	size_t	i;

	i = 1;
	while (action->next != NULL)
	{
		action = action->next;
		i++;
	}
	return (i);
}
