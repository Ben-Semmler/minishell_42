/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:48:11 by jgobbett          #+#    #+#             */
/*   Updated: 2022/11/14 15:53:20 by jgobbett         ###   ########.fr       */
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

int	execute_actions2(t_outputs *output, char **stderrs,
	t_action *action)
{
	int	i;

	if (output->stdout && (action->relation == NULL
			|| ft_strncmp(action->relation, "|", 2) == 0))
		printf("%s", output->stdout);
	i = 0;
	while ((unsigned int)i < action_size(action))
	{
		if (stderrs[i] != NULL)
		{
			printf("%s", stderrs[i]);
			free(stderrs[i]);
		}
		i++;
	}
	free(stderrs);
	return (output->returnval);
}

int	execute_actions(t_action *action, bool *run)
{
	int			i;
	t_inputs	input;
	t_outputs	output;
	char		**stderrs;

	i = 0;
	output.stdout = NULL;
	output.stderr = NULL;
	output.returnval = INT_MAX;
	stderrs = malloc(sizeof(char *) * action_size(action));
	while (true)
	{
		input.argc = action->argc;
		input.argv = action->argv;
		input.stdin = output.stdout;
		switch_relation(action, &input, &output, run);
		stderrs[i] = output.stderr;
		if (action->next == NULL)
			break ;
		action = action->next;
		i++;
	}
	return (execute_actions2(&output, stderrs, action));
}

void	switch_relation(t_action *action, t_inputs *input,
	t_outputs *output, bool *run)
{
	if (action->relation == NULL || ft_strncmp(action->relation, "|", 2) == 0)
		run_action(action, input, output, run);
	else if (ft_strncmp(action->relation, ">", 2) == 0)
		write_to_file(input->stdin, action->command);
	else if (ft_strncmp(action->relation, ">>", 3) == 0)
		write_to_file_append(input->stdin, action->command);
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
