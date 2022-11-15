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

void	run_action(t_action *action, t_inputs *input,
			t_outputs *output, bool *run);

void	switch_relation(t_action *action, t_inputs *input,
			t_outputs *output, bool *run)
{
	if (action->relation == NULL || ft_strncmp(action->relation, "|", 2) == 0)
		run_action(action, input, output, run);
	else if (ft_strncmp(action->relation, ">", 2) == 0)
		write_file(input->stdin, action->command);
	else if (ft_strncmp(action->relation, ">>", 3) == 0)
		write_file_append(input->stdin, action->command);
	else if (ft_strncmp(action->relation, "<", 2) == 0)
		redir_left(action->command, output);
	else if (ft_strncmp(action->relation, "<<", 3) == 0)
		insert_doc(action->command, output);
	else if (output->stdout != NULL)
		free(output->stdout);
	if (action->relation != NULL && (ft_strncmp(action->relation, ">", 2) == 0
			|| ft_strncmp(action->relation, ">>", 3) == 0))
		output->stdout = NULL;
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
