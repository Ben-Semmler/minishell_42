/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:21:48 by bsemmler          #+#    #+#             */
/*   Updated: 2022/06/23 12:51:10 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_actions(t_action *action, bool *run);
void	switch_relation(t_action *action, t_inputs *input, t_outputs *output, bool *run);
void	run_action(t_action *action, t_inputs *input, t_outputs *output, bool *run);

int	main(int argc, char **argv, char **env)
{
	t_action	*actions;
	char		*input;
	bool		*run;

	(void)argc;
	(void)argv;
 	import_env(env);
	run = malloc(sizeof(bool));
	*run = true;
	while (*run)
	{
		input = readline("minishell& ");
		add_history(input);
		//vv - Do stuff with the input in here - vv -b
		actions = split_actions(input);
		execute_actions(actions, run);
		free(input);
	}
	free(run);
}

void	execute_actions(t_action *action, bool *run)
{
	t_inputs	input;
	t_outputs	output;
	
	output.stdout = NULL;
	while (true)
	{
		input.argc = action->argc;
		input.argv = action->argv;
		input.stdin = output.stdout;
		switch_relation(action, &input, &output, run);
		if (action->next == NULL)
			break;
		action = action->next;
	}
	if (output.stdout && (action->relation == NULL || ft_strncmp(action->relation, "|", 2) == 0))
		printf("%s", output.stdout);
}

void	switch_relation(t_action *action, t_inputs *input, t_outputs *output, bool *run)
{
	//printf("switch relation\n");
	if (action->relation == NULL || ft_strncmp(action->relation, "|", 2) == 0)
	{
		run_action(action, input, output, run);
		return ;
	}
	else if (ft_strncmp(action->relation, ">", 2) == 0)
		writeToFile(input->stdin, action->command);
	else if (ft_strncmp(action->relation, ">>", 3) == 0)
		writeToFile_append(input->stdin, action->command);
	else if (ft_strncmp(action->relation, "<", 2) == 0)
	{
		readFile(action->command, output);
		return ;
	}
	else if (ft_strncmp(action->relation, "<<", 3) == 0)
	{
		insert_doc(action->command, output);
		return ;
	}
	else if (output->stdout != NULL)
		free(output->stdout);
	output->stdout = NULL;
}

void	run_action(t_action *action, t_inputs *input, t_outputs *output, bool *run)
{
	int		filedes[2];
	pid_t	p;

	//Bandaid fix for cd and exit not working as child process, should be modified
	if (ft_strncmp(action->command, "cd", 3) == 0)
		command_cd(input);
	else if (ft_strncmp(action->command, "exit", 5) == 0)
		*run = false;
	else
	{
		pipe(filedes);
		p = fork();
		if (p == 0)
		{
			while ((dup2(filedes[1], STDOUT_FILENO) == -1) && (errno == EINTR))
				;
			switch_command(action->command, input);
			exit(0);
		}
		close(filedes[1]);
		output->stdout = read_stdout(action, filedes);
	}
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