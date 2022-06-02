/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:31:40 by bsemmler          #+#    #+#             */
/*   Updated: 2022/04/22 15:31:41 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_args(char **input);

char	*run_executable(char **input)
{
	char	*cwd;
	char	*output;
	char	**args;
	pid_t	p;

	//Create buffer with size of PATH_MAX, fill using getcwd to get
	//the working directory
	output = NULL;
	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
	{
		free(cwd);
		return (ft_strdup("Error: could not get directory\n"));
	}
	cwd = ft_joinfree(cwd, 1, ft_strjoin("/", &input[0][2]), 1);
	args = create_args(input);
	p = fork();
	if (p == 0)
	{
		execve(cwd, input, NULL);
		printf("Error: failed to run program\n");
		exit(1);
	}
	wait(NULL);
	free(cwd);
	free(args[0]);
	free(args);
	return (output);
}

char	**create_args(char **input)
{
	char	**args;
	int		i;

	i = 0;
	while (input[i] != NULL)
		i++;
	args = malloc(sizeof(char *) * i);
	args[0] = ft_strdup(&input[0][2]);
	i = 1;
	while (input[i] != NULL)
	{
		args[i] = input[i];
		i++;
	}
	args[i] = NULL;
	return (args);
}
