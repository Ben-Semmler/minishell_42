/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:31:40 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/14 16:00:18 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_executable2(int filedes[2], char *cwd,
	t_inputs *input, t_outputs *output)
{
	while ((dup2(filedes[1], STDERR_FILENO) == -1) && (errno == EINTR))
		;
	execve(cwd, input->argv, NULL);
	output->stderr = ft_joinfree("minishell: ./", 0,
			ft_strjoin(input->argv[0], ": cannot execute file"), 1);
	exit(127);
}

int	run_executable(t_inputs *input, t_outputs *output)
{
	char	*cwd;
	pid_t	p;
	int		filedes[2];
	int		wstatus;

	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
	{
		free(cwd);
		return (1);
	}
	cwd = ft_joinfree(cwd, 1, ft_strjoin("/", input->argv[0]), 1);
	pipe(filedes);
	p = fork();
	if (p == 0)
		run_executable2(filedes, cwd, input, output);
	close(filedes[1]);
	output->stderr = read_fd(filedes, false);
	waitpid(p, &wstatus, 0);
	free(cwd);
	return (WEXITSTATUS(wstatus));
}
