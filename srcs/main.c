/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <bsemmler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:21:48 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/18 17:00:27 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_actions(t_action *action, bool *run);
int		run_piped_action(t_action *action, int stdin_fd, char **stderrs);
int		switch_relation(t_action *action, bool *run, int in_fd, int outfd);

size_t	action_size(t_action *action);
bool	is_command_empty(char *input);
void	handle_sig(int sig);

int	main(int argc, char **argv, char **env)
{
	t_action	*actions;
	char		*input;
	bool		run;
	int			returnval;

	(void)argc;
	(void)argv;
	returnval = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sig);
	import_env(env);
	run = true;
	return_run(&run);
	while (run)
	{
		input = readline("minishell& ");
		if (!is_command_empty(input))
		{
			add_history(input);
			actions = split_actions(input, returnval);
			returnval = execute_actions(actions, &run);
			free(input);
		}
	}
	return (0);
}

int	execute_actions(t_action *action, bool *run)
{
	int		i;
	int		returnval;
	char	**errors;

	returnval = INT_MAX;
	errors = malloc(sizeof(char *) * action_size(action));
	i = -1;
	while (i++ < (int)action_size(action) - 1)
		errors[i] = NULL;
	if (action->next == NULL)
		returnval = switch_relation(action, run, STDIN_FILENO, STDOUT_FILENO);
	else
		returnval = run_piped_action(action, STDIN_FILENO, errors);
	i = 0;
	while ((unsigned int)i < action_size(action))
	{
		if (errors[i] != NULL)
		{
			printf("%s", errors[i]);
			free(errors[i]);
		}
		i++;
	}
	free(errors);
	return (returnval);
}

int	run_piped_action(t_action *action, int stdin_fd, char **errors)
{
	pid_t	cmd_p;
	int		fstdout[2];
	int		fstderr[2];
	int		returnval;

	pipe(fstdout);
	pipe(fstderr);
	cmd_p = fork();
	if (cmd_p == 0)
	{
		dup2(stdin_fd, STDIN_FILENO);
		if (action->next != NULL && (action->relation == NULL
				|| ft_strncmp(action->relation, "|", 2) == 0))
			dup2(fstdout[1], STDOUT_FILENO);
		dup2(fstderr[1], STDERR_FILENO);
		exit(switch_relation(action, false, stdin_fd, fstdout[1]));
	}
	close(fstdout[1]);
	close(fstderr[1]);
	returnval = 0;
	if (action->next != NULL)
		returnval = run_piped_action(action->next, fstdout[0], &errors[1]);
	errors[0] = read_fd(fstderr[0], false);
	waitpid(cmd_p, (int *)((long)(action->next == NULL) * (long)&returnval), 0);
	return (returnval / (((action->next == NULL) * 255) + 1));
}

int	switch_relation(t_action *action, bool *run, int infd, int outfd)
{
	if (action->relation == NULL || ft_strncmp(action->relation, "|", 2) == 0)
		return (switch_command(action->command, &action->args, run));
	else if (ft_strncmp(action->relation, ">", 2) == 0)
		return (write_file(action->command, infd));
	else if (ft_strncmp(action->relation, ">>", 3) == 0)
		return (write_file_append(action->command, infd));
	else if (ft_strncmp(action->relation, "<", 2) == 0)
		return (redir_left(action->command, outfd));
	else if (ft_strncmp(action->relation, "<<", 3) == 0)
		return (insert_doc(action->command, outfd));
	return (127);
}
