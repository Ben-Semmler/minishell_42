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

char	**add_element(char **arr, char *toadd)
{
	int		i;
	char	**newarr;

	i = 0;
	while (arr[i] != NULL)
		i++;
	newarr = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (arr[i] != NULL)
	{
		//printf("arr[i]");
		newarr[i] = arr[i];
		i++;
	}
	newarr[i] = toadd;
	newarr[i + 1] = NULL;
	return (newarr);
}

int	main(int argc, char **argv, char **env)
{
	t_action	*actions;
	t_action	*tempaction;
	pid_t		p;
	int			run;
	char		*input;
	char		*stdout;
	int			filedes[2];

	(void)argc;
	(void)argv;
 	import_env(env);
	run = 1;
	while (run == 1)
	{
		input = readline("minishell& ");
		add_history(input);
		//vv - Do stuff with the input in here - vv -b
		actions = split_actions(input);
		tempaction = actions;
		while (tempaction != NULL)
		{
			stdout = NULL;
			//BANDAID FIX FOR CD NOT WORKING AS A CHILD PROCESS, FIX LATER
			if (ft_strncmp(tempaction->command[0], "cd", 3) == 0)
				command_cd(tempaction->command);
			else
			{
				pipe(filedes);
				p = fork();
				if (p == 0)
				{
					while ((dup2(filedes[1], STDOUT_FILENO) == -1) && (errno == EINTR))
						;
					switch_command(tempaction->command, stdout, &run);
					exit(0);
				}
				close(filedes[1]);
				stdout = read_stdout(tempaction, filedes);
			}
			if (!tempaction->next && stdout)
			{
				printf("%s", stdout);
				free(stdout);
			}
			tempaction = tempaction->next;
		}
		free(input);
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