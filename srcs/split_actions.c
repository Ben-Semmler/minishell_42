/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:15:01 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/15 18:53:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			find_next_seperator(char *input);
t_action	*redir_reverse(t_action *action, char *input,
				int *k, int returnval);
void		fill_action(t_action *action, char *input, int size, int returnval);
t_action	*init_next_action(t_action *action);
int			check_pipe_chars(char *input);
char		*find_relation(char *input);
void		print_actions(t_action *actions);

t_action	*split_actions2(void)
{
	return (malloc(sizeof(t_action)));
}

int	init_split_actions(t_action	*tempaction)
{
	tempaction->command = NULL;
	tempaction->fork = true;
	return (0);
}

t_action	*split_actions(char *input, int returnval)
{
	t_action	*actions;
	t_action	*tempaction;
	int			i;
	int			j;
	int			k;

	actions = malloc(sizeof(t_action));
	tempaction = actions;
	i = init_split_actions(tempaction);
	while ((size_t)i < ft_strlen(input))
	{
		k = 0;
		tempaction->relation = find_relation(&input[i]);
		i += check_pipe_chars(&input[i]);
		j = find_next_seperator(&input[i]);
		if (input[i + j] == '<')
			tempaction = redir_reverse(tempaction,
					&input[i + j], &k, returnval);
		fill_action(tempaction, &input[i], j, returnval);
		i += j + k;
		if (input[i])
			tempaction = init_next_action(tempaction);
	}
	actions->fork = !(actions->next == NULL);
	return (actions);
}

int	find_next_seperator(char *input)
{
	int		i;
	char	quotations;

	i = 0;
	quotations = 0;
	while (input[i])
	{
		if (quotations == 0 && check_pipe_chars(&input[i]))
			break ;
		if (input[i] == 34 || input[i] == 39)
		{
			if (quotations == 0)
				quotations = input[i];
			else
				quotations = 0;
		}
		i++;
	}
	return (i);
}

t_action	*redir_reverse(t_action *action, char *input, int *k, int returnval)
{
	action->relation = find_relation(input);
	*k = check_pipe_chars(input);
	fill_action(action, &input[*k],
		find_next_seperator(&input[*k]), returnval);
	action = init_next_action(action);
	*k += find_next_seperator(&input[*k]);
	return (action);
}
