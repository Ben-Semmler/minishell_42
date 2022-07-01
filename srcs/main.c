/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:21:48 by bsemmler          #+#    #+#             */
/*   Updated: 2022/06/14 15:26:11 by jgobbett         ###   ########.fr       */
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

int	main(void)
{
	t_action	*actions;
	t_action	*tempaction;
	pid_t		p;
	int			run;
	char		*input;
	char		*stdout;
	int			filedes[2];

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

// 	(void)argc;
// 	(void)argv;
// 	(void)env;
// 	char *test = "kerdfgkjny$USER ya mum";

// 	printf("%s\n", test);
// 	printf("%s\n", get_key(test));
// 	printf("%s\n", get_data(test));
// 	check_env(argv);
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
