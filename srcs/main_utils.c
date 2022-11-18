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

bool	*return_run(bool *run)
{
	static bool	*rp;

	if (run != NULL)
		rp = run;
	return (rp);
}

void	handle_sig(int sig)
{
	bool	*r;

	r = return_run(NULL);
	if (sig == SIGQUIT)
		*r = false;
	else
	{
		rl_replace_line("", 0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

bool	is_command_empty(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i])
		return (false);
	return (true);
}
