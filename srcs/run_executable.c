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
	{
		while ((dup2(filedes[1], STDERR_FILENO) == -1) && (errno == EINTR))
			;
		execve(cwd, input->argv, NULL);
		output->stderr = ft_joinfree("minishell: ./", 0,
				ft_strjoin(input->argv[0], ": cannot execute file"), 1);
		exit(127);
	}
	close(filedes[1]);
	output->stderr = read_fd(filedes, false);
	waitpid(p, &wstatus, 0);
	free(cwd);
	return (WEXITSTATUS(wstatus));
}
