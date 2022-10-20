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

int	run_executable(const t_inputs *input, t_outputs *output)
{
	char	*cwd;
	pid_t	p;
	int		filedes[3];
	int		wstatus;
	//Create buffer with size of PATH_MAX, fill using getcwd to get
	//the working directory
	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
	{
		free(cwd);
		//output->stderr = ft_joinfree("./", 0, ft_strjoin(input->argv[0]""))
		return (1);
	}
	cwd = ft_joinfree(cwd, 1, ft_strjoin("/", input->argv[0]), 1);
	pipe(filedes);
	p = fork();
	if (p == 0)
	{
		execve(cwd, input->argv, NULL);
		output->stderr = ft_joinfree("minishell: ./", 0, ft_strjoin(input->argv[0], ": cannot execute file"), 1);
		exit(127);
	}
	//waitpid(0, &wstatus, 0);
	t_action	act;
	act.next = NULL;
	read_stdout(&act, &filedes[2]);
	free(cwd);
	return (WEXITSTATUS(wstatus));
}
