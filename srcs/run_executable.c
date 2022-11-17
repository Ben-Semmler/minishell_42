/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_executable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:31:40 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/15 18:20:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /char	**create_args(char **input);

int	run_executable(const t_args *args)
{
	char	*cwd;
	pid_t	p;
	int		wstatus;

	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
	{
		free(cwd);
		return (1);
	}
	cwd = ft_joinfree(cwd, 1, ft_strjoin("/", args->argv[0]), 1);
	p = fork();
	if (p == 0)
	{
		execve(cwd, args->argv, NULL);
		perror(ft_joinfree("minishell: ./", 0,
			ft_strjoin(args->argv[0], ": cannot execute file"), 1));
	}
	exit(127);
	waitpid(p, &wstatus, 0);
	free(cwd);
	return (WEXITSTATUS(wstatus));
}
