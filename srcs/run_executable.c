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

void	run_executable(t_inputs *input)
{
	char	*cwd;
	pid_t	p;

	//Create buffer with size of PATH_MAX, fill using getcwd to get
	//the working directory
	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
	{
		free(cwd);
		printf("Error: could not get directory\n");
	}
	cwd = ft_joinfree(cwd, 1, ft_strjoin("/", input->argv[0]), 1);
	p = fork();
	if (p == 0)
	{
		execve(cwd, input->argv, NULL);
		printf("Error: failed to run program\n");
		exit(1);
	}
	wait(NULL);
	free(cwd);
}

/*char	**create_args(char **input)
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
}*/
