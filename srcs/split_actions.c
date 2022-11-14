/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:06:12 by jgobbett          #+#    #+#             */
/*   Updated: 2022/11/14 15:11:56 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*

void	print_actions(t_action *actions)
{
	t_action	*tempactions = actions;
	int			size = 0;
	int			count = 0;
	int			i;

	while (tempactions != NULL)
	{
		tempactions = tempactions->next;
		size++;
	}
	printf("---TOTAL ACTIONS TO PERFORM: %i---\n", size);
	while (count < size)
	{
		printf("-ACTION %i-\n", count + 1);
		printf("COMMAND:  %s\n", actions->command);
		printf("RELATION: %s\n", actions->relation);
		printf("ARGC:\t  %i\n", actions->argc);
		i = 0;
		while (actions->argv[i] != NULL)
		{
			printf("ARG %i:\t%s\n", i, actions->argv[i]);
			i++;
		}
		printf("\n");
		count++;
		actions = actions->next;
	}
}
*/
