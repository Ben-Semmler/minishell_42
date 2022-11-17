/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:21:48 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/15 20:20:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_actions(t_action *action, bool *run);
int		switch_relation(t_action *action, bool *run, int outfd);
size_t	action_size(t_action *action);
int		run_piped_action(t_action *action, int stdin_fd, char **stderrs);

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

int	init(int argc, char **argv, char **env, bool *run)
{
	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sig);
	import_env(env);
	*run = true;
	return_run(run);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_action	*actions;
	char		*input;
	bool		run;
	int			returnval;

	returnval = init(argc, argv, env, &run);
	while (run)
	{
		input = readline("minishell& ");
		if (!input)
			run = false;
		if (input && input[0])
		{
			add_history(input);
			actions = split_actions(input, returnval);
			returnval = execute_actions(actions, &run);
			free(input);
		}
	}
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
		returnval = switch_relation(action, run, STDOUT_FILENO);
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
	int		wstatus;

	pipe(fstdout);
	pipe(fstderr);
	cmd_p = fork();
	if (cmd_p == 0)
	{
		dup2(stdin_fd, STDIN_FILENO);
		if (action->next != NULL)
			dup2(fstdout[1], STDOUT_FILENO);
		dup2(fstderr[1], STDERR_FILENO);
		exit(switch_relation(action, false, fstdout[1]));
	}
	close(fstdout[1]);
	close(fstderr[1]);
	if (action->next != NULL)
		returnval = run_piped_action(action->next, fstdout[0], &errors[1]);
	errors[0] = read_fd(fstderr, false);
	waitpid(cmd_p, &wstatus, 0);
	return (((action->next != NULL) * returnval)
		+ ((action->next == NULL) * WEXITSTATUS(wstatus)));
}
