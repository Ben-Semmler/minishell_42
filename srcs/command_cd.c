/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:31:21 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/14 15:13:19 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_cd(const t_inputs *input)
{
	if (input->argv[0] == NULL)
		return (1);
	if (input->argv[0][0] == '/')
		return (cd_absolute(input->argv));
	else
		return (cd_relative(input->argv));
}

int	cd_absolute(char **argv)
{
	if (chdir(argv[0]) != 0)
	{
		printf("minishell: %s: No such file or directory\n", argv[0]);
		return (1);
	}
	return (0);
}

void	cd_relative2(char *cwd, char *ext, char *cwdext, int *returnval)
{
	ext = ft_strjoin("/", argv[0]);
	cwdext = ft_strjoin(cwd, ext);
	if (chdir(cwdext) != 0)
	{
		printf("minishell: %s: No such file or directory\n", argv[0]);
		*returnval = 1;
	}
	free(ext);
	free(cwdext);
}

int	cd_relative(char **argv)
{
	char	*cwd;
	char	*ext;
	char	*cwdext;
	int		returnval;

	returnval = 0;
	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) != NULL)
		cd_relative2(cwd, ext, cwdext, &returnval);
	else
	{
		printf("Error: could not get working directory\n");
		returnval = 1;
	}
	free(cwd);
	return (returnval);
}
