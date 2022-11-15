/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:21:48 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/15 15:50:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool debug;

int		execute_actions(t_action *action, bool *run);
void	switch_relation(t_action *action, t_inputs *input, t_outputs *output, bool *run);
void	run_action(t_action *action, t_inputs *input, t_outputs *output, bool *run);
size_t	action_size(t_action *action);

bool *return_run(bool *run)
{
	static bool *rp;

	if (run != NULL)
		rp = run;
	return (rp);
}

void handle_sig(int sig)
{
	bool *r;

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

int	main(int argc, char **argv, char **env)
{
	debug = false;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sig);
	

	t_action	*actions;
	char		*input;
	bool		run;
	int			returnval;

	(void)argc;
	(void)argv;
 	import_env(env);
	returnval = 0;
	run = true;
	return_run(&run);

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
	int			i = 0;
	t_inputs	input;
	t_outputs	output;
	char		**stderrs;
	
	output.stdout = NULL;
	output.stderr = NULL;
	output.returnval = INT_MAX;
	stderrs = malloc(sizeof(char*) * action_size(action));
	while (true)
	{
		printf("STARTING LOOP\n");
		input.argc = action->argc;
		input.argv = action->argv;
		input.stdin = output.stdout;
		switch_relation(action, &input, &output, run);
		stderrs[i] = output.stderr;
		if (action->next == NULL)
			break;
		action = action->next;
		i++;
	}

	if (output.stdout && (action->relation == NULL || ft_strncmp(action->relation, "|", 2) == 0))
		printf("%s", output.stdout);
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
	return (output.returnval);
}

void	switch_relation(t_action *action, t_inputs *input, t_outputs *output, bool *run)
{
	if (action->relation == NULL || ft_strncmp(action->relation, "|", 2) == 0)
		run_action(action, input, output, run);
	else if (ft_strncmp(action->relation, ">", 2) == 0)
		writeToFile(input->stdin, action->command);
	else if (ft_strncmp(action->relation, ">>", 3) == 0)
		writeToFile_append(input->stdin, action->command);
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

void	run_action(t_action *action, t_inputs *input, t_outputs *output, bool *run)
{
	int		fstdin[2];
	int		fstdout[2];
	int		fstderr[2];
	pid_t	p;
	pid_t	p2;
	int		wstatus;

	//Bandaid fix for cd and exit not working as child process
	if (!action->fork)
		output->returnval = switch_command(action->command, input, output, run);
	//DON'T MODIFY THIS SECTION
	//vvv
	else
	{
		pipe(fstdin);
		pipe(fstdout);
		pipe(fstderr);
		p = fork();
		if (p == 0)
		{
			if (input->stdin != NULL)
				write(fstdin[1], input->stdin, ft_strlen(input->stdin));
			p2 = fork();
			if (p2 == 0)
			{
				dup2(fstdin[0], STDIN_FILENO);
				dup2(fstdout[1], STDOUT_FILENO);
				dup2(fstderr[1], STDERR_FILENO);
				exit(switch_command(action->command, input, output, false));
			}
			waitpid(p2, &wstatus, 0);
			exit(WEXITSTATUS(wstatus));
		}
		p2 = fork();
		if (p2 == 0)
		{
			close(fstderr[1]);
			output->stderr = read_fd(fstderr, false);
			waitpid(p, NULL, 0);
			dup2(fstderr[1], STDERR_FILENO);
			write(fstderr[1], output->stderr, ft_strlen(output->stderr));
			exit(0);
		}
		close(fstdout[1]);
		close(fstderr[1]);
		output->stdout = read_fd(fstdout, action->next == NULL);
		waitpid(p, &wstatus, 0);
		output->stderr = read_fd(fstderr, false);
		waitpid(p2, NULL, 0);
		if (action->next == NULL)
			output->returnval = WEXITSTATUS(wstatus);
	}
	//^^^
	//DON'T MODIFY THIS SECTION
}

void	free_split_input(char **s_input)
{
	int	i;

	//Free the split input
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
	return(i);
}

//DEBUG
void	print_inputs(const t_inputs input)
{
	printf("--INPUT STRUCT--\n");
	printf("ARGC: %i\n", input.argc);

	printf("ARGV:\n");
	for (int i = 0; input.argv[i]; i++)
		printf("  ARG %i: %s\n", i, input.argv[i]);

	printf("STDIN: %s", input.stdin);
	printf("\n");

}

void	print_outputs(const t_outputs output)
{
	printf("--OUTPUT STRUCT--\n");
	printf("STDOUT: %s", output.stdout);
	if (output.stdout == NULL)
		printf("\n");
}
//DEBUG

// int	main(int argc, char **argv, char **env)
// {
// 	int		run;
// 	char	*input;
// 	char	*output;

// 	run = 1;
// 	while (run == 1)
// 	{
// 		input = readline("minishell& ");
// 		add_history(input);
// 		//vv - Do stuff with the input in here - vv -b
// 		output = switch_command(input, &run);
// 		if (output != NULL)
// 		{
// 			printf("%s", output);
// 			free(output);
// 		}
// 		free(input);
// 	}
// }

// int	main(int argc, char **argv, char **env)
// {
// 	int		run;
// 	char	*input;
// 	char	*output;

// 	(void)argc;
// 	(void)argv;

// 	import_env(env);
// 	run = 1;
// 	while (run == 1)
// 	{
// 		input = readline("minishell& ");
// 		add_history(input);
// 		//vv - Do stuff with the input in here - vv -b
// 		output = switch_command(input, &run);
// 		if (output != NULL)
// 		{
// 			printf("%s", output);
// 			free(output);
// 		}
// 		free(input);
// 	}
// }

/*void writeToFile(char *input, char *file)
{
	write(open(file, O_WRONLY | O_CREAT, 0644), input, ft_strlen(input));
}

void writeToFile_append(char *input, char *file)
{
	write(open(file, O_WRONLY | O_CREAT | O_APPEND, 0644), input, ft_strlen(input));
}

void print_out(t_cmd *cmd)
{
	printf("%s", cmd->output);
}

void	append_out(t_cmd *cmd)
{
	int		i;
	char	*name;

	i = 1;
	while (cmd->input[i] && ft_strncmp(cmd->input[i], ">>", 2) && ft_strncmp(cmd->input[i], ">", 1))
		i++;
	name = cmd->input[i + 1];
	i = 0;
	while (*name && (*name == ' ' || *name == '	'))
		name++;
	writeToFile(cmd->output, name);
}

int	main(void)
{
	t_cmd	cmd;
	char	*test_input[6] = {"echo", "n", "hello", "world", ">", "out"};
	char	*test_output = "hello world";

	//cmd.input = av;

	//writeToFile(test, "t");
	cmd.input = test_input;
	cmd.output = test_output;

	//void	(*in_fun)(t_cmd *cmd);
	//void	(*out_fun)(t_cmd *cmd);

	//in_fun	= &echo;
	//out_fun = &append_out;

	cmd.in_fun = &command_echo;
	cmd.out_fun = &print_out;
	cmd.in_fun(&cmd);
	cmd.out_fun(&cmd);
}*/