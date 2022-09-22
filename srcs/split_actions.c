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

char		*ft_strncpy(char *src, int size);
int			find_next_seperator(char *input);
t_action	*redir_reverse(t_action *action, char *input, int *k);
void		fill_action(t_action *action, char *input, int size);
t_action	*init_next_action(t_action* action);
int			check_pipe_chars(char *input);
char		*find_relation(char *input);

void	print_actions(t_action *actions);

t_action	*split_actions(char *input)
{
	t_action	*actions;
	t_action 	*tempaction;
	int			i;
	int			j;
	int			k;

	actions = malloc(sizeof(t_action));
	tempaction = actions;
	tempaction->command = NULL;
	i = 0;
	while ((size_t)i < ft_strlen(input))
	{
		k = 0;
		tempaction->relation = find_relation(&input[i]);
		i += check_pipe_chars(&input[i]);
		j = find_next_seperator(&input[i]);
		if (input[i + j] == '<')
			tempaction = redir_reverse(tempaction, &input[i + j], &k);
		fill_action(tempaction, &input[i], j);
		i += j + k;
		if (input[i])
			tempaction = init_next_action(tempaction);
	}

	//DEBUG
	if (debug)
		print_actions(actions);
	//DEBUG

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

t_action	*redir_reverse(t_action *action, char *input, int *k)
{
	action->relation = find_relation(input);
	*k = check_pipe_chars(input);
	fill_action(action, &input[*k],
		find_next_seperator(&input[*k]));
	action = init_next_action(action);
	*k += find_next_seperator(&input[*k]);
	return (action);
}

void	fill_action(t_action *action, char *input, int size)
{
	char	*tempin;

	tempin = ft_strncpy(input, size);
	get_options(action, tempin);
	action->next = NULL;
	free(tempin);
}

t_action	*init_next_action(t_action* action)
{
	action->next = malloc(sizeof(t_action));
	action = action->next;
	action->command = NULL;
	action->argc = 0;
	action->argv = NULL;
	action->relation = NULL;
	action->next = NULL;
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
